## MAP PROCESSING
Need to think of how am I going to spot error case like:
- wrong lines:
	- duplicate lines
	- wrong in-line character
	- empty line within/after the map block

when spliting my map content by lines:
I can send each line to the process function:
the process function will 
	- process each line and set the line of each function
	- for the first block (setting):
		- process empty line()
		if not an empty line:
		- process_color_line()
		if it's not a color line it goes into the next function
		- process_texture_line()
	- process the line as color-line/texture-line/empty-line (increment a counter in a Setting struct)

when the first setting-block is processed, we will processed the second (map-block):
- we know the first block is processed when we have 6 valid setting lines and found the first character of the map that indicates the start of the map block (second part)
- we will process the map by doing:
- going through line by line make sure there is no empty line
- going char by char make sure there is the correct set of char
- get the dimension
- get the player position 

important thing to consider:
the map line can be represented a single rectangular block where we do not accept empty line.
the last line of the file has to be a map line of the map block


### PARSING

	typedef enum e_parse_state
	{
		CONFIG,
		IN_MAP
	}	t_parse_state;


	typedef enum e_line_type
	{
		EMPTY,
		COLOR,
		TEXTURE,
		MAP,
		INVALID
	}	t_line_type;


	read_file();
	split_lines();

	init_parser_state();
	

	for each line:
	    type = classify_line(line);

    if state == BEFORE_MAP:
        if type == EMPTY:
            continue;
        else if type == TEXTURE:
            parse_texture(scene, line);
        else if type == COLOR:
            parse_color(scene, line);
        else if type == MAP:
            ensure_all_6_settings_found(scene);
            state = IN_MAP;
            map_start = i;
            store_raw_map_line(line);
        else
            error();

    else if state == IN_MAP:
        if type != MAP:
            error();
        store_raw_map_line(line);

	ensure_map_exists();
	build_rectangular_map();
	validate_map_chars_and_player();
	validate_closed_map();


In order to properly start parsing the map, we need to get to the first char of the map.
To do so, we will:
	- Identify each line in the .cub file
	> setting-line:
		- Color:
			- Floor
			- Ceiling
		- Texture 
			- NO
			- SO
			- EA
			- WE
	empty line


Before the map
we either have a setting line OR an empty line

Count the 6 setting lines


### CHECKING
Starting at the first map char (can be a space)
- extract the map content
- check the map chars


### STORING
- store the valid map in a 2d matrix
- store the player position
