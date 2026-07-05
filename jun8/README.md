*This project has been created as part of the 42 curriculum by regillio, mohikhan.*

# cub3D

## Description

`cub3D` is a 42 graphics project inspired by the early first-person rendering style of
Wolfenstein 3D. The goal is to build a small 3D-looking game engine in C using
raycasting.

The program reads a `.cub` scene file, validates its configuration and map, loads XPM
textures, then renders a first-person view with MiniLibX. The player can move through
the map while the engine casts one ray per screen column to find and draw visible walls.

Main parts of the project:

- `.cub` file parsing and validation
- map enclosure and player-position checks
- RGB floor and ceiling colors
- wall texture loading for north, south, west, and east faces
- raycasting-based wall rendering
- keyboard and mouse controls

## Instructions

### Requirements

This project is built for Linux with MiniLibX and X11.

You need:

- `make`
- a C compiler such as `cc`
- X11 development libraries (`X11`, `Xext`)
- `zlib`
- `math` library support

### Compilation

```sh
make
```
### Execution

Run the executable with one `.cub` map file:

```sh
./cub3D maps/simple.cub
```

If the argument is missing or invalid, the program exits with an error message.

### Controls

- `W` / `Up`: move forward
- `S` / `Down`: move backward
- `Left` / `Right`: rotate camera
- Mouse movement: rotate camera
- `Esc` or window close button: quit

## Map Format

A valid `.cub` file contains four texture paths, two RGB colors, then the map:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 50,50,50
C 30,30,80

111111
100001
10N001
100001
111111
```

Configuration identifiers:

- `NO`, `SO`, `WE`, `EA`: wall texture paths
- `F`: floor RGB color
- `C`: ceiling RGB color

Map characters:

- `1`: wall
- `0`: empty space
- `N`, `S`, `E`, `W`: player start position and direction
- spaces are allowed only where the map remains closed

The map must contain exactly one player start and must be fully enclosed by walls.

## Project Structure

- `src/`: parser, raycasting, rendering, hooks, movement, and initialization
- `inc/`: project headers and shared types
- `maps/`: example valid and invalid `.cub` files
- `textures/`: XPM textures used by the maps
- `libft/`: custom 42 C library
- `get_next_line/`: line-reading helper
- `mlx/`: MiniLibX source used for graphics

## Resources

Classic references related to this project:

- 42 `cub3D` subject
- MiniLibX documentation and examples
- Lode Vandevenne, "Raycasting Tutorial": https://lodev.org/cgtutor/raycasting.html
- Permadi, "Ray-Casting Tutorial": https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- The Wolfenstein Black Book
- MLX documentation

AI usage:

- AI assistance was used to simplify and restructure this README.
- AI was used to summarize the project organization and describe the main features from
  the existing source files.
- AI was use to test the program (parsing part) 
- It was use to explain graphical concepts and game design choices ("enclose the map or enclose the player ?")

### FELLOW 42 STUDENTS
- yucchen shared with me her way of reading through the file, parsing the info and we wrapped our minds around the use of `get_next_line`, and discuss different type usage to prevent leak by either freeing the stash or reading until the end of file.
She also help me refactor my code so I optimize the reading part by reading once, get all the info I need and use them later on.
- Cedric gave me great insight on how I can interpret the map characters, how to allocate the map and share with me his graphics sources

