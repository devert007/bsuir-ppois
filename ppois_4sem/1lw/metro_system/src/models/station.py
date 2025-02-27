from datetime import datetime
from schedule import Schedule
from station_platform import Platform
from turnstyle import TurnStyle
from train import Train

class Station:
    def __init__(self, name: str) -> None:
        self.name = name
        self.platform = Platform()
        self.schedule = Schedule()
        self.is_open = False 
        self.turnstyle = TurnStyle()
        self.train = Train()
        self.platform.open_platform()
        self.update_station_status()

    def update_station_status(self) -> None:
        current_time = datetime.now()
        current_hour = current_time.hour
        if 5 <= current_hour < 24 or current_hour == 0:  
            self.is_open = True
        else:
            self.is_open = False

    def train_arrives(self) -> None:
        if self.is_open:
            self.platform.is_empty = False
            self.platform.current_train = self.train
            self.schedule.train_arrival()
            print(f"Поезд прибыл на станцию {self.name}")
        else:
            print(f"Станция {self.name} закрыта, поезд не может прибыть")

    def train_departs(self) -> None:
        if self.is_open:
            self.platform.is_empty = True
            self.platform.current_train = None
            self.train.start_train()
            self.schedule.train_departure()
            self.schedule.update_schedule(self.train)
        else:
            print(f"Станция {self.name} закрыта, поезд не может отправиться")