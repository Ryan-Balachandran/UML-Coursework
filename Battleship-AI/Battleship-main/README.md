# Battleship

## main.py
Handles the main runtime of the program.

## GameBoard.py
Contains Tile and Board class.

Tile class contains:
  - shot boolean: indicates whether the tile has been shot at
  - ship boolean: indicates whether a ship is on the tile

Board class contains:
  - \_\_init__(self, result = 0, turns = 0): 
        <br>- result: returns winner of game
        <br>- turns: returns the amount of turns taken by a player
        <br>- a grid array to make the gameboard
        <br>- a ships array contains references to all of this board's ships
        <br>- creating a 2D array grid with a pair of booleans of shot and shop
  - shootTile(self, coord): given a pair of coordinates, sets the tile boolean of shot to true
  - get_turns(self): returns self.turns
  - single_board(self): creates a single 2D gameboard to be displayed on the screen
  - double_board(self): creates 2 2D gameboards to be displayed on the screen
  - print_board(self, choice): initializes pygame and returns either single or
                               double board to be drawn on the screen
                        
## Constants.py
Contains constant variables to be used on the GameBoard

## algorithm.py
Contains algorithms to be employed by the various AIs

Ship class contains:
  - \_\_init__(self, origin, direction, length):
        <br>- self.length = length: initialize length of ship
        <br>- self.aliveSections = length: initialize ships sections
        <br>- self.sections = []: array containing sections of the ship equal to its length. Sections take the form [(xCoord, yCoord), Alive?]
  - hit(self, coord): TODO
  - isAlive(self): returns whether a ship is alive depending on if aliveSections <= 0

- HP_findshot(board): algorithm to find the shot for Hunt-Parity AI
- HP_placeShip(board, vessel): algorithm to place ships in Hunt-Parity AI

## agents.py
Contains classes for AI agents

HP_AI class contains: (Hunt Parity AI)
  - \_\_init__(self, board):
        <br>- self.board = board: takes in the gameboard from main
        <br>- self.shipsAlive = 5: initialize number of ships alive
        <br>- self.shipSet = []: an array of ships
  - evaluate(self): counts number of living ships
  - takeTurn(self): finds the coordinates for the AI to shoot at before calling fire action

## actions.py
Contains definitions of actions for players to take when game is running

fire(board, coord):
  - given a gameboard and a pair of coordinates, calls shootTile



## state_space.py
Contains definitions for Boards, Tiles, and Ships.
