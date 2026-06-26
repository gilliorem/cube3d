/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:18:59 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:22:20 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static int	can_walk(t_map *map, double x, double y)
{
	int		grid_x;
	int		grid_y;
	char	cell;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_y < 0 || grid_y >= map->height)
		return (0);
	if (grid_x < 0 || grid_x >= (int)ft_strlen(map->grid[grid_y]))
		return (0);
	cell = map->grid[grid_y][grid_x];
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W');
}

static void	get_next_position(t_cub3d *cub, double *new_x, double *new_y)
{
	*new_x = cub->player.pos_x;
	*new_y = cub->player.pos_y;
	if (cub->keys[0])
	{
		*new_x += cub->player.dir_x * MOVE_SPEED;
		*new_y += cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys[2])
	{
		*new_x -= cub->player.dir_x * MOVE_SPEED;
		*new_y -= cub->player.dir_y * MOVE_SPEED;
	}
	if (cub->keys[1])
	{
		*new_x += cub->player.plane_x * MOVE_SPEED;
		*new_y += cub->player.plane_y * MOVE_SPEED;
	}
	if (cub->keys[3])
	{
		*new_x -= cub->player.plane_x * MOVE_SPEED;
		*new_y -= cub->player.plane_y * MOVE_SPEED;
	}
}

static void	commit_position(t_cub3d *cub, double new_x, double new_y)
{
	if (!can_walk(cub->map, new_x, new_y))
		return ;
	cub->player.pos_x = new_x;
	cub->player.pos_y = new_y;
}

static void	apply_rotation(t_cub3d *cub)
{
	if (cub->keys[4])
		rotate_player(&cub->player, -ROT_SPEED);
	if (cub->keys[5])
		rotate_player(&cub->player, ROT_SPEED);
}

void	move_player(t_cub3d *cub)
{
	double	new_x;
	double	new_y;

	get_next_position(cub, &new_x, &new_y);
	commit_position(cub, new_x, new_y);
	apply_rotation(cub);
}
