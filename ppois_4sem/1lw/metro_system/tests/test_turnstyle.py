import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from turnstyle import TurnStyle
from passenger import Passenger
from system_metro import MetroSystem

class TestTurnStyle(unittest.TestCase):
    def setUp(self):
        self.turnstyle = TurnStyle()
        self.metro = MetroSystem()
        self.passenger = Passenger("Alice", 5, self.metro)

    def test_initial_state(self):
        self.assertFalse(self.turnstyle.open)

    def test_toggle_open(self):
        self.turnstyle.toggle_open()
        self.assertTrue(self.turnstyle.open)
        self.turnstyle.toggle_open()
        self.assertFalse(self.turnstyle.open)

    def test_check_ticket(self):
        self.passenger.has_ticket = True
        self.passenger.ticket = type('Ticket', (), {'is_valid': True})()
        self.assertTrue(self.turnstyle.check_ticket(self.passenger))

if __name__ == '__main__':
    unittest.main()