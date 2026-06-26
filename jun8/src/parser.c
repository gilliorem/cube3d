/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:46:51 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 09:46:52 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static int	start_map(t_config *config, int index)
{
	if (!config_is_complete(config))
		return (parser_error_count("map started before config",
				config->count) & 0);
	config->map_start = index;
	return (1);
}

static int	parse_map_block(t_file *file, t_config *config, int *i)
{
	char	*cur_line;

	while (file->lines[*i])
	{
		cur_line = skip_leading_spaces(file->lines[*i]);
		if (!check_map_line(cur_line))
			return (0);
		config->map_height++;
		(*i)++;
	}
	return (1);
}

static int	validate_parse_result(t_config *config)
{
	if (!config_is_complete(config))
		return (parser_error_count("missing config",
				config->count) & 0);
	if (config->map_height == 0)
		return (parser_error("missing map") & 0);
	return (1);
}

int	parse_lines(t_file *file, t_config *config)
{
	enum e_line_type	line_type;
	int					i;
	char				*cur_line;

	i = 0;
	while (file->lines[i])
	{
		cur_line = skip_leading_spaces(file->lines[i]);
		line_type = classify_line(cur_line);
		if (line_type == EMPTY)
			i++;
		else if (line_type == COLOR || line_type == TEXTURE)
		{
			if (!parse_config_line(file, config, cur_line, line_type))
				return (0);
			i++;
		}
		else
		{
			if (!start_map(config, i) || !parse_map_block(file, config, &i))
				return (0);
		}
	}
	return (validate_parse_result(config));
}
