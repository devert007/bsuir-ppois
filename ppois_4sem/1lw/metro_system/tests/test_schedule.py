import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from schedule import Schedule
from train import Train
from datetime import datetime, timedelta

class TestSchedule(unittest.TestCase):
    def setUp(self):
        self.schedule = Schedule()
        self.train = Train()

    def test_initial_state(self):
        self.assertEqual(self.schedule.arrival_times, [])
        self.assertIsNone(self.schedule.last_departure)

    def test_update_schedule(self):
        self.train.is_running = True
        self.schedule.update_schedule(self.train)
        self.assertEqual(len(self.schedule.arrival_times), 1)
        expected_time = datetime.now() + timedelta(minutes=2)
        self.assertAlmostEqual(self.schedule.arrival_times[0].timestamp(), 
                             expected_time.timestamp(), delta=60)

    def test_train_departure(self):
        self.schedule.train_departure()
        self.assertIsNotNone(self.schedule.last_departure)

if __name__ == '__main__':
    unittest.main()