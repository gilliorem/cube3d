/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:07:32 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:11:34 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minimap.h"
#include "../inc/cub3d.h"

static void	draw_square(t_cub3d *cub, t_pos pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&cub->img, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cub3d *cub)
{
	t_pos	pos;
	t_pos	screen_pos;

	pos.y = 0;
	while (cub->map->grid[pos.y])
	{
		pos.x = 0;
		while (cub->map->grid[pos.y][pos.x])
		{
			if (cub->map->grid[pos.y][pos.x] == '1')
			{
				screen_pos.x = 20 + pos.x * 8;
				screen_pos.y = 20 + pos.y * 8;
				draw_square(cub, screen_pos, 8, 0xffffff);
			}
			pos.x++;
		}
		pos.y++;
	}
}

static void	draw_player_dir(t_cub3d *cub, t_pos center)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < 10)
	{
		x = center.x + cub->player.dir_x * i;
		y = center.y + cub->player.dir_y * i;
		put_pixel(&cub->img, x, y, 0x701155);
		i++;
	}
}

void	draw_minimap_player(t_cub3d *cub)
{
	t_pos	center;
	t_pos	square;

	center.x = 20 + cub->player.pos_x * 8;
	center.y = 20 + cub->player.pos_y * 8;
	square.x = center.x - 2;
	square.y = center.y - 2;
	draw_square(cub, square, 4, 0xFF0000);
	draw_player_dir(cub, center);
}
