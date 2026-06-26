/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:37:05 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:37:07 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	validate_map_size(t_map_2d *map_2d)
{
	if (map_2d->height < 3 || map_2d->width < 3)
		return (parser_error("map too small") & 0);
	return (1);
}

int	get_map_width(t_file *file, t_config *config)
{
	int	max_width;
	int	i;
	int	line_len;

	i = config->map_start;
	max_width = 0;
	while (i < config->map_start + config->map_height)
	{
		line_len = get_line_len_no_newline(file->lines[i]);
		if (line_len > max_width)
			max_width = line_len;
		i++;
	}
	return (max_width);
}

void	init_map_matrix(t_map_2d *map_2d)
{
	int	i;

	i = 0;
	map_2d->matrix = (char **) ft_calloc(map_2d->height + 1, sizeof(char *));
	while (i < map_2d->height)
	{
		map_2d->matrix[i] = (char *) ft_calloc(map_2d->width + 1, sizeof(char));
		ft_memset(map_2d->matrix[i], ' ', map_2d->width);
		i++;
	}
}

t_map_2d	*init_map_2d(t_file *file, t_config *config)
{
	t_map_2d	*map_2d;

	map_2d = ft_calloc(1, sizeof(t_map_2d));
	map_2d->first_line = config->map_start;
	map_2d->height = config->map_height;
	map_2d->width = get_map_width(file, config);
	init_map_matrix(map_2d);
	map_2d->player_x = 0;
	map_2d->player_y = 0;
	map_2d->player_dir = 0;
	return (map_2d);
}

void	fill_map_matrix(t_map_2d *map_2d, t_config *config, t_file *file)
{
	int	i;
	int	j;
	int	len;

	i = config->map_start;
	j = 0;
	while (j < map_2d->height)
	{
		len = ft_strlen(file->lines[i]);
		if (file->lines[i][len - 1] == '\n')
			len--;
		ft_memcpy(map_2d->matrix[j], file->lines[i], len);
		i++;
		j++;
	}
}
