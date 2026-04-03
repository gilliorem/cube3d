## MAP PROCESSING
Need to think of how am I going to spot error case like:
- wrong lines:
	- duplicate lines
	- wrong in-line character
	- empty line within/after the map block
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
