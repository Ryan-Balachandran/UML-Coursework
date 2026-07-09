from __future__ import annotations
from math import floor
import random
from typing import List, Tuple, Any
import constants
from direction import Direction, Orientation


class Fleet(object):
    def __init__(self, board):
        self.numShips: int = len(constants.ALL_SHIPS)
        self.board = board
        self.fleetRoster: List[Ship] = []

    def populate(self):
        for ship in constants.ALL_SHIPS:
            self.fleetRoster.append(Ship(ship[0], ship[1], self.board))

    def placeShipsRandomly(self):
        for ship in self.fleetRoster:
            illegallyPlaced = True
            while illegallyPlaced:
                randomX = random.randint(0, 9)
                randomY = random.randint(0, 9)
                randomDir: Orientation = Orientation.valueOf(random.randint(0, 1))
                if ship.isLegal(randomX, randomY, randomDir):
                    illegallyPlaced = False
                    ship.initalize(randomX, randomY, randomDir)

    def checkAllShipsSunk(self):
        for ship in self.fleetRoster:
            if not ship.isSunk():
                return False
        return True

    def getShipAtCoord(self, x, y):
        for ship in self.fleetRoster:
            if ship.orientation == Orientation.VERTICAL:
                if y == ship.coords[1] and ship.coords[0] <= x < ship.coords[0] + ship.length:
                    return ship
            else:
                if x == ship.coords[0] and ship.coords[1] <= y < ship.coords[1] + ship.length:
                    return ship

class Ship(object):
    orientation: Orientation
    coords: tuple[int, int]

    # origin = origin coordinate
    def __init__(self, type: str, length: int, board):
        self.type: str = type
        self.length: int = length
        self.sunk = False
        self.maxDamage = length
        self.damage = 0
        self.aliveSections = length
        self.board = board

    # TODO FIX THIS
    def hit(self, coord: Tuple[int, int]):
        self.sections[self.sections.index(((coord[0], coord[1]), True))][2] = False
        self.aliveSections -= 1

        # TODO: add hit and miss function from GameBoard

    def addDamage(self):
        self.damage = self.damage + 1

    def isSunk(self):
        return self.damage >= self.maxDamage

    def checkSunk(self) -> bool:
        return self.damage >= self.maxDamage

    def isInGrid(self, x, y, orientation) -> bool:
        if orientation == Orientation.VERTICAL:
            return x + self.length <= 10
        else:
            return y + self.length <= 10

    def isLegal(self, x, y, dir: Orientation):
        if self.isInGrid(x, y, dir):
            for i in range(self.length):
                if dir == Orientation.VERTICAL:
                    if self.board.grid[x + i][y].ship:
                        return False
                else:
                    if self.board.grid[x][y + i].ship:
                        return False
            return True
        else:
            return False

    def initalize(self, x: int, y: int, dir: Orientation):
        self.coords = (x, y)
        self.orientation = dir
        for i in range(self.length):
            if dir == Orientation.VERTICAL:
                self.board.grid[x + i][y].ship = True
            else:
                self.board.grid[x][y + i].ship = True
