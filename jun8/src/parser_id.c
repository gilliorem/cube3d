/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:09:02 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:09:07 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	config_is_complete(t_config *config)
{
	if (config->color_count == 2 && config->text_count == 4)
		return (1);
	return (0);
}

int	register_color_id(t_config *config, char color_id)
{
	if (color_id == 'F')
	{
		if (config->has_floor)
			return (parser_error("duplicate floor color") & 0);
		config->has_floor = 1;
	}
	else if (color_id == 'C')
	{
		if (config->has_ceiling)
			return (parser_error("duplicate ceiling color") & 0);
		config->has_ceiling = 1;
	}
	else
		return (parser_error("invalid color id") & 0);
	config->color_count++;
	config->count++;
	return (1);
}

static int	check_and_set(int *flag, char *name)
{
	if (*flag)
		return (parser_error(name) & 0);
	*flag = 1;
	return (1);
}

int	register_texture_id(t_config *config, char texture_id[3])
{
	int	res;

	if (ft_strncmp(texture_id, "NO", 2) == 0)
		res = check_and_set(&config->has_north, "duplicate NO");
	else if (ft_strncmp(texture_id, "SO", 2) == 0)
		res = check_and_set(&config->has_south, "duplicate SO");
	else if (ft_strncmp(texture_id, "EA", 2) == 0)
		res = check_and_set(&config->has_east, "duplicate EA");
	else if (ft_strncmp(texture_id, "WE", 2) == 0)
		res = check_and_set(&config->has_west, "duplicate WE");
	else
		return (parser_error("invalid texture id") & 0);
	if (!res)
		return (0);
	config->text_count++;
	config->count++;
	return (1);
}
