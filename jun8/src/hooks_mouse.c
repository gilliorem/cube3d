/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:01:52 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:17:53 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = old_dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = old_plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

static void	update_mouse_position(t_cub3d *cub, int x, int y)
{
	cub->prev_mouse_x = x;
	cub->prev_mouse_y = y;
}

static int	get_mouse_delta(int x, t_cub3d *cub)
{
	return (x - cub->prev_mouse_x);
}

int	mouse_move(int x, int y, t_cub3d *cub)
{
	int		delta_x;
	double	angle;

	delta_x = get_mouse_delta(x, cub);
	if (delta_x != 0)
	{
		angle = ROT_SPEED * delta_x * 0.1;
		rotate(&cub->player, angle);
	}
	update_mouse_position(cub, x, y);
	return (0);
}
