# CUBE 3D
*This project has been created as part of the 42 curriculum by regillio and mohikhan*

## Description
this (42) project is the reproduction of wolfenstein 3D which is considered as the first FPS ever created (Doom, id software)
The goal of this project is to teach us how to understand and implement a "3d" rendering method - *raycasting* to draw the FPS view of our player.
Here is how it works, put it simply:


## Instructions
- Clone this git repo
- run the makefile
- run the executable with a map as a command line argument - a map can be find in the dir ./maps and have the .cub extension

```bash
make
./cub3d maps/simple.cub
```

## Resources

## PARSING
I've done 3 type of parsings.


### File format
-
name.cub

- name has to be at least 1 char
- extension has to be exactly ".cub"
- check for the first two char of each line.

each element must begin with its type identifier (composed
by one or two characters): SO NO WHITE SPACES AT THE BEGINING.
So I can check the specific *first* and *second* char in every single line.


	- Color first:
	- Go through each line of file
	- check for the first char of each line AND that the char next to it is a space.
	- carefull: can have the exact same line twice: error.
	- mark the line where I find 'F ' and the line where I find 'C '
### Memory issue GNL
The problem we have is that once we found the lines that correspond, we leave
But the gnl *stash* is not being freeed. so we have allocated bytes
	> each time we call `gnl`, we will read until the EOF to assure that the *stash* is empty.
	> this will prevent memory leak.
	- skip the first char and the whites spaces.
	- check that the second string is ',' separated and has only 2 comas
	convert the rgb to an int and check the rang.
	to check that I have a valid color code I can:
	split on ','
	check that we have exactly 3 colors.
	check for individual char value (range 0 to 255)
		

Walls Textures
-
	Can be separated by one or more spaces
	Can be set in any order (SO NO WE EA)
	Stricly need to respect NO SO WE EA + path of texture file with one <space>
	
`
NO textures/xpm_dir/file.xpm
SO textures/xpm_dir/file.xpm
WE textures/xpm_dir/file.xpm
EA textures/xpm_dir/file.xpm
`

Floor and ceiling color
-
`
F 123,123,123
C 123,123,123
`

Map
-
`
 NNN 
W   E
W   E
W N E
W   E
W   E
 SSS 
`

REPRESENT THE MAP
-
We need to have:
- The starting line
- The longest line (max-width)
- The total number of lines

After parsing and checking our 2 coulours and textures, our file struct looks like this
`
typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	int	line_count_color;
	int	n_color_lines;
	char	*color_lines[2];
	char 	*color_codes[2];
	char	**rgb[2];
	int	line_count_texture;
	char	*texture_lines[4];
	char	*texture_paths[4];
	char	*texture_names[4];
	int	textures_fds[4];
	char	**map; // as it is in the file (with the '\n')
}	t_file;
`

I don't think we want our map to be in the file as a `char**`
we can have a pointer to the map object in the file
we need to have the number of lines of the map (rows) and the
longest line (cols)
in the file struct it can be save as *map_lines*, and *longest_map_line* and later
would be transfer to our map object with the attributes map.rows and map.cols;

---

### RULES
A function that call `get_next_line` has to read the file until the last line. That function is responsible for opening the file, reading it entirely and closing it. Doing this will prevent leaking.

## RESOURCES

### FELLOW 42 STUDENTS
- yucchen shared with me her way of reading through the file, parsing the info and we wrapped our minds around the use of `get_next_line`, and discuss different type usage to prevent leak by either freeing the stash or reading until the end of file.
She also help me refactor my code so I optimize the reading part by reading once, get all the info I need and use them later on.
- Cedric gave me great insight on how I can interpret the map characters, how to allocate the map and share with me his graphics sources

### READING AND DOCUMENTATION


### VIDEO


