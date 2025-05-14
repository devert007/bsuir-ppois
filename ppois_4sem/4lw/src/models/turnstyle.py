class TurnStyle:
    def __init__(self):
        self.open = False

    def toggle_open(self):
        self.open = not self.open
        return self.open

    def check_ticket(self, passenger):
        return passenger.has_ticket and passenger.ticket.is_valid