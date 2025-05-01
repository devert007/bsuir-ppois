import pygame
import random
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), './src/models')))
from menu import *
from game.main import *

pygame.init()
WIDTH, HEIGHT = 1200, 800
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Стрельба по курицам")

WHITE = (255, 255, 255)
FPS = 120
clock = pygame.time.Clock()

game = Game(screen) 

menu = Menu(screen)
in_menu = True
show_records = False
show_help = False

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
    clock.tick(FPS)

pygame.quit()
sys.exit()