t_map	*init_map(t_file *file)
{
	t_map	*map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = ft_calloc(1, sizeof(t_map));
	map->first_line = find_map_first_line(file);
	if (map->first_line == 0)
		return (NULL);
	map->height = file->map_lines;
	map->width = file->longest_map_line;
	map->matrix = (char**)ft_calloc(map->height, sizeof(char *) + 1);
	while (i < map->height)
	{
		map->matrix[i] = (char*) ft_calloc(map->width, sizeof(char) + 1);
		i++;
	}
	i = 0;
	//printf("\nmap height:%d, map max-width:%d\n", map->height, map->width);
	while (i < map->height) 
	{
		j = 0;
		while (j < map->width)
		{
			map->matrix[i][j] = ' ';
			//printf("%c", map->matrix[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	file->fd = try_open_file(file->name);
	while (i < map->first_line)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		i++;
	}
	i = 0;
	int line_len;
	while (i < map->height)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		line_len = ft_strlen(file->cur_line);
		j = 0;
		while (j < (line_len - 1))
		{
			map->matrix[i][j] = file->cur_line[j];
			//printf("%c", map->matrix[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	printf("----MAP----\n");
	while (i < map->height) 
	{
		j = 0;
		while (j < map->width)
		{
			//map->matrix[i][j] = 'X';
			printf("%c", map->matrix[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
	return (map);
}

void	check_for_all_char(t_map *map)
{
	char	*map_str;
	char	*temp;
	int	i;

	map_str = ft_strdup("");
	i = 0;
	while (i < map->height)
	{
		temp = ft_strjoin(map_str, map->matrix[i]);
		//printf("map str: %s\n", map_str);
		//printf("temp:%s", temp);
		map_str = ft_strdup(temp);
		free(temp);
		i++;
	}	
	printf("map string:%s\n", map_str);
}

int	check_map_valid_char(t_file *file, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_strchr(" 10NSEW", map->matrix[i][j]))
			{
				return (print_debug("error: wrong char found in map:", map->matrix[i][j], NULL) & 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
