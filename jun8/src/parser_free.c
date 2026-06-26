/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:33:34 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:33:36 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_file_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	if (!lines[0])
	{
		free(lines);
		return ;
	}
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_map_data(t_map_2d *map_2d)
{
	int	i;

	if (!map_2d)
		return ;
	if (map_2d->matrix)
	{
		i = 0;
		while (i < map_2d->height)
		{
			free(map_2d->matrix[i]);
			i++;
		}
		free(map_2d->matrix);
	}
	free(map_2d);
}

void	free_file_attributes(t_file *file)
{
	if (!file)
		return ;
	free_file_lines(file->lines);
	free(file->name);
	free(file);
}

void	free_data(void *data)
{
	if (!data)
		return ;
	free(data);
}

void	textures_clear(t_texture textures[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		textures[i].path = NULL;
		i++;
	}
}
