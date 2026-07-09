# 2021.03.16
# Mit Bailey
# Ryan Balachandran
# Matt Bonanno
# Copyright (c) 2021

# This file contains algorithms to be employed by the various AIs.

"""
The ship class is used to generate one of each type of ship.

self.length: number of tiles ship occupies
self.aliveSections: what tiles of the ship have not been hit
self.sections: array representing tile sections the ship is on
"""
from __future__ import annotations

import random
from random import randint
from typing import Tuple

import GameBoard
from GameBoard import Board
from direction import Orientation
from ship import Ship


def HP_findShot(board, prevShot):
    # TODO: Add code to actually find a good shot.

    # The Hunt-Parity algorithm works by
    # PARITY
    # - Not firing at squarely adjacent tiles.
    # HUNT
    # - Once a hit is achieved, search the nearby tiles.
    x = 0
    y = 0


    if board.grid[prevShot[0]][prevShot[1]].shot is True and board.grid[prevShot[0]][prevShot[1]].ship is True:
        pass   # TODO: Find an appropriate shot near the hit
    else:
        if board.grid[0][0].shot is True:
            # We shot (0,0) first.
            while board.grid[x][y].shot is True and y <= 10:
                x = (x + 2) % 11
                y += 1
        elif board.grid[0][1].shot is True:
            # We shot (0,1) first.
            x = (x + 2) % 11
            y += 1
        else:
            # We have not yet shot.
            x = random.randint(0, 1)
            y = 0

    return x, y


def Random_findShot(board, prevShot):
    # The Random algorithm works by firing at random tiles
    x = 0
    y = 0

    # Randomly shoot within grid parameters
    # TODO: make sure tile is not shot at twice
    while not board.grid[prevShot[0]][prevShot[1]].shot:
        x = random.randint(0, 9)
        y = random.randint(0, 9)

    return x, y

def Hunt_findShot(agent, board: GameBoard, prevShot) -> Tuple[int, int]:

    # TODO: Add code to actually find a good shot.

    # The Hunt-Parity algorithm works by
    # HUNT
    # - Once a hit is achieved, search the nearby tiles.
    x = 0
    y = 0

    if board.grid[prevShot[0]][prevShot[1]].shot is True and board.grid[prevShot[0]][prevShot[1]].ship is True:
        if not agent.huntList:
            pop: Tuple[int, int] = agent.huntList.pop()
            while pop in agent.prevShotList:
                pop = agent.huntList.pop()
            return pop
        else:
            print("either ship was sunk or an error occured")
    else:
        if board.grid[0][0].shot is True:
            # We shot (0,0) first.
            while board.grid[x][y].shot is True and y <= 10:
                x = (x + 2) % 11
                y += 1
        elif board.grid[0][1].shot is True:
            # We shot (0,1) first.
            x = (x + 2) % 11
            y += 1
        else:
            # We have not yet shot.
            x = random.randint(0, 1)
            y = 0

    return x, y
