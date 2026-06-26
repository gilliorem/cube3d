/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:27:03 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:27:04 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);
	else
		return (parser_error("char is not part of the map charset") & 0);
}

char	*identify_map_line(char *line)
{
	if (ft_strchr(" 1", line[0]))
		return (line);
	return (NULL);
}

int	check_map_line(char *map_line)
{
	int	i;

	i = 0;
	if (map_line[i] == '\n')
		return (parser_error("empty line in map") & 0);
	while (map_line[i] && map_line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", map_line[i]))
			return (parser_error("invalid char in map") & 0);
		i++;
	}
	if (map_line[i] == '\n' && map_line[i + 1] != '\0')
		return (parser_error("invalid char after map newline") & 0);
	return (1);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_walkable_char(char c)
{
	if (c == '0' || is_player_char(c))
		return (1);
	return (0);
}
