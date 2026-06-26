/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:04:23 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 10:04:24 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cub->keys[0] = 1;
	else if (keycode == KEY_A)
		cub->keys[1] = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->keys[2] = 1;
	else if (keycode == KEY_D)
		cub->keys[3] = 1;
	else if (keycode == KEY_LEFT)
		cub->keys[4] = 1;
	else if (keycode == KEY_RIGHT)
		cub->keys[5] = 1;
	else if (keycode == KEY_ESC)
		close_window(cub);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cub->keys[0] = 0;
	else if (keycode == KEY_A)
		cub->keys[1] = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->keys[2] = 0;
	else if (keycode == KEY_D)
		cub->keys[3] = 0;
	else if (keycode == KEY_LEFT)
		cub->keys[4] = 0;
	else if (keycode == KEY_RIGHT)
		cub->keys[5] = 0;
	return (0);
}

int	close_window(t_cub3d *cub)
{
	(void)cub;
	exit(0);
	return (0);
}

int	game_loop(t_cub3d *cub)
{
	move_player(cub);
	cast_rays(cub);
	render_frame(cub);
	return (0);
}
