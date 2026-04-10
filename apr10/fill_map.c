t_map *init_map(t_file *file, t_config *config)
{
	t_map *map;
	int	i;

	map = ft_calloc(1, sizeof(t_map));
	map->first_line = config->map_start;
	map->height = config->map_height;
	map->width = get_map_width(file, config); // <
	init_map_matrix(map);
	//for (int i = 0; map->matrix[i]; i++)
	//	printf("%s\n", map->matrix[i]);
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
	i = 0;
	return (map);		
}

void	fill_map_matrix(t_map *map, t_config *config, t_file *file)
{
	int	i;
	int	j;

	i = config->map_start;
	printf("lines[%d]:%s\n",i, file->lines[i]);
	printf("file height:%d\n", file->height);
	printf("i:%d\n", i);
	j = 0;
	while (j < map->height)
	{
		ft_strlcpy(map->matrix[j], file->lines[i], ft_strlen(file->lines[i]));
		printf("%s", map->matrix[j]);
		i++;
		j++;
	}
}

