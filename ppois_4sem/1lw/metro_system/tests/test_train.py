import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from train import Train

class TestTrain(unittest.TestCase):
    def setUp(self):
        self.train = Train()

    def test_initial_state(self):
        self.assertEqual(self.train.speed, 40)
        self.assertEqual(self.train.distance, 0)
        self.assertFalse(self.train.is_running)

    def test_start_train(self):
        self.train.start_train()
        self.assertTrue(self.train.is_running)
        self.assertEqual(self.train.distance, 3)

    def test_calculate_arrival_time(self):
        self.train.distance = 40
        self.train.speed = 40
        self.assertEqual(self.train.calculate_arrival_time(), 60)

if __name__ == '__main__':
    unittest.main()