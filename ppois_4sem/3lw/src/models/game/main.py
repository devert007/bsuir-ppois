import pygame
import os
import json
from PIL import Image
import random
from menu import *

BASE_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

class TableRecords:
    def __init__(self):
        self.json_path = os.path.join(BASE_DIR, "high_scores.json")
        self.dictionary = self.load_scores()
        self.font = pygame.font.SysFont("arial", 24)

    def load_scores(self):
        try:
            with open(self.json_path, "r") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def save_score(self, player_name, score):
        self.dictionary[player_name] = score
        try:
            with open(self.json_path, "w") as f:
                json.dump(self.dictionary, f, indent=4)
        except Exception as e:
            print(f"Ошибка сохранения JSON: {e}")

    def get_top_scores(self, limit=5):
        sorted_scores = sorted(self.dictionary.items(), key=lambda x: x[1], reverse=True)
        return sorted_scores[:limit]

    def draw(self, screen):
        screen.fill((0, 0, 0))
        title = self.font.render("High Scores", True, (255, 255, 255))
        screen.blit(title, (screen.get_width() // 2 - title.get_width() // 2, 50))

        top_scores = self.get_top_scores()
        for i, (name, score) in enumerate(top_scores):
            text = self.font.render(f"{i+1}. {name}: {score}", True, (255, 255, 255))
            screen.blit(text, (screen.get_width() // 2 - text.get_width() // 2, 100 + i * 40))

        prompt = self.font.render("Press any key to continue", True, (255, 255, 255))
        screen.blit(prompt, (screen.get_width() // 2 - prompt.get_width() // 2, 400))

class Gun:
    def __init__(self, screen):
        self.count_pistols = 5
        self.screen = screen

    def refresh_pistols(self, perezaryad_sound):
        perezaryad_sound.play()
        self.count_pistols += 5

    def remove_patron(self):
        if self.count_pistols > 0:
            self.count_pistols -= 1

    def draw_patrons(self):
        img_path = os.path.join(BASE_DIR, "img", "patron.png")
        self.pistol_1 = pygame.image.load(img_path).convert()
        self.array_pistols = [pygame.transform.scale(self.pistol_1, (80, 50)) for _ in range(self.count_pistols)]
        for i, pistol in enumerate(self.array_pistols):
            x = 10 + i * (90)
            y = self.screen.get_height() - 60
            self.screen.blit(pistol, (x, y))

class GifObject:
    def __init__(self, gif_path, x, y, size, speed, bg_width, layer="foreground"):
        self.gif_path = gif_path
        self.frames = self.load_gif_frames(gif_path)
        self.frames = [pygame.transform.scale(frame, (size, size)) for frame in self.frames]
        self.x = x
        self.y = y
        self.size = size
        self.frame_index = 0
        self.animation_timer = 0
        self.animation_speed = 0.1
        self.current_frame = self.frames[0]
        self.speed = speed
        self.bg_width = bg_width
        self.played_once = False
        self.layer = layer  

    def load_gif_frames(self, path):
        frames = []
        try:
            with Image.open(path) as img:
                for frame in range(img.n_frames):
                    img.seek(frame)
                    frame_img = img.convert("RGBA")
                    mode = frame_img.mode
                    size = frame_img.size
                    data = frame_img.tobytes()
                    pygame_img = pygame.image.fromstring(data, size, mode)
                    frames.append(pygame_img)
        except Exception as e:
            print(f"Ошибка загрузки GIF {path}: {e}")
            frames.append(pygame.image.load(path))
        return frames

    def replace_gif(self, new_gif_path):
        self.gif_path = new_gif_path
        self.frames = self.load_gif_frames(new_gif_path)
        self.frames = [pygame.transform.scale(frame, (self.size, self.size)) for frame in self.frames]
        self.frame_index = 0
        self.current_frame = self.frames[0]
        self.played_once = False

    def update(self, dt):
        self.animation_timer += self.animation_speed * dt * 60
        if self.animation_timer >= 1:
            self.animation_timer = 0
            self.frame_index += 1
            if self.frame_index >= len(self.frames):
                self.frame_index = 0
                if "moorhuhn_001.gif" in self.gif_path:
                    self.replace_gif(os.path.join(BASE_DIR, "img", "moorhuhn_002.gif"))
            self.current_frame = self.frames[self.frame_index]
        
        self.x += self.speed * dt * 60
        if self.speed > 0:
            if self.x > self.bg_width:
                self.x = -self.current_frame.get_width()
        else:
            if self.x < -self.current_frame.get_width():
                self.x = self.bg_width

    def draw(self, screen, scroll_x):
        screen.blit(self.current_frame, (self.x - scroll_x, self.y))

class Game:
    def __init__(self, screen):
        self.screen = screen
        self.scroll_x = 0
        self.scroll_speed = 5
        self.object_speed = 3
        self.bg_width = 2400
        self.object_x = self.bg_width
        self.gun = Gun(screen)
        self.score = 0
        self.game_timer = 120
        self.game_over = False
        self.player_name = ""
        self.input_active = False
        self.paused = False
        self.show_records = False
        self.show_help = False
        self.table_records = TableRecords()
        self.menu = Menu(screen)
        self.font = pygame.font.SysFont("arial", 24)
        self.music_playing = False  
        pygame.mouse.set_visible(False)
        pygame.mixer.init()
        self.layers = []
        
        for img_name in ["b1.png", "b3.png"]:
            img_path = os.path.join(BASE_DIR, "img", img_name)
            try:
                layer = pygame.image.load(img_path).convert_alpha()
                self.layers.append(pygame.transform.scale(layer, (2400, 800)))
            except pygame.error as e:
                print(f"Ошибка загрузки {img_name}: {e}")
                self.layers.append(pygame.Surface((2400, 800), pygame.SRCALPHA))
        self.bg_width = self.layers[0].get_width()
        self.bg_height = self.layers[0].get_height()
        
        self.parallax_factors = [0.7, 1.0]  

        cursor_img_path = os.path.join(BASE_DIR, "img", "cursor.png")
        try:
            self.shot_sound = pygame.mixer.Sound(os.path.join(BASE_DIR, "sound", "boom.mp3"))
            self.chicken_sound = pygame.mixer.Sound(os.path.join(BASE_DIR, "sound", "chicken.mp3"))
            self.perezaryad_sound = pygame.mixer.Sound(os.path.join(BASE_DIR, "sound", "perezaryad.mp3"))
           
            self.background_music = os.path.join(BASE_DIR, "sound", "game.mp3")
            pygame.mixer.music.load(self.background_music)
            self.cursor_img = pygame.image.load(cursor_img_path).convert_alpha()
            self.cursor_img = pygame.transform.scale(self.cursor_img, (32, 32))
        except pygame.error as e:
            print(f"Ошибка загрузки cursor.png, звуков или музыки: {e}")
            self.shot_sound = None
            self.chicken_sound = None
            self.perezaryad_sound = None
            self.background_music = None
            self.cursor_img = pygame.Surface((32, 32), pygame.SRCALPHA)
            self.cursor_img.fill((255, 0, 0, 128))

        gif_path = os.path.join(BASE_DIR, "img", "moorhuhn0477.gif")
        self.gif_objects = [GifObject(gif_path, self.object_x, 350, 50, -self.object_speed, self.bg_width, layer="foreground")]
        self.gif_spawn_timer = 0
        self.gif_spawn_interval = 10
        self.reload_timer = 0
        self.reload_delay = 2
        self.waiting_for_reload = False
        self.special_gif_timer = 0
        self.special_gif_interval = 30

    def start_background_music(self):
        if self.background_music and not self.music_playing:
            try:
                pygame.mixer.music.play(-1)  
                self.music_playing = True
                print("Background music started")
            except pygame.error as e:
                print(f"Ошибка воспроизведения музыки: {e}")

    def stop_background_music(self):
        if self.music_playing:
            pygame.mixer.music.stop()
            self.music_playing = False
            print("Background music stopped")

    def handle_event(self, event):
        if self.paused:
            result = self.menu.handle_event(event)
            if result:
                if result == "continue":
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
                try:
                    if self.shot_sound:
                        self.shot_sound.play()
                finally:
                    self.check_hit(mouse_pos)
                self.gun.remove_patron()
                print(f"Осталось патронов: {self.gun.count_pistols}")
                if self.gun.count_pistols == 0:
                    self.waiting_for_reload = True
                    self.reload_timer = 0
            else:
                print("Патроны закончились! Ожидайте перезарядки...")

        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            self.gif_objects[0].x -= self.object_speed
        if keys[pygame.K_RIGHT]:
            self.gif_objects[0].x += self.object_speed
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
                print("Попадание!")

    def reset_game(self):
        self.score = 0
        self.game_timer = 120
        self.game_over = False
        self.player_name = ""
        self.input_active = False
        self.gun.count_pistols = 5
        self.waiting_for_reload = False
        self.reload_timer = 0
        self.gif_objects = [GifObject(
            os.path.join(BASE_DIR, "img", "moorhuhn0477.gif"),
            self.bg_width, 350, 50, -self.object_speed, self.bg_width, layer="foreground"
        )]
        self.start_background_music()  

    def draw_help(self):
        self.screen.fill((0, 0, 0))
        help_text = self.font.render("Use mouse to shoot, Esc to pause, Left/Right to move first target", True, (255, 255, 255))
        self.screen.blit(help_text, (self.screen.get_width() // 2 - help_text.get_width() // 2, 300))
        prompt = self.font.render("Press Esc to return to menu", True, (255, 255, 255))
        self.screen.blit(prompt, (self.screen.get_width() // 2 - prompt.get_width() // 2, 400))

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
            print(f"Ошибка subsurface для слоя 0: {e}")
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
            print(f"Ошибка subsurface для слоя 1: {e}")

        
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
        mouse_x = mouse_pos[0]
        mouse_y = mouse_pos[1]
        new_tuple = (mouse_x - 10, mouse_y - 10)
        self.screen.blit(self.cursor_img, new_tuple)

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
                print("Патроны перезаряжены!")

        self.gif_spawn_timer += dt
        if self.gif_spawn_timer >= self.gif_spawn_interval:
            self.gif_spawn_timer = 0
            screen_width, screen_height = self.screen.get_size()
            for _ in range(4):
                size = random.randint(30, 100)
                y = random.randint(0, screen_height - size)
                side = random.choice(["left", "right"])
                if side == "left":
                    x = self.scroll_x - size
                    speed = random.uniform(1, 3)
                    gif_path = os.path.join(BASE_DIR, "img", "moorhuhn0477left.gif")
                else:
                    x = self.scroll_x + screen_width
                    speed = -random.uniform(1, 3)
                    gif_path = os.path.join(BASE_DIR, "img", "moorhuhn0477.gif")
                self.gif_objects.append(GifObject(gif_path, x, y, size, speed, self.bg_width, layer="foreground"))

        self.special_gif_timer += dt
        if self.special_gif_timer >= self.special_gif_interval:
            self.special_gif_timer = 0
            screen_width, screen_height = self.screen.get_size()
            size = 200
            y = screen_height - size
            x = random.randint(0, self.bg_width - size)
            speed = 0
            gif_path = os.path.join(BASE_DIR, "img", "moorhuhn_001.gif")
            self.gif_objects.append(GifObject(gif_path, x, y, size, speed, self.bg_width, layer="midground"))

        for gif_obj in self.gif_objects:
            gif_obj.update(dt)

    def start(self):
        running = True
        self.clock = pygame.time.Clock()
        self.start_background_music()  
        while running:
            for event in pygame.event.get():
                result = self.handle_event(event)
                if result == "quit":
                    running = False

            self.update()
            self.screen.fill((0, 0, 0))
            self.draw()
            pygame.display.flip()
            self.clock.tick(60)
        self.stop_background_music() 