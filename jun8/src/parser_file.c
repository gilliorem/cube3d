/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:32:03 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 08:54:12 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	check_file_extension(char *filename, char extension[4])
{
	int		i;
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	i = 0;
	if (len <= ext_len)
		return (parser_error("wrong file ext") & 0);
	while (filename[i])
		i++;
	if (filename[i - 1] != extension[3] || filename[i - 2] != extension[2]
		|| filename[i - 3] != extension[1] || filename[i - 4] != extension[0])
		return (parser_error_str("wrong extension: ", filename) & 0);
	return (1);
}

int	check_argv(char *argv[])
{
	(void)argv[0];
	if (!check_file_extension(argv[1], ".cub"))
		return (0);
	return (1);
}

int	try_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		parser_error_str("invalid file: ", file);
		return (-1);
	}
	return (fd);
}

int	get_file_size(t_file *file)
{
	int	i;

	file->fd = try_open_file(file->name);
	if (file->fd == -1)
		return (0);
	i = 0;
	while (1)
	{
		file->cur_line = gnl_str(file->fd);
		if (!file->cur_line)
			break ;
		free(file->cur_line);
		i++;
	}
	file->line_count = i;
	close(file->fd);
	return (1);
}

int	get_file_lines(t_file *file)
{
	int	i;

	if (!get_file_size(file))
		return (0);
	file->lines = ft_calloc(file->line_count + 1, sizeof(char *));
	if (!file->lines)
		return (0);
	file->fd = try_open_file(file->name);
	if (file->fd == -1)
		return (0);
	i = 0;
	while (1)
	{
		file->cur_line = gnl_str(file->fd);
		if (!file->cur_line)
			break ;
		file->lines[i] = file->cur_line;
		i++;
	}
	close(file->fd);
	return (1);
}
