/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:45:05 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:45:31 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_wall_draw(t_wall_draw *draw, t_cub3d *cub, t_ray *ray)
{
	draw->tex = &cub->tex[ray->tex_idx];
	draw->tex_x = (int)(ray->wall_x * (double)draw->tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->tex_x = draw->tex->width - draw->tex_x - 1;
	draw->step = 1.0 * draw->tex->height / ray->line_height;
	draw->tex_pos = (ray->draw_start - WIN_H / 2
			+ ray->line_height / 2) * draw->step;
	draw->y = ray->draw_start;
}

static void	draw_wall_pixels(t_cub3d *cub, t_ray *ray, int x,
	t_wall_draw *draw)
{
	while (draw->y <= ray->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos & (draw->tex->height - 1);
		draw->tex_pos += draw->step;
		put_pixel(&cub->img, x, draw->y,
			get_tex_pixel(draw->tex, draw->tex_x, draw->tex_y));
		draw->y++;
	}
}

void	draw_wall_column(t_cub3d *cub, t_ray *ray, int x)
{
	t_wall_draw	draw;

	init_wall_draw(&draw, cub, ray);
	draw_wall_pixels(cub, ray, x, &draw);
}
