/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:37:07 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:37:09 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*skip_leading_spaces(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ')
		line++;
	return (line);
}

char	*gnl_str(int fd)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(fd, &line);
	if (ret <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	trim_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}

int	get_line_len_no_newline(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	rgb_to_hex(int rgb[3])
{
	int	hex;

	hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (hex);
}
