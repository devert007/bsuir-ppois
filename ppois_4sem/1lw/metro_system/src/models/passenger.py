from ticket import Ticket
import time

class Passenger:
    def __init__(self, name: str, money: int, metro_system) -> None:
        self.name = name
        self.money = money
        self.has_ticket = False
        self.ticket = None
        self.metro_system = metro_system
        self.station = None
        self.progress = 0  # 0: не на станции, 1: на станции, 2: купил билет, 3: прошел турникет, 4: ждет поезд

    def go_to_metro_station(self, station_name: str) -> None:
        if self.progress == 0:
            self.station = self.metro_system.find_station(station_name)
            if self.station.is_open:
                self.progress = 1
                print(f"{self.name} входит на станцию {station_name}.")
            else:
                print(f"Станция {station_name} закрыта.")
        else:
            print(f"{self.name} уже находится на станции или дальше в процессе.")

    def buy_ticket(self) -> None:
        if self.progress != 1:
            print(f"{self.name} должен сначала зайти на станцию.")
            return
        print("Стоимость билета - 1 BYN")
        if self.money < 1:
            print(f"{self.name} не хватает денег для покупки билета.")
        self.money -= 1
        self.has_ticket = True
        self.ticket = Ticket()
        self.progress = 2
        print(f"{self.name} купил билет за {self.ticket.price} BYN.")

    def go_through_turnstyle(self) -> None:
        if self.progress != 2:
            print(f"{self.name} должен сначала купить билет.")
            return
        if self.station.turnstyle.check_ticket(self):
            self.station.turnstyle.toggle_open()
            print(f"{self.name} прошел через турникет на станции {self.station.name}.")
            self.station.turnstyle.toggle_open()
            self.progress = 3
        else:
            print(f"{self.name}: билет не актуален или отсутствует.")

    def check_schedule_and_board(self) -> None:
        if self.progress != 3:
            print(f"{self.name} должен сначала пройти через турникет.")
            return
        if self.station.platform.current_train:
            if self.station.platform.current_train.boarding_passengers():
                self.progress = 4
                print(f"{self.name} сел в поезд.")
            else:
                print(f"{self.name}: поезд не готов к посадке.")
        else:
            print(f"Поезда на станции {self.station.name} нет.")
            minutes = self.station.schedule.show_next_arrival()
            if minutes is not None:
                if minutes > 0:
                    print(f"Ожидание поезда {minutes} минут...")
                    time.sleep(minutes * 60) 
                self.station.train_arrives()
                if self.station.platform.current_train.boarding_passengers():
                    self.progress = 4
                    print(f"{self.name} сел в поезд после ожидания.")
            else:
                if minutes is not None:
                    self.station.train_departs()  
                    minutes = self.station.schedule.show_next_arrival()
                    print(f"Ожидание поезда {minutes} минут...")
                    time.sleep(minutes * 60)
                    self.station.train_arrives()
                    if self.station.platform.current_train.boarding_passengers():
                        self.progress = 4
                        print(f"{self.name} сел в поезд после ожидания.")
                else:
                    print(f"{self.name}: нет информации о следующем поезде.")