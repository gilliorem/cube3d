/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:57:12 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 09:57:13 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_ns(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

static void	set_dir_ew(t_player *p, char dir)
{
	if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_cub3d *cub)
{
	cub->player.pos_x = cub->map->player_x;
	cub->player.pos_y = cub->map->player_y;
	set_dir_ns(&cub->player, cub->map->player_dir);
	set_dir_ew(&cub->player, cub->map->player_dir);
}

int	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (print_error(ERR_MLX));
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "Mogillio cub3D");
	if (!cub->win)
		return (print_error(ERR_MLX));
	cub->img.ptr = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->img.ptr)
		return (print_error(ERR_MLX));
	cub->img.addr = mlx_get_data_addr(cub->img.ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	return (1);
}
