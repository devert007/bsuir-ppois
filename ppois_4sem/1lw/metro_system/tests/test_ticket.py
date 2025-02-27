import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from ticket import Ticket

class TestTicket(unittest.TestCase):
    def setUp(self):
        self.ticket = Ticket()

    def test_initial_state(self):
        self.assertEqual(self.ticket.price, 1)
        self.assertTrue(self.ticket.is_valid)

if __name__ == '__main__':
    unittest.main()