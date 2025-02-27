from datetime import datetime, timedelta

class Schedule:
    def __init__(self):
        self.arrival_times = []  # Список времен прибытия в формате datetime
        self.last_departure = None

    def update_schedule(self, train):
        if train.is_running:
            # Берем текущее время и добавляем 2 минуты
            current_time = datetime.now()
            arrival_time = current_time + timedelta(minutes=2)
            self.arrival_times.append(arrival_time)
            print(f"Расписание обновлено. Следующий поезд прибудет в {arrival_time.strftime('%H:%M')}")

    def train_departure(self):
        self.last_departure = datetime.now()
        self.arrival_times.pop(0) if self.arrival_times else None
        print(f"Поезд отправился в {self.last_departure.strftime('%H:%M')}")

    def train_arrival(self):
        self.arrival_times = []
        print("Поезд прибыл, расписание сброшено")

    def show_next_arrival(self):
        if self.arrival_times:
            next_time = self.arrival_times[0]
            current_time = datetime.now()
            minutes_left = (next_time - current_time).total_seconds() / 60
            if minutes_left >= 0:
                print(f"Следующий поезд прибудет в {next_time.strftime('%H:%M')} (через {int(minutes_left)} минут)")
                return int(minutes_left)
            else:
                print("Поезд уже должен был прибыть, обновите расписание")
                self.arrival_times.pop(0)  # Удаляем просроченное время
                return 0
        else:
            print("Расписание пусто")
            return None