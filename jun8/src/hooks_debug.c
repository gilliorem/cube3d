/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:54:25 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 09:54:25 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	key_press_debug(int keycode, t_cub3d *cub)
{
	printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_W)
		cub->keys[0] = 1;
	else if (keycode == KEY_A)
		cub->keys[1] = 1;
	else if (keycode == KEY_S)
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

int	key_release_debug(int keycode, t_cub3d *cub)
{
	printf("Key released: %d\n", keycode);
	if (keycode == KEY_W)
		cub->keys[0] = 0;
	else if (keycode == KEY_A)
		cub->keys[1] = 0;
	else if (keycode == KEY_S)
		cub->keys[2] = 0;
	else if (keycode == KEY_D)
		cub->keys[3] = 0;
	else if (keycode == KEY_LEFT)
		cub->keys[4] = 0;
	else if (keycode == KEY_RIGHT)
		cub->keys[5] = 0;
	return (0);
}
