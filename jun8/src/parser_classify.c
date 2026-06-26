/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_classify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:51:53 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 09:51:55 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

enum e_line_type	classify_line(char *line)
{
	if (!line)
		return (INVALID);
	if (line[0] == '\0' || line[0] == '\n')
		return (EMPTY);
	else if (line[0] == 'F' || line[0] == 'C')
		return (COLOR);
	else if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'E' && line[1] == 'A')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'S' && line[1] == 'O'))
		return (TEXTURE);
	else if (ft_strchr("01NSEW", line[0]))
		return (MAP);
	else
		return (INVALID);
}

static int	parse_config_color(t_file *file, t_config *config, char *cur_line)
{
	if (!parse_color(file, cur_line, config))
		return (0);
	if (!register_color_id(config, get_color_id(cur_line)))
		return (0);
	return (1);
}

static int	parse_config_texture(t_config *config, char *cur_line)
{
	t_texture	texture;
	char		texture_id[3];

	ft_memcpy(texture_id, cur_line, 2);
	texture_id[2] = '\0';
	if (!register_texture_id(config, texture_id))
		return (0);
	texture = process_texture_line(cur_line);
	if (!texture.path)
		return (0);
	free(texture.path);
	return (1);
}

int	parse_config_line(t_file *file, t_config *config,
	char *cur_line, enum e_line_type line_type)
{
	if (line_type == COLOR)
		return (parse_config_color(file, config, cur_line));
	if (line_type == TEXTURE)
		return (parse_config_texture(config, cur_line));
	return (1);
}
