typedef struct s_cub3d
{
	t_map *map;
	t_player player;
	t_img img;
	t_tex tex[4 or 7]; // Stores NO, SO, WE, EA, DOOR, SPR1, SPR2 (optional)
	void *mlx;
	void *win;
	int keys[8];
	double zbuffer[WIN_W]; // sprite depth
	long frame;          // sprite animation
} t_cub3d;




