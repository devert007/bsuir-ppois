import pygame
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), './src/models')))
from game.game import Game
from menu import Menu

pygame.init()
pygame.mixer.init()

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
from src.utils.config_loader import ConfigLoader
config = ConfigLoader(os.path.join(BASE_DIR, 'config.json')).get_config()

screen = pygame.display.set_mode((config['game_settings']['screen_width'], config['game_settings']['screen_height']))
pygame.display.set_caption("Стрельба по курицам")

game = Game(screen, config)
menu = Menu(screen, config)
in_menu = True
show_records = False
show_help = False

clock = pygame.time.Clock()
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if in_menu:
            result = menu.handle_event(event)
            if result == "start game":
                menu.stop_music()
                game.start()
                in_menu = False
                show_records = False
                show_help = False
            elif result == "records":
                show_records = True
                in_menu = False
                show_help = False
            elif result == "help":
                show_help = True
                in_menu = False
                show_records = False
            elif result == "exit":
                running = False
        elif show_records:
            if event.type == pygame.KEYDOWN:
                in_menu = True
                show_records = False
        elif show_help:
            if event.type == pygame.KEYDOWN:
                in_menu = True
                show_help = False

    screen.fill((0, 0, 0))
    if in_menu:
        menu.draw()
    elif show_records:
        game.table_records.draw(screen)
    elif show_help:
        game.draw_help()

    pygame.display.flip()
    clock.tick(config['game_settings']['fps'])

pygame.mouse.set_visible(True)
pygame.mixer.music.stop()
pygame.quit()
sys.exit()