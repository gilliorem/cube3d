/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:26:10 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:26:11 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	check_color_line(char *color_line, char color_id)
{
	int	i;

	if (!color_line)
		return (parser_error("missing color line") & 0);
	if (color_line[0] != color_id)
		return (parser_error("wrong color id") & 0);
	i = 1;
	if (color_line[i] != ' ')
		return (parser_error("missing space after color id") & 0);
	while (color_line[i] == ' ')
		i++;
	if (!color_line[i])
		return (parser_error("missing color value") & 0);
	while (color_line[i] && color_line[i] != ' ' && color_line[i] != '\n')
	{
		if (!ft_strchr("0123456789,", color_line[i]))
			return (parser_error_char("invalid char: ", color_line[i]) & 0);
		i++;
	}
	while (color_line[i] == ' ')
		i++;
	if (color_line[i] != '\0' && color_line[i] != '\n')
		return (parser_error("invalid trailing chars in color line") & 0);
	return (1);
}

int	check_color_value(char *color_value)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (color_value[i])
	{
		if (color_value[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (parser_error("invalid RGB comma count") & 0);
	return (1);
}

int	is_rgb_range(int value)
{
	if (value >= 0 && value <= 255)
		return (1);
	return (0);
}

int	check_rgbs(char color_id, char *color_value)
{
	int	red;
	int	green;
	int	blue;

	red = get_red(color_id, color_value);
	if (!is_rgb_range(red))
		return (0);
	green = get_green(color_id, color_value);
	if (!is_rgb_range(green))
		return (0);
	blue = get_blue(color_id, color_value);
	if (!is_rgb_range(blue))
		return (0);
	return (1);
}

int	check_color(char *cur_line, char color_id)
{
	char	*color_value;

	if (!check_color_line(cur_line, color_id))
		return (0);
	color_value = get_color_value(cur_line, color_id);
	if (!color_value)
		return (parser_error("failed to extract color value") & 0);
	if (!check_color_value(color_value))
		return (free(color_value), 0);
	if (!check_rgbs(color_id, color_value))
		return (free(color_value), 0);
	free(color_value);
	return (1);
}
