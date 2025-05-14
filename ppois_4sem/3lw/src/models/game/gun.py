import pygame
import os

class Gun:
    def __init__(self, screen, config):
        self.config = config
        self.count_pistols = config['entities']['gun']['initial_pistols']
        self.screen = screen
        self.pistol_img = None
        self.load_pistol_image()

    def load_pistol_image(self):
        img_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gun']['patron_image'])
        try:
            self.pistol_img = pygame.image.load(img_path).convert()
        except pygame.error as e:
            print(f"Error loading patron image: {e}")
            self.pistol_img = pygame.Surface((80, 50), pygame.SRCALPHA)
            self.pistol_img.fill((255, 0, 0, 128))

    def refresh_pistols(self, perezaryad_sound):
        if perezaryad_sound:
            perezaryad_sound.play()
        self.count_pistols = self.config['entities']['gun']['initial_pistols']

    def remove_patron(self):
        if self.count_pistols > 0:
            self.count_pistols -= 1

    def draw_patrons(self):
        scale = self.config['entities']['gun']['patron_scale']
        array_pistols = [pygame.transform.scale(self.pistol_img, scale) for _ in range(self.count_pistols)]
        for i, pistol in enumerate(array_pistols):
            x = 10 + i * (scale[0] + 10)
            y = self.screen.get_height() - scale[1] - 10
            self.screen.blit(pistol, (x, y))  