/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 07:32:34 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 07:32:35 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_color_lines(char *color_lines[])
{
	if (color_lines[0])
		free(color_lines[0]);
	if (color_lines[1])
		free(color_lines[1]);
}

void	free_color_codes(int n, char *color_codes[])
{
	int	i;

	if (!color_codes || !color_codes[0])
		return ;
	i = 0;
	while (i < n && color_codes[i])
	{
		free(color_codes[i]);
		i++;
	}
}

void	free_texture_lines(char *texture_lines[])
{
	int	i;

	if (!texture_lines || texture_lines[0])
		return ;
	i = 0;
	while (i < 4)
	{
		free(texture_lines[i]);
		i++;
	}
}

void	free_texture_names(char *texture_names[])
{
	int	i;

	if (!texture_names || !texture_names[0])
		return ;
	i = 0;
	while (i < 4)
	{
		free(texture_names[i]);
		i++;
	}
}

void	free_texture_list(t_texture texture_list[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (texture_list[i].path)
			free(texture_list[i].path);
		i++;
	}
}
