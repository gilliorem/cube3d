/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:34:57 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:34:58 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*get_color_value(char *color_line, char color_id)
{
	int		i;
	int		start;
	int		end;
	char	*color_value;

	(void)color_id;
	if (!color_line)
		return (NULL);
	i = 1;
	while (color_line[i] == ' ')
		i++;
	start = i;
	while (color_line[i] && color_line[i] != ' ' && color_line[i] != '\n')
		i++;
	end = i;
	color_value = ft_substr(color_line, start, end - start);
	if (!color_value)
		return (NULL);
	return (color_value);
}

char	**get_rgbs(char *color_value)
{
	int		i;
	char	**rgb;

	i = 0;
	rgb = ft_split(color_value, ',');
	if (!rgb)
		return (NULL);
	while (rgb[i])
	{
		if (rgb[i][0] == '\0')
			return (parser_error("invalid RGB format"), NULL);
		if (ft_strlen(rgb[i]) > 3)
			return (parser_error("invalid RGB format"), NULL);
		i++;
	}
	if (i != 3)
		return (parser_error_count("wrong RGB component count", i), NULL);
	return (rgb);
}

int	get_rgb_component(char *color_value, int index)
{
	int		value;
	char	**rgbs;
	int		i;

	rgbs = get_rgbs(color_value);
	if (!rgbs)
		return (-1);
	value = ft_atoi(rgbs[index]);
	i = 0;
	while (rgbs[i])
	{
		free(rgbs[i]);
		i++;
	}
	free(rgbs);
	return (value);
}

int	parse_color(t_file *file, char *cur_line, t_config *config)
{
	char	color_id;

	(void)file;
	color_id = get_color_id(cur_line);
	if (!check_color(cur_line, color_id))
		return (0);
	if (color_id == 'C')
		store_color_attributes(cur_line, &config->ceiling, 'C');
	else if (color_id == 'F')
		store_color_attributes(cur_line, &config->floor, 'F');
	else
		return (parser_error("invalid color id") & 0);
	return (1);
}
