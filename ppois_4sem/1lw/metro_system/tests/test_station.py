import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from station import Station
from datetime import datetime

class TestStation(unittest.TestCase):
    def setUp(self):
        self.station = Station("Central")

    def test_initial_state(self):
        self.assertEqual(self.station.name, "Central")
        self.assertFalse(self.station.platform.is_closed)
        self.assertTrue(self.station.platform.is_empty)

    def test_update_station_status(self):
        self.station.update_station_status()
        current_hour = datetime.now().hour
        expected = 5 <= current_hour < 24 or current_hour == 0
        self.assertEqual(self.station.is_open, expected)

    def test_train_arrives(self):
        self.station.is_open = True
        self.station.train_arrives()
        self.assertFalse(self.station.platform.is_empty)
        self.assertIsNotNone(self.station.platform.current_train)

if __name__ == '__main__':
    unittest.main()