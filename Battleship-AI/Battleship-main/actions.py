# 2021.03.16
# Mit Bailey
# Copyright (c) 2021

# This file contains actions to be employed by the various AIs.

from __future__ import annotations

# returns true if a ship was hit
def fire(ai, board, coord) -> bool:
    ai.coords_hit.add(coord)
    print("Firing at tile (", coord[0], ", ", coord[1], ").")
    # board.Statistics.add_shots()
    return board.shootTile(coord)
