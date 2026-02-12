# CUBE 3D
this (42) project is the reproduction of wolfenstein 3D which is considered as the first FPS ever created (Doom ancestor, Quake for the youngers)

*regillio 42*

## PARSING
- skip the white spaces and the new lines
each element must begin with its type identifier (composed
by one or two characters): SO NO WHITE SPACES AT THE BEGINING.
So I can check the specific *first* and *second* char in every single line.



	- Color first:
	- Go through each line of file
	- check for the first char of each line AND that the char next to it is a space.
	- carefull: can have the exact same line twice: error.
	- mark the line where I find 'F ' and the line where I find 'C '
	- skip the first char and the whites spaces.
	-
	- check that the second string is ',' separated and has only 2 comas, that is \n terminateed
	- check that the second string follow this format
		0,0,0 | 0,10,0 | 0,0,10 | 10,0,0 | 10,10,0, 10,0,10 | 100,0,10 | 100,0,0 | 100,100,10 | ... a lot (3*3) i think
	to check that I have a valid color code I can:
	split on ','
	check for strlen (in range 1 to 3)
	check for individual char value (range 0 to 255)
			
		


	- go through each line of the file.
	- check for the first 2 char;
	-

`




NO ...



`

check that there is each element
	TEXTURES
		do a string compare on each line of the file, that checks if we have the 2-char-type-id + the path: IT has to be on the same line.
	COLORS
		do a string compare on each line of the file, that check if we have the 1-char-type-id + the colorcode: IT has to be on the same line.
	MAP
		
check that, on one line (before the map)

### format

File name & format
-
name.cub

- name has to be at least 1 char
- extension has to be exactly ".cub"

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
F RRR,GGG,BBB
C RRR,GGG,BBB
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


