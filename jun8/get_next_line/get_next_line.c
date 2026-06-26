/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohikhan <mohikhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:57:24 by mohikhan          #+#    #+#             */
/*   Updated: 2025/08/23 06:23:41 by mohikhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*allocate_line_buffer(char **line, char *buf)
{
	char	*ret;
	int		l_len;
	int		b_len;

	l_len = 0;
	while (*line && (*line)[l_len] && (*line)[l_len] != '\n')
		l_len++;
	b_len = 0;
	while (buf[b_len] && buf[b_len] != '\n')
		b_len++;
	ret = (char *)malloc(sizeof(char) * (b_len + l_len + 2));
	if (!ret)
		return (NULL);
	return (ret);
}

static int	ft_add_to_line(char **line, char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = allocate_line_buffer(line, buf);
	if (!tmp)
		return (-1);
	i = 0;
	j = 0;
	while (*line && (*line)[i] && (*line)[i] != '\n')
		tmp[i++] = (*line)[j++];
	j = 0;
	while (buf[j] && buf[j] != '\n')
		tmp[i++] = buf[j++];
	tmp[i] = buf[j];
	free(*line);
	*line = tmp;
	i = 0;
	while (buf[j])
		buf[i++] = buf[++j];
	buf[i] = '\0';
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	return (i);
}

static int	gnl_core_engine(int fd, char **line)
{
	static char		buf[FD_MAX][BUFFER_SIZE + 1];
	int				ret;

	*line = NULL;
	ret = ft_add_to_line(line, buf[fd]);
	while (ret != -1 && (*line)[ret] != '\n')
	{
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret < 1)
		{
			if (ret < 0)
			{
				free(*line);
				*line = NULL;
			}
			return (ret);
		}
		buf[fd][ret] = '\0';
		ret = ft_add_to_line(line, buf[fd]);
	}
	if (ret == 0 && *line && (*line)[0] != '\0')
		return (1);
	if (ret == -1)
		return (-1);
	return ((*line)[ret] = '\0', 1);
}

int	get_next_line(int fd, char **line)
{
	if (fd < 0 || fd > FD_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	return (gnl_core_engine(fd, line));
}
