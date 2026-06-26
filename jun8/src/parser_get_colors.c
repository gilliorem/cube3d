/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:35:44 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:35:45 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	get_red(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 0));
}

int	get_green(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 1));
}

int	get_blue(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 2));
}

char	get_color_id(char *line)
{
	if (line[0] == 'F')
		return ('F');
	if (line[0] == 'C')
		return ('C');
	else
		return ('\0');
}

void	store_color_attributes(char *cur_line, t_color *color, char id)
{
	char	*color_value;

	color_value = get_color_value(cur_line, id);
	if (!color_value)
		return ;
	if (id == 'F')
	{
		color->id = 'F';
		color->rgb[0] = get_red('F', color_value);
		color->rgb[1] = get_green('F', color_value);
		color->rgb[2] = get_blue('F', color_value);
	}
	else if (id == 'C')
	{
		color->id = 'C';
		color->rgb[0] = get_red('C', color_value);
		color->rgb[1] = get_green('C', color_value);
		color->rgb[2] = get_blue('C', color_value);
	}
	free(color_value);
}
