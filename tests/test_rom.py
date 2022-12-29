#!/usr/bin/env python3

import unittest
import struct
from os import path, environ


class TestRom(unittest.TestCase):
    """Test that the generated game ROM is correct."""

    ROM_SIZE = int(environ.get("ROM_MAX", 0), 16)

    @classmethod
    def setUpClass(cls):
        with open(path.join("..", "bin", "game.rom"), "rb") as fd:
            cls.data = fd.read()

        with open(path.join("..", "game", "build", "game.map"), "rb") as fd:
            game_map = fd.readlines()

        cls.main_init = 0
        for line in game_map:
            if b"_main_init" in line:
                cls.main_init = int(line.split()[0], 16)
                break

    def test_header_magic(self):
        self.assertEqual(self.data[:2], b"AB")

    def test_size(self):
        self.assertEqual(len(self.data), self.ROM_SIZE)

    def test_header_main_init_address(self):
        self.assertEqual(struct.unpack("<H", self.data[2:4]), (self.main_init,))


if __name__ == "__main__":
    unittest.main()
