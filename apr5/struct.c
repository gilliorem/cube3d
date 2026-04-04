enum e_state 
{
	CONFIG,
	IN_MAP
};

enum e_line_type 
{
    EMPTY,
    COLOR,
    TEXTURE,
    MAP,
    INVALID
};

/* we first check if we have the config lines
 * we then check if they contain the correct values 
 */
typedef struct s_config
{
	bool	has_floor;
	bool	has_ceiling;
	bool	has_no;
	bool	has_so;
	bool	has_ea;
	bool	has_we;
	int	floor_rgb[3];
	int	ceiling_rgb[3];
	char	*texture_no;
	char	*texture_so;
	char	*texture_ea;
	char	*texture_we;
}	t_config;

typedef struct s_map
{
	int	width;
	int	height;
	char	**matrix;
	int	player_x;
	int	player_y;
	char	player_dir;
}	t_map;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
}	t_scene;

typedef struct s_color
{
	char	id; 
	int	rgb[3];
}	t_color;

typedef struct s_texture
{
	char	id[3];
	char	*path;
	int	fd;
}	t_texture;


typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	char	*content;
	char	**lines;
	t_color floor;
	t_color ceiling;
	t_texture textures[4];
