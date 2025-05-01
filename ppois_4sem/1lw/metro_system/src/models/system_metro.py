from station import Station
from passenger import Passenger
import sys
import json


class MetroSystem:
    def __init__(self) -> None:
        self.stations = []
        self.branches = []
        self.passenger = None  

    def add_station(self,station_name) -> Station:
        new_station = Station(station_name)
        self.stations.append(new_station)
        print(f"Станция {station_name} добавлена.")
        return new_station

    def find_station(self, station_name: str) -> Station | None:  
        for station in self.stations:
            if station.name == station_name:
                return station
        print(f"Станция {station_name} не найдена")
        return None

    def create_passenger(self, name: str, money: int) -> None:
        self.passenger = Passenger(name, money, self)
        print(f"Пассажир {name} создан.")

    def save_state(self, filename: str = "metro_state.json") -> None:
        if not hasattr(self, "passenger"):
            self.passenger = None  
        data = {
            "stations": [{"name": s.name} for s in self.stations],
            "passenger": {
                "name": self.passenger.name,
                "money": self.passenger.money,
                "progress": self.passenger.progress,
                "station": self.passenger.station.name if self.passenger.station else None
            } if self.passenger else None
        }
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)
        print("Состояние сохранено.")

    def load_state(self, filename: str = "metro_state.json") -> None:
        try:
            with open(filename, "r", encoding="utf-8") as f:
                data = json.load(f)
                self.stations = [Station(s["name"]) for s in data["stations"]]
                if data["passenger"]:
                    self.passenger = Passenger(data["passenger"]["name"], data["passenger"]["money"], self)
                    if data["passenger"]["station"]:
                        self.passenger.station = self.find_station(data["passenger"]["station"])
                    self.passenger.progress = data["passenger"]["progress"]
            print("Состояние загружено.")
        except FileNotFoundError:
            print("Файл состояния не найден, начинаем с нуля.")


def main() -> None:
    metro_system = MetroSystem()
    print("Система метро загружена.")

    while True:
        command = input("Введите команду (help для списка): ").strip().lower()
        if command == "exit":
            print("До свидания!")
            sys.exit(0)
        elif command == "save":
            metro_system.save_state()
        elif command == "load":
            metro_system.load_state()
        elif command == "add_station":
            station_name = input("Введите имя станции: ")
            metro_system.add_station(station_name)
        elif command == "create_passenger":
            name = input("Введите имя пассажира: ")
            metro_system.create_passenger(name, 5)
        elif command == "go_to_station":
            if metro_system.passenger:  
                station_name = input("Введите имя станции: ")
                metro_system.passenger.go_to_metro_station(station_name)
            else:
                print("Сначала создайте пассажира (create_passenger).")
        elif command == "buy_ticket":
            if metro_system.passenger:
                metro_system.passenger.buy_ticket()
            else:
                print("Сначала создайте пассажира (create_passenger).")
        elif command == "pass_turnstile":
            if metro_system.passenger:
                metro_system.passenger.go_through_turnstyle()
            else:
                print("Сначала создайте пассажира (create_passenger).")
        elif command == "board_train":
            if metro_system.passenger:
                metro_system.passenger.check_schedule_and_board()
            else:
                print("Сначала создайте пассажира (create_passenger).")
        elif command == "help":
            print("""
        Команды:
        - exit: Выйти из программы
        - save: Сохранить текущее состояние
        - load: Загрузить текущее состояние
        - add_station: Добавить новую станцию
        - create_passenger: Создать пассажира
        - go_to_station: Зайти на станцию
        - buy_ticket: Купить билет
        - pass_turnstile: Пройти через турникет
        - board_train: Проверить расписание и сесть в поезд
        - help: Показать этот список
            """)
        else:
            print("Неизвестная команда. Введите 'help' для списка.")


if __name__ == "__main__":
    main()
