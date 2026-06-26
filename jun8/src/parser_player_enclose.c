/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player_enclose.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:20:01 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:20:06 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	check_player_cell(t_map_2d *map_2d, int i, int j, int *player_count)
{
	if (!is_player_char(map_2d->matrix[i][j]))
		return (1);
	(*player_count)++;
	map_2d->player_y = i;
	map_2d->player_x = j;
	map_2d->player_dir = map_2d->matrix[i][j];
	if (i == 0 || i == map_2d->height -1 || j == 0 || j == map_2d->width - 1)
		return (parser_error("player on map edge") & 0);
	return (1);
}

int	validate_player(t_map_2d *map_2d)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map_2d->height)
	{
		j = 0;
		while (j < map_2d->width)
		{
			if (!check_player_cell(map_2d, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (parser_error("missing player") & 0);
	if (player_count > 1)
		return (parser_error_count("multiple players", player_count) & 0);
	return (1);
}

int	flood_fill_player_area(t_map_2d *map_2d, char *visited, int y, int x)
{
	int	index;

	if (y < 0 || y >= map_2d->height || x < 0 || x >= map_2d->width)
		return (0);
	if (map_2d->matrix[y][x] == ' ')
		return (0);
	if (!is_walkable_char(map_2d->matrix[y][x]))
		return (1);
	index = y * map_2d->width + x;
	if (visited[index])
		return (1);
	visited[index] = 1;
	if (!flood_fill_player_area(map_2d, visited, y - 1, x))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y + 1, x))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y, x - 1))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y, x + 1))
		return (0);
	return (1);
}

int	validate_map_enclosure(t_map_2d *map_2d)
{
	char	*visited;
	int		is_closed;

	visited = ft_calloc(map_2d->height * map_2d->width, sizeof(char));
	if (!visited)
		return (parser_error("visited alloc failed") & 0);
	is_closed = flood_fill_player_area(map_2d, visited,
			map_2d->player_y, map_2d->player_x);
	free(visited);
	if (!is_closed)
		return (parser_error("player area open to void") & 0);
	return (1);
}
