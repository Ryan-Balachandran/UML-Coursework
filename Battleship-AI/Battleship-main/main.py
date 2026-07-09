# 2021.03.16
# Mit Bailey
# Ryan Balachandran
# Matt Bonanno
# Copyright (c) 2021

"""
This is the main.py file of the Artificial Intelligence for Battleship using Genetic Programming.

How does it work?
The AI begins with a finite population of programs. These programs then play Battleship, with the highest
performing programs being selected to produce the subsequent generation of programs. The next generation
replaces the old programs that were not selected. This continues until performance plateaus.

The board will be represented by a list of lists of Tiles. List X will contain 10 lists which in turn each
contain a Tile. Note that the entire game consists of two boards (one for each player).

  0 1 2 3 4 5 6 7 8 9
  x x x x x x x x x x
0 y y y y y y y y y y
1 y y y y y y y y y y
2 y y y y y y y y y y
3 y y y y y y y y y y
4 y y y y y y y y y y
5 y y y y y y y y y y
6 y y y y y y y y y y
7 y y y y y y y y y y
8 y y y y y y y y y y
9 y y y y y y y y y y
"""

# Imports
from __future__ import annotations

import pygame

import GameBoard
import agents
from ship import Fleet


def main():
    pygame.init()
    # Initialize
    done = -1

    ai_board = GameBoard.Board()
    stats = GameBoard.Statistics()
    ai_fleet = Fleet(ai_board)
    agent = agents.Random_AI(ai_board, ai_fleet, stats)
    ai_board.single_board(ai_fleet, agent)
    # playerOne = agents.Hunt(ai_board)
    # playerTwo = agents.Hunt(ai_board)
    # Loop (done will contain the player number who lost).
    # while done < 0:
    #     playerOne.takeTurn()
    #     playerTwo.takeTurn()
    #
    #     if playerOne.evaluate():
    #         done = 1
    #     elif playerTwo.evaluate():
    #         done = 2
    #     # Remove the variable below once the game loop is ready and functional.
    #     done = -1

    print("GAMEOVER: Player ", done, " has lost!")
    pygame.quit()
    # ai_board.print_board(1, ai_fleet, agent)  # TODO: add board parameter to pass in grid
    stats.get_result()


if __name__ == "__main__":
    main()
