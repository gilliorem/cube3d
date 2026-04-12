## Store and check
### Store
I do need to respect a very specific order during the parsing of the elements:
	go through each line
	detect what kind of line (the parser by looking at the first map char)
	perform all the checks for that line
	store it in the correct data strucuture.	
I need to check and store my config elements.
	color
	texture 
### EXTRA CHECK FOR THE CONFIG ELEMEMTS
6 config elements exactly
no duplicates
texture .xpm

### EXTRA CHECK
No config elements in map
No map elements in config (unless it is the last line, which mean the map has started)

map block in the correct spot in the file
map lines within the config block

map player
map enclosure

