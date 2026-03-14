# Quoridor Game in C++

## Overview
This project implements a graphical version of **Quoridor** in C++, using the `graphics.h` library for the interface and rendering.

The game supports both **2-player** and **4-player** modes, as well as matches against the computer. In addition to the basic game mechanics, the project includes player customization, menu navigation, move validation, barrier placement, path checking, and simple AI behaviors.

This was developed as a **teamwork project** in the first year of college, together with a colleague, and is included here for portfolio purposes.

## Technologies
- C++
- `graphics.h`
- basic game logic and pathfinding algorithms
- mouse and keyboard event handling

## Main Features
- graphical interface built with `graphics.h`
- main menu with multiple game modes
- **player vs player**
- **player vs computer**
- **player vs smarter computer**
- support for **2-player** and **4-player** games
- custom pawn selection
- player name input
- barrier placement with horizontal and vertical orientation
- move validation according to Quoridor rules
- winner detection
- path validation to prevent illegal wall placements
- highlighted legal moves for the current player
- help / instructions screen

## Game Modes
The application supports the following modes:

- **Player vs Player**
- **Player vs PC1** — computer makes simpler moves
- **Player vs PC2** — computer uses a more strategic approach
- **2-player mode**
- **4-player mode**

## Gameplay Logic
The board is modeled internally as a matrix that stores:

- empty spaces
- player positions
- horizontal barriers
- vertical barriers

The implementation handles:

- pawn movement
- adjacency rules
- jump logic when players face each other
- diagonal movement in special cases
- barrier placement restrictions
- alternating turns
- win conditions depending on player direction

## Barrier Validation
A key part of the project is the validation of barrier placement.

The game ensures that:

- barriers are only placed in valid positions
- barriers do not overlap existing barriers
- barriers respect orientation rules
- no barrier may completely block a player's path to the target side

To enforce this, the project uses path-checking logic based on graph traversal / Lee-style search before confirming a barrier placement.

## Interface
The project includes:

- menu screens
- winner / loser screens
- instruction screen
- custom pawn selection screen
- visual board rendering
- highlighted available moves
- displayed player names and remaining barriers

User interaction is handled through:

- **left click** for moving
- **right click** for placing barriers
- **R** for switching barrier orientation
- **ESC** for returning to the menu

## How to build and run
To run the project, you need:

- a C++ compiler compatible with `graphics.h`
- the `graphics.h` environment configured correctly
- all required `.bmp` files placed in the same folder as the project files

## What I learned

Through this project, I gained practical experience with:
- graphical programming in C++
- event-driven interaction with mouse and keyboard
- board game implementation
- movement and rule validation
- pathfinding for legality checks
- simple AI design
- turn-based game logic
- managing game states and menus
- teamwork on a larger project
