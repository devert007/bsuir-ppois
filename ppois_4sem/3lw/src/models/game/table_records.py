import pygame
import os
import json

class TableRecords:
    def __init__(self, config):
        self.config = config
        self.json_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), "high_scores.json")
        self.dictionary = self.load_scores()
        self.font = pygame.font.SysFont(config['game_settings']['font'], config['game_settings']['font_size'])

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
            print(f"Error saving JSON: {e}")

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

        prompt = self.font.render("Press esc key to continue", True, (255, 255, 255))
        screen.blit(prompt, (screen.get_width() // 2 - prompt.get_width() // 2, 400))