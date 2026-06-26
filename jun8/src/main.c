/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 09:59:24 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 09:59:26 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	print_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub;
	t_scene	scene;

	ft_memset(&cub, 0, sizeof(t_cub3d));
	if (argc != 2)
	{
		ft_putendl_fd(ERR_USAGE, 2);
		return (1);
	}
	if (!parse_scene(argv[1], &scene))
		return (1);
	cub.map = &scene.map;
	init_player(&cub);
	if (!init_mlx(&cub) || (!load_textures(&cub)))
		return (free_scene(&scene), 1);
	cub.prev_mouse_x = WIN_W / 2;
	cub.prev_mouse_y = WIN_H / 2;
	mlx_hook(cub.win, EV_KEY_PRESS, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, EV_KEY_RELEASE, 1L << 1, key_release, &cub);
	mlx_hook(cub.win, 6, 1L << 6, mouse_move, &cub);
	mlx_hook(cub.win, EV_DESTROY, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
