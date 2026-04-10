void	init_map_matrix(t_map *map)
{
	int	i;

	i = 0;
	map->matrix = (char **) ft_calloc(map->height + 1, sizeof(char *));
	while (i < map->height)
	{
		map->matrix[i] = (char *) ft_calloc(map->height + 1, sizeof(char *));
		ft_memset(map->matrix[i], ' ', map->width);
		i++;
	}
	
}

t_map *init_map(t_file *file, t_config *config)
{
	t_map *map;
	int	i;

	map = ft_calloc(1, sizeof(t_map));
	map->first_line = config->map_start;
	map->height = config->map_height;
	map->width = get_map_width(file, config); // <
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
	map->matrix = (char **) ft_calloc(map->height + 1, sizeof(char *));
	i = 0;
	return (map);		
}

