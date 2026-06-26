/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:10:51 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 10:10:53 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one_texture(t_cub3d *cub, t_tex *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(cub->mlx, path,
			&tex->width, &tex->height);
	if (!tex->ptr)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putendl_fd(path, 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (1);
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int	load_textures(t_cub3d *cub)
{
	if (!load_one_texture(cub, &cub->tex[TEX_NO], cub->map->no_tex))
		return (0);
	if (!load_one_texture(cub, &cub->tex[TEX_SO], cub->map->so_tex))
		return (0);
	if (!load_one_texture(cub, &cub->tex[TEX_WE], cub->map->we_tex))
		return (0);
	if (!load_one_texture(cub, &cub->tex[TEX_EA], cub->map->ea_tex))
		return (0);
	return (1);
}
