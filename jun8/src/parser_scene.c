/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:33:58 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:54:53 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	scene_init_empty(t_scene *out)
{
	out->config = init_config();
	ft_memset(&out->map, 0, sizeof(t_map));
}

void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	if (scene->map.grid)
	{
		i = 0;
		while (i < scene->map.height)
		{
			free(scene->map.grid[i]);
			i++;
		}
		free(scene->map.grid);
		scene->map.grid = NULL;
	}
	free(scene->map.no_tex);
	free(scene->map.so_tex);
	free(scene->map.ea_tex);
	free(scene->map.we_tex);
	scene->map.no_tex = NULL;
	scene->map.so_tex = NULL;
	scene->map.ea_tex = NULL;
	scene->map.we_tex = NULL;
}

static int	build_scene(t_file *file, t_scene *out,
t_map_2d *map_2d, t_texture textures[4])
{
	if (!validate_map_size(map_2d) || !validate_player(map_2d)
		|| !validate_map_enclosure(map_2d))
		return (0);
	init_textures(textures, file);
	init_map(&out->map, map_2d, &out->config, textures);
	map_2d->matrix = NULL;
	textures_clear(textures);
	return (1);
}

static int	build_map(t_file *file, t_scene *out,
t_map_2d **map_2d, t_texture textures[4])
{
	if (!parse_lines(file, &out->config))
		return (0);
	*map_2d = init_map_2d(file, &out->config);
	fill_map_matrix(*map_2d, &out->config, file);
	return (build_scene(file, out, *map_2d, textures));
}

int	parse_scene(const char *path, t_scene *out)
{
	t_file		*file;
	t_map_2d	*map_2d;
	t_texture	textures[4];
	int			status;

	if (!out || !check_file_extension((char *)path, ".cub"))
		return (0);
	scene_init_empty(out);
	textures_clear(textures);
	file = init_file((char *)path);
	if (!file || !get_file_lines(file))
		return (0);
	map_2d = NULL;
	status = build_map(file, out, &map_2d, textures);
	free_texture_list(textures);
	free_map_data(map_2d);
	free_file_attributes(file);
	if (!status)
		free_scene(out);
	return (status);
}
