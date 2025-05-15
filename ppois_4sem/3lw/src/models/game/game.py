import pygame
import random
import os
from .gun import Gun
from .table_records import TableRecords
from .gif_object import GifObject
from src.models.menu import Menu

class Game:
    def __init__(self, screen, config):
        self.screen = screen
        self.config = config
        self.scroll_x = 0
        self.level = config['levels']['1']
        self.scroll_speed = self.level['scroll_speed']
        self.object_speed = self.level['object_speed']
        self.bg_width = config['entities']['background']['bg_width']
        self.object_x = self.bg_width
        self.gun = Gun(screen, config)
        self.score = 0
        self.game_timer = self.level['game_timer']
        self.game_over = False
        self.player_name = ""
        self.input_active = False
        self.paused = False
        self.show_records = False
        self.show_help = False
        self.table_records = TableRecords(config)
        self.menu = Menu(screen, config)
        self.font = pygame.font.SysFont(config['game_settings']['font'], config['game_settings']['font_size'])
        self.music_playing = False
        pygame.mouse.set_visible(False)
        self.layers = []
        
        for img_name in config['entities']['background']['layers']:
            img_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), img_name)
            try:
                layer = pygame.image.load(img_path).convert_alpha()
                self.layers.append(pygame.transform.scale(layer, (self.bg_width, config['entities']['background']['bg_height'])))
            except pygame.error as e:
                print(f"Error loading {img_name}: {e}")
                self.layers.append(pygame.Surface((self.bg_width, config['entities']['background']['bg_height']), pygame.SRCALPHA))
        
        self.parallax_factors = config['entities']['background']['parallax_factors']
        self.bg_height = self.layers[0].get_height()

        self.shot_sound = self.load_sound(config['entities']['sounds']['shot'])
        self.chicken_sound = self.load_sound(config['entities']['sounds']['chicken'])
        self.perezaryad_sound = self.load_sound(config['entities']['sounds']['reload'])
        self.background_music = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), config['entities']['sounds']['game_music'])
        self.cursor_img = self.load_cursor(config['entities']['cursor']['image'], config['entities']['cursor']['scale'])

        gif_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), config['entities']['gif_object']['default_gif'])
        self.gif_objects = [GifObject(gif_path, self.object_x, 350, 50, -self.object_speed, self.bg_width, config, layer="foreground")]
        self.gif_spawn_timer = 0
        self.gif_spawn_interval = self.level['gif_spawn_interval']
        self.reload_timer = 0
        self.reload_delay = self.level['reload_delay']
        self.waiting_for_reload = False
        self.special_gif_timer = 0
        self.special_gif_interval = self.level['special_gif_interval']

    def load_sound(self, sound_path):
        try:
            sound = pygame.mixer.Sound(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), sound_path))
            sound.set_volume(self.config['entities']['sounds']['volume'])
            return sound
        except pygame.error as e:
            print(f"Error loading sound {sound_path}: {e}")
            return None

    def load_cursor(self, cursor_path, scale):
        try:
            cursor_img = pygame.image.load(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), cursor_path)).convert_alpha()
            return pygame.transform.scale(cursor_img, scale)
        except pygame.error as e:
            print(f"Error loading cursor {cursor_path}: {e}")
            return pygame.Surface(scale, pygame.SRCALPHA)

    def start_background_music(self):
        if self.background_music and not self.music_playing:
            try:
                pygame.mixer.music.load(self.background_music)
                pygame.mixer.music.set_volume(self.config['entities']['sounds']['volume'])
                pygame.mixer.music.play(-1)
                self.music_playing = True
            except pygame.error as e:
                print(f"Error playing music: {e}")

    def stop_background_music(self):
        if self.music_playing:
            pygame.mixer.music.stop()
            self.music_playing = False

    def handle_event(self, event):
        if self.paused:
            result = self.menu.handle_event(event)
            if result:
                if result == "start game": 
                    self.reset_game()
                    self.paused = False
                    self.show_records = False
                    self.show_help = False
                    self.start_background_music()
                elif result == "records":
                    self.show_records = True
                    self.show_help = False
                    self.stop_background_music()
                elif result == "help":
                    self.show_help = True
                    self.show_records = False
                    self.stop_background_music()
                elif result == "exit":
                    self.stop_background_music()
                    return "quit"
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                self.paused = False
                self.show_records = False
                self.show_help = False
                self.start_background_music()
            return None

        if self.game_over:
            if self.input_active:
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN and self.player_name:
                        self.table_records.save_score(self.player_name, self.score)
                        self.input_active = False
                    elif event.key == pygame.K_BACKSPACE:
                        self.player_name = self.player_name[:-1]
                    elif event.unicode.isprintable() and len(self.player_name) < 20:
                        self.player_name += event.unicode
            else:
                if event.type == pygame.KEYDOWN:
                    self.reset_game()
            return None

        if event.type == pygame.QUIT:
            self.stop_background_music()
            return "quit"
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                self.paused = True
                self.stop_background_music()
                return None
        elif event.type == pygame.MOUSEMOTION:
            x, _ = event.pos
            screen_width = self.screen.get_width()
            margin = 50
            if x < margin:
                self.scroll_x -= self.scroll_speed
            elif x > screen_width - margin:
                self.scroll_x += self.scroll_speed
        elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            if self.gun.count_pistols > 0:
                mouse_pos = event.pos
                if self.shot_sound:
                    self.shot_sound.play()
                self.check_hit(mouse_pos)
                self.gun.remove_patron()
                if self.gun.count_pistols == 0:
                    self.waiting_for_reload = True
                    self.reload_timer = 0
        return None

    def check_hit(self, mouse_pos):
        for gif_obj in self.gif_objects[:]:
            rect = gif_obj.current_frame.get_rect(topleft=(gif_obj.x - self.scroll_x, gif_obj.y))
            if rect.collidepoint(mouse_pos):
                self.gif_objects.remove(gif_obj)
                if gif_obj.size < 40:
                    self.score += 20
                else:
                    self.score += 10
                if self.chicken_sound:
                    self.chicken_sound.play()

    def reset_game(self):
        self.score = 0
        self.game_timer = self.level['game_timer']
        self.game_over = False
        self.player_name = ""
        self.input_active = False
        self.gun.count_pistols = self.config['entities']['gun']['initial_pistols']
        self.waiting_for_reload = False
        self.reload_timer = 0
        self.gif_objects = [GifObject(
            os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gif_object']['default_gif']),
            self.bg_width, 350, 50, -self.object_speed, self.bg_width, self.config, layer="foreground"
        )]
        self.start_background_music()

    def draw_help(self):
        self.screen.fill((0, 0, 0))
        help_lines = [
            "Moorhuhn - Shooting Game Help",
            "",
            "Objective: Shoot moving chickens to earn points before time runs out.",
            "Smaller chickens give more points (20), larger ones give 10 points.",
            "",
            "Game Controls:",
            "- Move the mouse to aim the custom cursor.",
            "- Left-click to shoot (limited ammo; auto-reloads when empty).",
            "- Move the mouse to the screen edges to scroll the background.",
            "- Esc: Pause the game to access the menu.",
            "",
            "Menu Controls:",
            "- Up/Down arrows: Navigate menu options (Start, Records, Help, Exit).",
            "- Enter: Select the highlighted option.",
            "- Move the mouse to the screen edges to scroll the menu background.",
            "",
            "High Scores Screen:",
            "- Displays the top 5 scores with player names.",
            
            "",
            "Press Esc to return to the game or menu."
        ]
        y_offset = 50
        for line in help_lines:
            text = self.font.render(line, True, (255, 255, 255))
            self.screen.blit(text, (self.screen.get_width() // 2 - text.get_width() // 2, y_offset))
            y_offset += 30

    def draw(self):
        if self.paused:
            if self.show_records:
                self.table_records.draw(self.screen)
            elif self.show_help:
                self.draw_help()
            else:
                self.menu.draw()
            pygame.display.flip()
            return

        if self.game_over:
            if self.input_active:
                self.screen.fill((0, 0, 0))
                prompt = self.font.render(f"Game Over! Your score: {self.score}", True, (255, 255, 255))
                self.screen.blit(prompt, (self.screen.get_width() // 2 - prompt.get_width() // 2, 100))
                name_prompt = self.font.render("Enter your name:", True, (255, 255, 255))
                self.screen.blit(name_prompt, (self.screen.get_width() // 2 - name_prompt.get_width() // 2, 200))
                name_text = self.font.render(self.player_name, True, (255, 255, 255))
                self.screen.blit(name_text, (self.screen.get_width() // 2 - name_text.get_width() // 2, 250))
            else:
                self.table_records.draw(self.screen)
            pygame.display.flip()
            return

        screen_width, screen_height = self.screen.get_size()
        self.scroll_x = max(0, min(self.scroll_x, self.bg_width - screen_width))
        subsurface_width = min(screen_width, self.bg_width - self.scroll_x)
        subsurface_height = min(screen_height, self.bg_height)

        try:
            layer_scroll_x = self.scroll_x * self.parallax_factors[0]
            layer_scroll_x = max(0, min(layer_scroll_x, self.bg_width - screen_width))
            bg_visible = self.layers[0].subsurface((layer_scroll_x, 0, subsurface_width, subsurface_height))
            self.screen.blit(bg_visible, (0, 0))
        except ValueError as e:
            print(f"Error subsurface for layer 0: {e}")
            self.screen.fill((0, 0, 0))

        for gif_obj in self.gif_objects:
            if gif_obj.layer == "midground":
                gif_obj.draw(self.screen, self.scroll_x)

        try:
            layer_scroll_x = self.scroll_x * self.parallax_factors[1]
            layer_scroll_x = max(0, min(layer_scroll_x, self.bg_width - screen_width))
            bg_visible = self.layers[1].subsurface((layer_scroll_x, 0, subsurface_width, subsurface_height))
            self.screen.blit(bg_visible, (0, 0))
        except ValueError as e:
            print(f"Error subsurface for layer 1: {e}")

        for gif_obj in self.gif_objects:
            if gif_obj.layer == "foreground":
                gif_obj.draw(self.screen, self.scroll_x)

        self.gun.draw_patrons()

        score_text = self.font.render(f"Score: {self.score}", True, (255, 255, 255))
        self.screen.blit(score_text, (10, 10))
        timer_text = self.font.render(f"Time: {int(self.game_timer)}", True, (0, 0, 20))
        self.screen.blit(timer_text, (self.screen.get_width() - 100, 10))

        if self.waiting_for_reload:
            reload_text = self.font.render("Reloading...", True, (255, 255, 255))
            self.screen.blit(reload_text, (self.screen.get_width() // 2 - reload_text.get_width() // 2, self.screen.get_height() - 100))

        mouse_pos = pygame.mouse.get_pos()
        self.screen.blit(self.cursor_img, (mouse_pos[0] - self.cursor_img.get_width() // 2, mouse_pos[1] - self.cursor_img.get_height() // 2))

    def update(self):
        if self.game_over or self.paused:
            return

        dt = self.clock.get_time() / 1000.0
        self.game_timer -= dt
        if self.game_timer <= 0:
            self.game_over = True
            self.input_active = True
            self.stop_background_music()
            return

        if self.waiting_for_reload:
            self.reload_timer += dt
            if self.reload_timer >= self.reload_delay:
                self.gun.refresh_pistols(self.perezaryad_sound)
                self.waiting_for_reload = False
                self.reload_timer = 0

        self.gif_spawn_timer += dt
        if self.gif_spawn_timer >= self.gif_spawn_interval:
            self.gif_spawn_timer = 0
            screen_width, screen_height = self.screen.get_size()
            for _ in range(10):
                size = random.randint(self.config['entities']['gif_object']['min_size'], self.config['entities']['gif_object']['max_size'])
                y = random.randint(0, screen_height - size)
                side = random.choice(["left", "right"])
                if side == "left":
                    x = self.scroll_x - size
                    speed = random.uniform(1, 3)
                    gif_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gif_object']['left_gif'])
                else:
                    x = self.scroll_x + screen_width
                    speed = -random.uniform(1, 3)
                    gif_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gif_object']['default_gif'])
                self.gif_objects.append(GifObject(gif_path, x, y, size, speed, self.bg_width, self.config, layer="foreground"))

        self.special_gif_timer += dt
        if self.special_gif_timer >= self.special_gif_interval:
            self.special_gif_timer = 0
            screen_width, screen_height = self.screen.get_size()
            size = self.config['entities']['gif_object']['special_size']
            y = screen_height - size
            x = random.randint(0, self.bg_width - size)
            speed = 0
            gif_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gif_object']['special_gif'])
            self.gif_objects.append(GifObject(gif_path, x, y, size, speed, self.bg_width, self.config, layer="midground"))

        for gif_obj in self.gif_objects:
            gif_obj.update(dt)

    def start(self):
        self.clock = pygame.time.Clock()
        self.start_background_music()
        running = True
        while running:
            for event in pygame.event.get():
                result = self.handle_event(event)
                if result == "quit":
                    running = False

            self.update()
            self.screen.fill((0, 0, 0))
            self.draw()
            pygame.display.flip()
            self.clock.tick(self.config['game_settings']['fps'])
        self.stop_background_music()