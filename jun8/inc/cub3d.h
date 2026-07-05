/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 22:48:49 by regillio          #+#    #+#             */
/*   Updated: 2026/06/26 22:48:50 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../mlx/mlx.h"
# include "types.h"

/* Error messages  */

# define ERR_USAGE	"Usage: ./cub3D [map.cub]"
# define ERR_MLX	"Error\nFailed to initialize MiniLibX"

/* Screen constants */

# define WIN_W		1280
# define WIN_H		720

/* X11 event codes  */

# define EV_KEY_PRESS	2
# define EV_KEY_RELEASE	3
# define EV_DESTROY	17

/* X11 key codes (Linux)  */

# define KEY_W		119
# define KEY_A		100
# define KEY_S		115
# define KEY_D		97
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307

/* Movement constants  */

# define MOVE_SPEED	0.08
# define ROT_SPEED	0.05

/* Texture indices  */

# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3

/* Structs  */

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_idx;
}	t_ray;

typedef struct s_wall_draw
{
	t_tex	*tex;
	int		tex_x;
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;
}	t_wall_draw;

typedef struct s_cub3d
{
	t_map		*map;
	t_player	player;
	t_img		img;
	t_tex		tex[4];
	void		*mlx;
	void		*win;
	int			keys[8];
	int			prev_mouse_x;
	int			prev_mouse_y;
	double		zbuffer[WIN_W];
}	t_cub3d;

/* main.c */
int		print_error(char *msg);

/* init_mlx.c */
int		init_mlx(t_cub3d *cub);
void	init_player(t_cub3d *cub);

/* textures.c */
int		load_textures(t_cub3d *cub);
int		get_tex_pixel(t_tex *tex, int x, int y);

/* raycaster.c */
void	init_ray(t_ray *ray, t_player *p, int x);
void	cast_rays(t_cub3d *cub);

/* render.c */
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_wall_column(t_cub3d *cub, t_ray *ray, int x);
void	render_frame_column(t_cub3d *cub, t_ray *ray, int x);
void	render_frame(t_cub3d *cub);

/* hooks.c */
int		key_press(int keycode, t_cub3d *cub);
int		key_press_debug(int keycode, t_cub3d *cub);
int		key_release(int keycode, t_cub3d *cub);
int		key_release_debug(int keycode, t_cub3d *cub);
int		mouse_move(int x, int y, t_cub3d *cub);
int		close_window(t_cub3d *cub);
int		game_loop(t_cub3d *cub);

/* movement.c */
void	move_player(t_cub3d *cub);
void	rotate_player(t_player *player, double angle);

#endif
