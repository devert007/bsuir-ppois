import pygame
from PIL import Image
import os

class GifObject:
    def __init__(self, gif_path, x, y, size, speed, bg_width, config, layer="foreground"):
        self.config = config
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
            print(f"Error loading GIF {path}: {e}")
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
                    self.replace_gif(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), self.config['entities']['gif_object']['special_gif_replace']))
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