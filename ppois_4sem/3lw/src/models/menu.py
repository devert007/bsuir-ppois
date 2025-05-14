import pygame
import os

class Menu:
    def __init__(self, screen, config):
        self.screen = screen
        self.config = config
        self.font = pygame.font.SysFont(config['game_settings']['font'], config['game_settings']['menu_font_size'], bold=True)
        self.title_font = pygame.font.SysFont(config['game_settings']['title_font'], config['game_settings']['title_font_size'], bold=True)
        self.options = ["start game", "records", "help", "exit"]
        self.title_text = self.title_font.render("Moorhuhn", True, (255, 255, 255))
        self.selected = 0
        self.scroll_x = 0
        self.scroll_speed = config['levels']['1']['scroll_speed']
        self.load_background()
        self.load_music()

    def load_background(self):
        img_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "img", "back.jpg")
        try:
            self.background = pygame.image.load(img_path).convert()
            self.background = pygame.transform.scale(self.background, (self.config['entities']['background']['bg_width'], self.config['entities']['background']['bg_height']))
        except pygame.error as e:
            print(f"Error loading background: {e}")
            self.background = pygame.Surface((self.config['entities']['background']['bg_width'], self.config['entities']['background']['bg_height']))
        self.bg_width = self.background.get_width()
        self.bg_height = self.background.get_height()

    def load_music(self):
        music_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), self.config['entities']['sounds']['menu_music'])
        try:
            pygame.mixer.music.load(music_path)
            pygame.mixer.music.set_volume(self.config['entities']['sounds']['volume'])
            pygame.mixer.music.play(-1)
        except pygame.error as e:
            print(f"Error loading menu music: {e}")

    def stop_music(self):
        pygame.mixer.music.stop()

    def draw(self):
        screen_width, screen_height = self.screen.get_size()
        self.scroll_x = max(0, min(self.scroll_x, self.bg_width - screen_width))
        try:
            bg_visible = self.background.subsurface((self.scroll_x, 0, screen_width, screen_height))
            self.screen.blit(bg_visible, (0, 0))
        except ValueError as e:
            print(f"Error drawing background: {e}")
            self.screen.fill((0, 0, 0))

        title_width, title_height = self.title_text.get_size()
        title_x = (screen_width - title_width) // 2
        title_y = 100
        self.screen.blit(self.title_text, (title_x, title_y))

        for i, option in enumerate(self.options):
            color = (255, 255, 255) if i == self.selected else (100, 100, 100)
            text_surface = self.font.render(option, True, color)
            text_x = (screen_width - text_surface.get_width()) // 2
            self.screen.blit(text_surface, (text_x, 300 + i * 60))

    def handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                self.selected = (self.selected - 1) % len(self.options)
            elif event.key == pygame.K_DOWN:
                self.selected = (self.selected + 1) % len(self.options)
            elif event.key == pygame.K_RETURN:
                return self.options[self.selected]
        elif event.type == pygame.MOUSEMOTION:
            x, _ = event.pos
            screen_width = self.screen.get_width()
            margin = 50
            if x < margin:
                self.scroll_x -= self.scroll_speed
            elif x > screen_width - margin:
                self.scroll_x += self.scroll_speed
        return None