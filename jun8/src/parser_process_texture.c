/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_process_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 08:22:13 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:22:14 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_texture	process_texture_line(char *line)
{
	char	id[3];
	char	*path;

	ft_memcpy(id, line, 2);
	id[2] = '\0';
	if (!check_texture_line(line, id))
		return (create_texture("\0\0", NULL));
	path = extract_texture_path(line);
	if (!path)
		return (create_texture("\0\0", NULL));
	if (!check_texture_path(path))
	{
		free(path);
		return (create_texture("\0\0", NULL));
	}
	return (create_texture(id, path));
}

void	init_textures(t_texture texture_list[4], t_file *file)
{
	texture_list[0] = process_texture(file, "NO");
	texture_list[1] = process_texture(file, "SO");
	texture_list[2] = process_texture(file, "EA");
	texture_list[3] = process_texture(file, "WE");
}

int	check_valid_fd(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (parser_error_str("could not open file: ", file_path) & 0);
	close(fd);
	return (1);
}

int	check_texture_path(char *path)
{
	size_t	len;

	if (!path || path[0] == '\0')
		return (parser_error("missing texture path") & 0);
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (parser_error_str("texture is not .xpm: ", path) & 0);
	if (!check_valid_fd(path))
		return (0);
	return (1);
}

int	check_textures_fds(t_texture texture_list[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_valid_fd(texture_list[i].path))
			return (0);
		i++;
	}
	return (1);
}
