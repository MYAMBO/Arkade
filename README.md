# Arcade Project

## Overview
Arcade is a gaming platform that allows users to choose different games to play and keeps track of player scores. The project uses a dynamic library system to load graphics libraries and games at runtime, ensuring flexibility and modularity in the platform's design.

## Key Features
- Multiple graphics libraries support (ncurses, SDL2, SFML)
- Multiple playable games
- Dynamic library loading at runtime
- Score tracking system
- Ability to switch between graphics libraries and games during gameplay

## Compilation
The project can be compiled using the provided Makefile:

### Using Makefile
```
make                # Build everything
make core           # Build only the core
make games          # Build only the game libraries
make graphicals     # Build only the graphics libraries
make clean          # Clean object files
make fclean         # Clean object files and binaries
make re             # Rebuild the project
```

## Usage
```
./arcade ./lib/[graphics_library.so]
```

Example:
```
./arcade ./lib/arcade_ncurses.so
```

## Controls
- Switch to next graphics library
- Switch to next game
- Restart current game
- Return to menu
- Exit program

## Project Structure
- `./assets/` - Directory including assets for games and core
- `./lib/`    - Directory containing all dynamic libraries
- `./src/`    - Source code for the core program
- `./doc/`    - Documentation including implementation guides

## Interface Sharing

As required by the project specifications, our team has shared our graphical and game library interfaces with another project group. This collaboration ensures that our games can run using their launcher and graphical libraries, and vice-versa.

### Collaboration Group Leader

**Leader Email:** enzo.dubeaurepaire@epitech.eu

## Available Libraries

### Graphics Libraries
- arcade_ncurses.so - NCurses implementation
- arcade_sdl2.so - SDL2 implementation
- arcade_sfml.so - SFML implementation

### Game Libraries
- arcade_snake.so - Snake game implementation
- arcade_minesweeper.so - Minesweeper game implementation
