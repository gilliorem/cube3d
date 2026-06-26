/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extract_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:30:30 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:30:31 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_texture	create_texture(char id[3], char *path)
{
	t_texture	texture;

	ft_memcpy(texture.id, id, 3);
	texture.path = path;
	texture.fd = -1;
	return (texture);
}

char	*identify_texture_line(char **lines, char *id)
{
	int		i;
	char	*line;

	i = 0;
	while (lines[i])
	{
		line = skip_leading_spaces(lines[i]);
		if (ft_strncmp(line, id, 2) == 0)
			return (line);
		i++;
	}
	return (NULL);
}

int	check_texture_line(char *line, char *id)
{
	int	i;

	i = 0;
	if (!line)
		return (parser_error("missing texture line") & 0);
	if (ft_strncmp(line, id, 2) != 0)
		return (parser_error("wrong texture id") & 0);
	i = 2;
	if (line[i] != ' ')
		return (parser_error("missing space after texture id") & 0);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (parser_error("missing texture path") & 0);
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (parser_error("invalid trailing chars in texture line") & 0);
	return (1);
}

char	*extract_texture_path(char *line)
{
	int		i;
	int		start;
	int		end;

	i = 2;
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	end = i;
	return (ft_substr(line, start, end - start));
}

t_texture	process_texture(t_file *file, char *id)
{
	char	*line;

	line = identify_texture_line(file->lines, id);
	if (!line)
		return (create_texture("\0\0", NULL));
	return (process_texture_line(line));
}
