
import pygame
import os
root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
class Menu:
    def __init__(self, screen):
        self.screen = screen
        self.font = pygame.font.SysFont("Arial", 48,bold=True)
        self.title_font = pygame.font.SysFont("Verdana", 104, bold=True)
        self.options = ["start game", "records", "help", "exit"]
        self.title_text = self.title_font.render("Moorhuhn", True, (255, 255, 255))  
        self.selected = 0
        img_path = os.path.join(root, "img", "back.jpg")
        self.layer_1=pygame.image.load(img_path).convert()
        self.background =pygame.transform.scale(self.layer_1, [2400,800])
        self.bg_width = self.background.get_width()
        self.bg_height = self.background.get_height()
        self.scroll_x = 0
        self.scroll_speed = 5  
        self.menu_sound =  pygame.mixer.Sound(os.path.join(root, "sound", "menu.mp3"))
        self.menu_sound.set_volume(0.1)
        music_path = os.path.join(root, "sound", "menu.mp3")
        pygame.mixer.music.load(music_path)  
        pygame.mixer.music.set_volume(0.1) 
        pygame.mixer.music.play(loops=-1)
    def stop_music(self):
        pygame.mixer.music.stop()
    
    def draw(self):
        screen_width, screen_height = self.screen.get_size()

        self.scroll_x = max(0, min(self.scroll_x, self.bg_width - screen_width))

        bg_visible = self.background.subsurface((self.scroll_x, 0, screen_width, screen_height))
        self.screen.blit(bg_visible, (0, 0))
        title_width, title_height = self.title_text.get_size()
        title_x = (screen_width - title_width) // 2  
        title_y = 100  
        self.screen.blit(self.title_text, (title_x, title_y))
        for i, option in enumerate(self.options):
            color = (255, 255, 255) if i == self.selected else (100, 100, 100)
            text_surface = self.font.render(option, True, color)
            self.screen.blit(text_surface, (500, 300 + i * 60))
       
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
