#ifndef TYPES_H
# define TYPES_H

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	int		floor_color;
	int		ceil_color;
	double	player_x;
	double	player_y;
	char	player_dir;
	int		num_sprites;
}	t_map;

#endif
