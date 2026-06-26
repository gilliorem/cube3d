/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:10:26 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:10:27 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_file	*init_file(char *argv_one)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	file->name = ft_strdup(argv_one);
	file->line_count = 0;
	return (file);
}

t_color	init_floor(void)
{
	t_color	floor;

	floor.id = '\0';
	floor.rgb[0] = 0;
	floor.rgb[1] = 0;
	floor.rgb[2] = 0;
	return (floor);
}

t_color	init_ceiling(void)
{
	t_color	ceiling;

	ceiling.id = '\0';
	ceiling.rgb[0] = 0;
	ceiling.rgb[1] = 0;
	ceiling.rgb[2] = 0;
	return (ceiling);
}

t_config	init_config(void)
{
	t_config	config;

	config.floor = init_floor();
	config.ceiling = init_ceiling();
	config.north = NULL;
	config.south = NULL;
	config.east = NULL;
	config.west = NULL;
	config.has_floor = 0;
	config.has_ceiling = 0;
	config.has_north = 0;
	config.has_south = 0;
	config.has_east = 0;
	config.has_west = 0;
	config.map_height = 0;
	config.count = 0;
	config.color_count = 0;
	config.text_count = 0;
	return (config);
}

void	init_map(t_map *map, t_map_2d *map_2d, t_config *config,
		t_texture textures[4])
{
	map->grid = map_2d->matrix;
	map->width = map_2d->width;
	map->height = map_2d->height;
	map->no_tex = textures[0].path;
	map->so_tex = textures[1].path;
	map->ea_tex = textures[2].path;
	map->we_tex = textures[3].path;
	map->floor_color = rgb_to_hex(config->floor.rgb);
	map->ceil_color = rgb_to_hex(config->ceiling.rgb);
	map->player_x = (double)map_2d->player_x + 0.5;
	map->player_y = (double)map_2d->player_y + 0.5;
	map->player_dir = map_2d->player_dir;
	map->num_sprites = 0;
}
