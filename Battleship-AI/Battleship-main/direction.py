# 2021.03.16
# Matt Bonanno
# Copyright (c) 2021

from enum import IntEnum


class Direction(IntEnum):
    NORTH = 1
    SOUTH = 2
    EAST = 3
    WEST = 4


class Orientation(IntEnum):
    HORIZONTAL = 1  # When the ship is along the x axis.
    VERTICAL = 0  # when the ship is along the y axis.

    @staticmethod
    def valueOf(value: int):
        if value == 0:
            return Orientation.VERTICAL
        elif value == 1:
            return Orientation.HORIZONTAL
