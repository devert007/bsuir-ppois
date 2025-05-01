import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from passenger import Passenger
from station import Station
from system_metro import MetroSystem
from ticket import Ticket

class TestPassenger(unittest.TestCase):
    def setUp(self):
        self.metro = MetroSystem()
        self.station = Station("Test Station")
        self.metro.stations.append(self.station)
        self.station.is_open = True 
        self.passenger = Passenger("John", 5, self.metro)
        self.station.turnstyle.is_open = False  
    def test_initial_state(self):
        self.assertEqual(self.passenger.name, "John")
        self.assertEqual(self.passenger.money, 5)
        self.assertFalse(self.passenger.has_ticket)
        self.assertEqual(self.passenger.progress, 0)

    def test_go_to_metro_station(self):
        self.passenger.go_to_metro_station("Test Station")
        self.assertEqual(self.passenger.progress, 1)
        self.assertEqual(self.passenger.station.name, "Test Station")

    def test_buy_ticket(self):
        self.passenger.go_to_metro_station("Test Station")
        self.passenger.buy_ticket()
        self.assertEqual(self.passenger.money, 4)
        self.assertTrue(self.passenger.has_ticket)
        self.assertEqual(self.passenger.progress, 2)

    def test_go_through_turnstile(self):
        self.passenger.go_to_metro_station("Test Station")
        self.passenger.buy_ticket()
        self.station.turnstyle.check_ticket = lambda p: True 
        self.station.turnstyle.toggle_open = lambda: None 
        
        self.passenger.go_through_turnstyle()
        self.assertEqual(self.passenger.progress, 3)

    def test_check_schedule_and_board(self):
        self.passenger.go_to_metro_station("Test Station")
        self.passenger.buy_ticket()
        self.station.turnstyle.check_ticket = lambda p: True
        self.station.turnstyle.toggle_open = lambda: None
        self.passenger.go_through_turnstyle()
        self.station.platform.current_train = None
        self.station.schedule.show_next_arrival = lambda: None
        self.station.train_departs = lambda: None
        self.station.train_arrives = lambda: None
        self.passenger.check_schedule_and_board()
        self.assertEqual(self.passenger.progress, 3)
    def test_check_schedule_and_board_not_through_turnstile(self):
        self.passenger.go_to_metro_station("Test Station")
        self.passenger.buy_ticket()
        self.station.platform.current_train = type('', (), {"boarding_passengers": lambda: True})()
        self.passenger.check_schedule_and_board()
        self.assertEqual(self.passenger.progress, 2)
if __name__ == '__main__':
    unittest.main()
