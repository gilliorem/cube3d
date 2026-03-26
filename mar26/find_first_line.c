int	find_map_first_line(t_file *file)
{
	int	first_line;
	int	end_first_part;
	int	i;
	int	start_flag;
	int	bad_char_flag;
	char	*last_line;
	
	last_line = NULL;
	start_flag = 0;
	bad_char_flag = 0;
	end_first_part = find_endline_first_part(file);
	i = 0;
	file->fd = try_open_file(file->name);
	while (i < end_first_part)
	{
		file->cur_line = get_next_line(file->fd);
		i++;
		if (i != end_first_part)
			free(file->cur_line);
	}
	print_debug("last text line of first part:", i, NULL);

	//TODO: This loop will also count the empty lines within the MAP. 
	//Fix it with a function that checks if we are in the map; if thats the case,
	//dont increment i.
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		if (file->cur_line[0] == '\n')
		{
			free(last_line);
			last_line = file->cur_line;
			i++;
			continue;
		}
		free(file->cur_line);
	}
	end_first_part = i;
	free(file->cur_line);
	print_debug("last line first part:", end_first_part, last_line);
	free(last_line);
	i = 0;
	close(file->fd);
	try_open_file(file->name);
	while (i < end_first_part)
	{
		file->cur_line = get_next_line(file->fd);
		i++;
	}
	int j = 0;
	while (1)
	{
		j = 0;
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break ;
		if (start_flag == 0 && is_map_char(file->cur_line[0]))
		{
			start_flag = 1;
			first_line = i;
			print_debug("map is starting at line:", first_line, file->cur_line);
		}
		if (bad_char_flag == 0 && start_flag == 1 && !is_map_char(file->cur_line[0]))
		{
			bad_char_flag = 1;
			print_debug("bad char found in map, in line:", i, NULL);
		}
		i++;
		file->map_lines++;
		while (file->cur_line[j] != '\n')
			j++;
		if (j > file->longest_map_line)
			file->longest_map_line = j;

		free(file->cur_line);
	}
	if (bad_char_flag == 1)
		return (print_debug("Error bad char in map", -1, NULL) & 0);
	if (start_flag == 0)
		return (print_debug("Error could not find map", -1, NULL) & 0);
	close(file->fd);
	//printf("map height:%d\nmap width:%d\n", file->map_lines, file->longest_map_line);
	return (first_line);
}
