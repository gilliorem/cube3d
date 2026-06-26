/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:48:59 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:49:00 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/minimap.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_ceiling_floor(t_cub3d *cub, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&cub->img, x, y, cub->map->ceil_color);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < WIN_H)
	{
		put_pixel(&cub->img, x, y, cub->map->floor_color);
		y++;
	}
}

void	render_frame_column(t_cub3d *cub, t_ray *ray, int x)
{
	draw_ceiling_floor(cub, ray, x);
	draw_wall_column(cub, ray, x);
}

void	render_frame(t_cub3d *cub)
{
	cast_rays(cub);
	draw_minimap(cub);
	draw_minimap_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.ptr, 0, 0);
}
