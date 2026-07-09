# 2021.03.16
# Mit Bailey
# Ryan Balachandran
# Matt Bonanno
# Copyright (c) 2021
from __future__ import annotations
from typing import List, Any
import pygame
from constants import *
from ship import Fleet

"""
The Tile class composes the basic makeup of the Battleship board.

shot: Has this tile been shot at?
ship: Is a ship segment present?
missed: Was there a shot here and did it miss?
"""


class Tile(object):
    shot = False
    ship = False


"""
Statistics class returns various states and scores at the end of the game

shots: number of shots taken in the game
misses: number of misses taken in the game
hits: number of hits taken in the game, max of 17 per player
turns: number of turns in the game
result: display of all above
"""


class Statistics(object):
    def __init__(self, shots=0, misses=0, hits=0, turns=0):
        self.shots = shots
        self.misses = misses
        self.hits = hits
        self.turns = turns

    # Returns number of shots taken
    def get_shots(self):
        return self.shots

    # Returns number of misses
    def get_misses(self):
        return self.misses

    def add_misses(self):
        self.misses = self.misses + 1
        self.shots = self.shots + 1

        return self.misses

    # Returns number of hits
    def get_hits(self):
        return self.hits

    def add_hits(self):
        self.hits = self.hits + 1
        self.shots = self.shots + 1
        return self.hits

    # Returns number of turns taken
    def get_turns(self):
        return self.turns

    def add_turns(self):
        self.turns = self.turns + 1
        return self.turns

    # Returns result of the game
    def get_result(self):
        print("Game lasted for:", self.get_turns(), "turns")
        print("Player made:", self.get_shots(), "Shots")
        print("Player made:", self.get_misses(), "misses")
        print("Player hit ships:", self.get_hits(), "times")


"""
Board class contains the Ships and Tiles for one player

__init__(self): This default constructor initializes empty lists for ships and the
                grid before appending 10 empty lists and 10 Tiles to each new list.

self.grid: Contains the game grid.
self.ships: Contains references to all of this board's ships.

shootTile: shoot the given tile and perform the appropriate cleanup
single_board: displays one grid to screen when testing algorithms
double_board: displays two grids to screen when comparing algorithms
"""


class Board(object):
    grid: List[List[Tile]]

    def __init__(self):
        self.screen = pygame.display.set_mode(size1)
        self.grid = []  # Used for making the gameboard
        self.ships = []
        self.clock = pygame.time.Clock()  # Used to manage how fast the screen updates

        # Create a 2D array
        for row in range(10):
            self.grid.append([])  # Add an empty array that will hold each Tile
            for column in range(10):
                self.grid[row].append(Tile())

    # shoot the given tile and perform the appropriate cleanup

    def shootTile(self, coord) -> bool:
        if self.grid[coord[0]][coord[1]].ship:
            self.grid[coord[0]][coord[1]].shot = True
            pygame.draw.rect(self.screen, RED,
                             [(margin + width) * coord[1] + margin + 50,
                              (margin + height) * coord[0] + margin + 50,
                              width, height])
            pygame.display.update()
            return True
        else:
            pygame.draw.rect(self.screen, BLACK,
                             [(margin + width) * coord[1] + margin + 50,
                              (margin + height) * coord[0] + margin + 50,
                              width, height])
            pygame.display.update()
        return False

    def init_single_board(self):
        pygame.display.set_caption("Battleship")
        font = pygame.font.SysFont(["comicsansms", "Comic Sans MS", "Arial"], 42)
        text1 = font.render("0   1   2   3   4   5   6   7   8   9", True, BLACK)
        text2 = font.render("9   8   7   6   5   4   3   2   1   0", True, BLACK)
        text2 = pygame.transform.rotate(text2, 90)

        self.screen.fill(WHITE)

        self.screen.blit(text1, (75, 0))
        self.screen.blit(text2, (0, 75))

        for row in range(10):
            for column in range(10):
                color = BLUE

                if self.grid[row][column].shot and not self.grid[row][column].ship:  # Miss
                    color = BLACK
                if self.grid[row][column].shot and self.grid[row][column].ship:  # Hit
                    color = RED
                if not self.grid[row][column].shot and self.grid[row][column].ship:  # Ship
                    color = GREEN

                pygame.draw.rect(self.screen, color,
                                 [(margin + width) * column + margin + 50,
                                  (margin + height) * row + margin + 50,
                                  width, height])

        # Updates the screen with what has been drawn.
        pygame.display.update()
        self.clock.tick(60)

    def single_board(self, fleet, agent):
        pygame.display.set_caption("Battleship")
        font = pygame.font.SysFont(["comicsansms", "Comic Sans MS", "Arial"], 42)
        text1 = font.render("0   1   2   3   4   5   6   7   8   9", True, BLACK)
        text2 = font.render("9   8   7   6   5   4   3   2   1   0", True, BLACK)
        text2 = pygame.transform.rotate(text2, 90)
        self.init_single_board()
        AllShipsSunk = False  # Loop until the user clicks the close button
        fleet.populate()
        fleet.placeShipsRandomly()

        while not fleet.checkAllShipsSunk():
            agent.takeTurn()
            for event in pygame.event.get():  # User did something
                if event.type == pygame.QUIT:  # If user clicked close
                    AllShipsSunk = True  # Flag that we are done so we exit this loop
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    AllShipsSunk = True

            # --- Game logic should go here
            # --- Screen-clearing code goes here

            # Drawing the display

            # Updates the screen with what has been drawn.
            pygame.display.update()
            self.clock.tick(60)

        pygame.quit()

    def double_board(self):
        screen = pygame.display.set_mode(size2)
        pygame.display.set_caption("Battleship")

        font = pygame.font.SysFont("comicsansms", 42)
        text1 = font.render("0   1   2   3   4   5   6   7   8   9", True, BLACK)
        text2 = font.render("9   8   7   6   5   4   3   2   1   0", True, BLACK)
        text2 = pygame.transform.rotate(text2, 90)

        print(size2)
        AllShipsSunk = False  # Loop until the user clicks the close button
        self.clock = pygame.time.Clock()  # Used to manage how fast the screen updates

        while not AllShipsSunk:
            for event in pygame.event.get():  # User did something
                if event.type == pygame.QUIT:  # If user clicked close
                    AllShipsSunk = True  # Flag that we are done so we exit this loop
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    AllShipsSunk = True

            # --- Game logic should go here

            # --- Screen-clearing code goes here

            # Drawing the display
            screen.fill(WHITE)

            screen.blit(text1, (75, 0))
            screen.blit(text1, (815, 0))
            screen.blit(text2, (0, 75))
            screen.blit(text2, (745, 75))

            # Fills all of the grid spaces with white
            for row in range(10):
                for column in range(10):
                    color = BLUE

                    if self.grid[row][column] == [True, False]:  # Miss
                        color = BLACK
                    if self.grid[row][column] == [True, True]:  # Hit
                        color = RED
                    if self.grid[row][column] == [False, True]:  # Ship
                        color = GREEN

                    pygame.draw.rect(screen, color,
                                     [(margin + width) * column + margin + 50,
                                      (margin + height) * row + margin + 50,
                                      width, height])

            for row in range(10):
                for column in range(10):
                    color = BLUE

                    if self.grid[row][column] == [True, False]:  # Miss
                        color = BLACK
                    if self.grid[row][column] == [True, True]:  # Hit
                        color = RED
                    if self.grid[row][column] == [False, True]:  # Ship
                        color = GREEN

                    pygame.draw.rect(screen, color,
                                     [(margin + width) * column + margin + 794,
                                      (margin + height) * row + margin + 50,
                                      width, height])

            # Updates the screen with what has been drawn.
            pygame.display.flip()
            self.clock.tick(60)
        pygame.quit()

    def update_grid(self):
        for row in range(10):
            for column in range(10):
                color = None
                if self.grid[row][column].shot and not self.grid[row][column].ship:  # Miss
                    color = BLACK
                if self.grid[row][column].shot and self.grid[row][column].ship:  # Hit
                    color = RED
                if not self.grid[row][column].shot and self.grid[row][column].ship:  # Ship
                    color = GREEN

                if color is not None:
                    pygame.draw.rect(self.screen, color,
                                     [(margin + width) * column + margin + 794,
                                      (margin + height) * row + margin + 50,
                                      width, height])

        # Updates the screen with what has been drawn.
        pygame.display.flip()
        self.clock.tick(60)

    def update_Tile(self, row, column):
        print("update tile")
        color = None
        if self.grid[row][column].shot and not self.grid[row][column].ship:  # Miss
            color = BLACK
        if self.grid[row][column].shot and self.grid[row][column].ship:  # Hit
            color = RED
            print("color now red at {0} , {1}".format(row, column))
        if not self.grid[row][column].shot and self.grid[row][column].ship:  # Ship
            color = GREEN
            print("color now green at {0} , {1}".format(row, column))

        if color is not None:
            pygame.draw.rect(self.screen, color,
                             [(margin + width) * column + margin + 794,
                              (margin + height) * row + margin + 50,
                              width, height])
        # Updates the screen with what has been drawn.
        pygame.display.update()
        self.clock.tick(60)

    def print_board(self, choice, fleet, agent):
        # Initialize pygame
        pygame.init()

        if choice == 1:
            self.single_board(fleet, agent)
        elif choice == 2:
            self.double_board()
