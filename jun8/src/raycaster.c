/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 12:30:16 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 12:30:17 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_step(t_ray *ray, t_player *p)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < map->height
			&& ray->map_x >= 0
			&& ray->map_x < (int)ft_strlen(map->grid[ray->map_y])
			&& map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static void	calc_tex_info(t_ray *ray, t_player *p)
{
	if (ray->side == 0)
		ray->wall_x = p->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = p->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->step_x < 0)
		ray->tex_idx = TEX_WE;
	else if (ray->side == 0 && ray->step_x > 0)
		ray->tex_idx = TEX_EA;
	else if (ray->side == 1 && ray->step_y < 0)
		ray->tex_idx = TEX_NO;
	else
		ray->tex_idx = TEX_SO;
}

void	cast_rays(t_cub3d *cub)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(&ray, &cub->player, x);
		calc_step(&ray, &cub->player);
		perform_dda(&ray, cub->map);
		calc_wall_height(&ray);
		calc_tex_info(&ray, &cub->player);
		cub->zbuffer[x] = ray.perp_wall_dist;
		render_frame_column(cub, &ray, x);
		x++;
	}
}
