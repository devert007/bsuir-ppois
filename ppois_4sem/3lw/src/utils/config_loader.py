import json
import os

class ConfigLoader:
    def __init__(self, config_path):
        self.config = self.load_config(config_path)

    def load_config(self, config_path):
        try:
            with open(config_path, 'r') as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError) as e:
            print(f"Error loading config: {e}")
            return {}

    def get_config(self):
        return self.config