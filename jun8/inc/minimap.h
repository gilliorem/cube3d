/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 22:51:10 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 22:51:13 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "./cub3d.h"

# define MINI_TILE 8
# define MINI_OFFSET_X 20
# define MINI_OFFSET_Y 20

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

void	draw_minimap_player(t_cub3d *cub);
void	draw_minimap(t_cub3d *cub);

#endif
