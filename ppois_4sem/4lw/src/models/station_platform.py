class Platform:
    def __init__(self):
        self.is_closed = True
        self.is_empty = True
        self.current_train = None

    def open_platform(self):
        if self.is_closed:
            self.is_closed = False
            print("Платформа открыта")