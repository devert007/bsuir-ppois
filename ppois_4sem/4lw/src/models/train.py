class Train:
    def __init__(self):
        self.speed = 40  
        self.distance = 0 
        self.is_running = False
        self.current_station = None

    def start_train(self):
        self.distance = 3
        self.is_running = True

    def stop_train(self):
        self.is_running = False
        self.distance = 0
        self.current_station = None

    def boarding_passengers(self):
        if self.is_running:
            print("Посадка пассажиров выполняется")
            return True
        return False

    def calculate_arrival_time(self):
        if self.distance > 0 and self.speed > 0:
            time_hours = self.distance / self.speed
            time_minutes = int(time_hours * 60)
            return time_minutes
        return 0