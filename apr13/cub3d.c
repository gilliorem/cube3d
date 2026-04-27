#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"
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

typedef struct s_map_3d
{
	char **grid;
	int width;
	int height;

	char *no_tex;
	char *so_tex;
	char *we_tex;
	char *ea_tex;

	int floor_color;
	int ceil_color;

	double player_x;
	double player_y;
	char player_dir;
	//t_sprite sprites[10];
	int num_sprites;
} t_map_3d;


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

typedef struct s_config
{
	t_color		floor;
	t_color		ceiling;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	int		has_floor;
	int		has_ceiling;
	int		has_north;
	int		has_south;
	int		has_east;
	int		has_west;
	int		count;
	int		color_count;
	int		text_count;
	int		map_start;
	int		map_height;
}	t_config;

typedef struct s_map_2d
{
	int	width;
	int	height;
	int	first_line;
	char	**matrix;
	int	player_x;
	int	player_y;
	char	player_dir;
}	t_map_2d;

typedef struct s_scene
{
	t_config	config;
	t_map_2d	map_2d;
	t_map_3d	map_3d;
}	t_scene;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_sprite
{
	double x;
	double y;
	double dist;
}	t_sprite;

typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	char	**lines; 
	int	line_count;
}	t_file;

char	*get_color_value(char *color_line, char color_id);
char	get_color_id(char *line);
int	check_map_line(char *map_line);
t_texture	process_texture(t_file *file, char *id);
t_texture	process_texture_line(char *line);
int	check_texture_path(char *path);
int	get_rgb_component(char *color_value, int index);
int	is_player_char(char c);
int	validate_player(t_map_2d *map_2d);
int	is_walkable_char(char c);
int	validate_map_size(t_map_2d *map_2d);
int	flood_fill_player_area(t_map_2d *map_2d, char *visited, int y, int x);
int	validate_map_enclosure(t_map_2d *map_2d);
void	free_color_lines(char *color_lines[]);
void	free_color_codes(int n, char *color_codes[]);
void	free_file_attributes(t_file *file); // the caller that's gonna call every free func
int	parse_color(t_file *file, char *cur_line, t_config *config);

int	parser_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_str(char *msg, char *value)
{
	ft_putstr_fd(msg, 2);
	if (value)
		ft_putstr_fd(value, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_char(char *msg, char value)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(value, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	parser_error_count(char *msg, int n)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('[', 2);
	ft_putnbr_fd(n, 2);
	ft_putstr_fd("]\n", 2);
	return (0);
}

void	free_data(void *data)
{
	if (!data)
		return ;
	free(data);
}

int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (0);
}

int	check_file_extension(char *filename, char extension[4])
{
	size_t	len;
	size_t	ext_len;
	int	i;

	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	i = 0;

	if (len <= ext_len)
		return (parser_error("file name is too short for the required extension") & 0);
	while (filename[i])
		i++;
	if (filename[i-1] != extension[3] || filename[i-2] != extension[2] || 
		filename[i-3] != extension[1] || filename[i-4] != extension[0])
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

t_file	*init_file(char *argv_one)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	file->name = ft_strdup(argv_one);
	file->line_count = 0;
	
	return file;
}

t_color init_floor(void)
{
	t_color floor;

	floor.id = '\0';
	floor.rgb[0] = 0;
	floor.rgb[1] = 0;
	floor.rgb[2] = 0;
	return (floor);
}

t_color init_ceiling(void)
{
	t_color	ceiling;

	ceiling.id = '\0';
	ceiling.rgb[0] = 0;
	ceiling.rgb[1] = 0;
	ceiling.rgb[2] = 0;
	return (ceiling);
}

t_config	init_config()
{
	t_config	config;
	config.floor = init_floor();
	config.ceiling = init_ceiling();
	config.north = NULL;
	config.south = NULL;
	config.east = NULL;
	config.west = NULL;
	config.has_floor = 0;
	config.has_ceiling = 0;
	config.has_north = 0;
	config.has_south = 0;
	config.has_east = 0;
	config.has_west = 0;
	config.map_height = 0;
	config.count = 0;
	config.color_count = 0;
	config.text_count = 0;
	return (config);
}

enum	e_line_type classify_line(char *line)
{
	if (!line)
		return (INVALID);
	if (line[0] == '\0' || line[0] == '\n')	
		return (EMPTY);
	else if (line[0] == 'F' || line[0] == 'C')
		return (COLOR);
	else if ((line[0] == 'N' && line[1] == 'O')
	|| (line[0] == 'E' && line[1] == 'A')
	|| (line[0] == 'W' && line[1] == 'E')
	|| (line[0] == 'S' && line[1] == 'O'))
		return (TEXTURE);
	else if (ft_strchr("01NSEW", line[0]))
		return (MAP);
	else
		return (INVALID);
}

void	print_line_type(t_file *file)
{
	enum e_line_type line_type;
	for (int i = 0; file->lines[i]; i++)
	{
		line_type = classify_line(file->lines[i]);
		switch (line_type)
		{
			case EMPTY: 
				printf("EMPTY Line[%d]\n", i);
				break;
			case COLOR: 
				printf("COLOR Line[%d]\n", i);
				break;
			case TEXTURE: 
				printf("TEXTURE Line[%d]\n", i);
				break;
			case MAP: 
				printf("MAP Line[%d]\n", i);
				break;
			default: 
				printf("INVALID LINE[%d]\n", i);
				break;
		}
	}
}

int	config_is_complete(t_config *config)
{
	if (config->color_count == 2 && config->text_count == 4)
		return (1);
	return (0);
}

int	register_color_id(t_config *config, char color_id)
{
	if (color_id == 'F')
	{
		if (config->has_floor)
			return (parser_error("duplicate floor color") & 0);
		config->has_floor = 1;
	}
	else if (color_id == 'C')
	{
		if (config->has_ceiling)
			return (parser_error("duplicate ceiling color") & 0);
		config->has_ceiling = 1;
	}
	else
		return (parser_error("invalid color id") & 0);
	config->color_count++;
	config->count++;
	return (1);
}

int	register_texture_id(t_config *config, char texture_id[3])
{
	if (ft_strncmp(texture_id, "NO", 2) == 0)
	{
		if (config->has_north)
			return (parser_error("duplicate north texture") & 0);
		config->has_north = 1;
	}
	else if (ft_strncmp(texture_id, "SO", 2) == 0)
	{
		if (config->has_south)
			return (parser_error("duplicate south texture") & 0);
		config->has_south = 1;
	}
	else if (ft_strncmp(texture_id, "EA", 2) == 0)
	{
		if (config->has_east)
			return (parser_error("duplicate east texture") & 0);
		config->has_east = 1;
	}
	else if (ft_strncmp(texture_id, "WE", 2) == 0)
	{
		if (config->has_west)
			return (parser_error("duplicate west texture") & 0);
		config->has_west = 1;
	}
	else
		return (parser_error("invalid texture id") & 0);
	config->text_count++;
	config->count++;
	return (1);
}

char	*skip_leading_spaces(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ')
		line++;
	return (line);
}

int	parse_lines(t_file *file, t_config *config)
{
	enum	e_state file_state;
	enum	e_line_type line_type;
	int	i;
	char	*cur_line;
	t_texture	texture;
	char	texture_id[3];
	texture_id[2] = '\0';

	i = 0;
	file_state = CONFIG;
	while (file->lines[i])
	{
		cur_line = skip_leading_spaces(file->lines[i]);
		line_type = classify_line(cur_line);
		if (file_state == CONFIG)
		{
			if (line_type == EMPTY)
			{
				i++;
				continue;
			}
			if (line_type == COLOR)
			{
				if (!parse_color(file, cur_line, config))
					return (0);
				if (!register_color_id(config, get_color_id(cur_line)))
					return (0);
				i++;
				continue;
			}
			if (line_type == TEXTURE)
			{
				ft_memcpy(texture_id, cur_line, 2);
				texture_id[2] = '\0';
				if (!register_texture_id(config, texture_id))
					return (0);
				texture = process_texture_line(cur_line);
				if (!texture.path)
					return (0);
				free(texture.path);
				i++;
				continue;
			}
			if (!config_is_complete(config))
				return (parser_error_count("map started before 6 config elements",
						config->count) & 0);
			file_state = IN_MAP;
			config->map_start = i;
		}
		if (!check_map_line(cur_line))
			return (0);
		config->map_height++;
		i++;
		if (file_state == IN_MAP)
		{
			while (file->lines[i])
			{
				cur_line = skip_leading_spaces(file->lines[i]);
				if (!check_map_line(cur_line))
					return (0);
				config->map_height++;
				i++;
			}
			break ;
		}
	}
	if (!config_is_complete(config))
		return (parser_error_count("missing config elements: valid config lines", config->count) & 0);
	if (config->map_height == 0)
		return (parser_error("missing map block") & 0);
	return (1);
}

t_texture	create_texture(char id[3], char *path)
{
	t_texture texture;
	ft_memcpy(texture.id, id, 3);
	texture.path = path;
	texture.fd = -1;
	return (texture);
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
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
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

	file->lines = ft_calloc(file->line_count + 1, sizeof(char *));
	file->fd = try_open_file(file->name);
	if (file->fd == -1)
		return (0);
	i = 0;
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		file->lines[i] = file->cur_line;
		//printf("lines[%d]:%s", i, file->lines[i]);
		i++;
	}
	close(file->fd);
	return (1);
}

void	print_file_lines(t_file *file)
{
	for (int i = 0; file->lines[i]; i++)
	{
		printf("%s", file->lines[i]);
	}
}

void	trim_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
		i++;
	}
}

int	check_color_line(char *color_line, char color_id)
{
	int	i;

	if (!color_line)
		return (parser_error("missing color line") & 0);
	if (color_line[0] != color_id)
		return (parser_error("wrong color id") & 0);
	i = 1;
	if (color_line[i] != ' ')
		return (parser_error("missing space after color id") & 0);
	while (color_line[i] == ' ')
		i++;
	if (!color_line[i])
		return (parser_error("missing color value") & 0);
	while (color_line[i] && color_line[i] != ' ' && color_line[i] != '\n')
	{
		if (!ft_strchr("0123456789,", color_line[i]))
			return (parser_error_char("invalid char in color value: ", color_line[i]) & 0);
		i++;
	}
	while (color_line[i] == ' ')
		i++;
	if (color_line[i] != '\0' && color_line[i] != '\n')
		return (parser_error("invalid trailing chars in color line") & 0);
	return (1);
}

char	*get_color_value(char *color_line, char color_id)
{
	int	i;
	int	start;
	int	end;
	char	*color_value;

	(void)color_id;
	if (!color_line)
		return (NULL);
	i = 1;
	while (color_line[i] == ' ')
		i++;
	start = i;
	while (color_line[i] && color_line[i] != ' ' && color_line[i] != '\n')
		i++;
	end = i;
	color_value = ft_substr(color_line, start, end - start);
	if (!color_value)
		return (NULL);
	return (color_value);
}

int	check_color_value(char *color_value)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (color_value[i])
	{
		if (color_value[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (parser_error("invalid RGB comma count") & 0);
	return (1);
}

char	**get_rgbs(char *color_value)
{
	int	i;
	char	**rgb;

	i = 0;
	rgb = ft_split(color_value, ',');
	if (!rgb)
		return (NULL);
	while (rgb[i])
	{
		if (rgb[i][0] == '\0')
			return (parser_error("invalid RGB format"), NULL);
		if (ft_strlen(rgb[i]) > 3)
			return (parser_error("invalid RGB format"), NULL);
		i++;
	}
	if (i != 3)
		return (parser_error_count("wrong RGB component count", i), NULL);
	return (rgb);
}

int	get_rgb_component(char *color_value, int index)
{
	int		value;
	char	**rgbs;
	int		i;

	rgbs = get_rgbs(color_value);
	if (!rgbs)
		return (-1);
	value = ft_atoi(rgbs[index]);
	i = 0;
	while (rgbs[i])
	{
		free(rgbs[i]);
		i++;
	}
	free(rgbs);
	return (value);
}

int	get_red(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 0));
}

int	get_green(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 1));
}

int	get_blue(char color_id, char *color_value)
{
	(void)color_id;
	return (get_rgb_component(color_value, 2));
}

int	is_rgb_range(int value)
{
	if (value >= 0 && value <= 255)
		return (1);
	return (0);
}

int	check_rgbs(char color_id, char *color_value)
{
	int	red;
	int	green;
	int	blue;

	red = get_red(color_id, color_value);
	if (!is_rgb_range(red))
		return 0;
	green = get_green(color_id, color_value);
	if (!is_rgb_range(green))
		return 0;
	blue = get_blue(color_id, color_value);
	if (!is_rgb_range(blue))
		return 0;
	
	return (1);
}

int	check_color(char *cur_line, char color_id)
{
	char	*color_value;

	if (!check_color_line(cur_line, color_id))
		return (0);
	color_value = get_color_value(cur_line, color_id);
	if (!color_value)
		return (parser_error("failed to extract color value") & 0);
	if (!check_color_value(color_value))
		return (free(color_value), 0);
	if (!check_rgbs(color_id, color_value))
		return (free(color_value), 0);
	free(color_value);
	return (1);
}

char	get_color_id(char *line)
{
	if (line[0] == 'F')
		return ('F');
	if (line[0] == 'C')
		return ('C');
	else
		return ('\0');
}

void	store_color_attributes(char *cur_line, t_color *color, char id)
{
	char	*color_value;

	color_value = get_color_value(cur_line, id);
	if (!color_value)
		return ;
	if (id == 'F')
	{
		color->id = 'F';
		color->rgb[0] = get_red('F', color_value);
		color->rgb[1] = get_green('F', color_value);
		color->rgb[2] = get_blue('F', color_value);
	}
	else if (id == 'C')
	{
		color->id = 'C';
		color->rgb[0] = get_red('C', color_value);
		color->rgb[1] = get_green('C', color_value);
		color->rgb[2] = get_blue('C', color_value);
	}
	free(color_value);
}

int	parse_color(t_file *file, char *cur_line, t_config *config)
{
	char	color_id;

	(void)file;
	color_id = get_color_id(cur_line);
	if (!check_color(cur_line, color_id))
		return 0;
	if (color_id == 'C')
		store_color_attributes(cur_line, &config->ceiling, 'C');
	else if (color_id == 'F')
		store_color_attributes(cur_line, &config->floor, 'F');
	else
		return (parser_error("invalid color id") & 0);
	return (1);
}

void	print_color(t_color *floor, t_color *ceil)
{
	printf("%c ", floor->id);
	printf("%i,", floor->rgb[0]);
	printf("%i,", floor->rgb[1]);
	printf("%i\n", floor->rgb[2]);

	printf("%c ", ceil->id);
	printf("%i,", ceil->rgb[0]);
	printf("%i,", ceil->rgb[1]);
	printf("%i\n", ceil->rgb[2]);
}

char *identify_texture_line(char **lines, char *id)
{
	int i = 0;
	char *line;

	while (lines[i])
	{
		line = skip_leading_spaces(lines[i]);
		if (ft_strncmp(line, id, 2) == 0)
			return (line);
		i++;
	}
	return (NULL);
}

int	check_texture_line(char *line, char *id)
{
	int	i;

	i = 0;
	if (!line)
		return (parser_error("missing texture line") & 0);
	if (ft_strncmp(line, id, 2) != 0)
		return (parser_error("wrong texture id") & 0);
	i = 2;
	if (line[i] != ' ')
		return (parser_error("missing space after texture id") & 0);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (parser_error("missing texture path") & 0);
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (parser_error("invalid trailing chars in texture line") & 0);
	return (1);
}

char	*extract_texture_path(char *line)
{
	int		i;
	int		start;
	int		end;

	i = 2;
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	end = i;
	return (ft_substr(line, start, end - start));
}

t_texture	process_texture(t_file *file, char *id)
{
	char	*line;

	line = identify_texture_line(file->lines, id);
	if (!line)
		return (create_texture("", NULL));
	return (process_texture_line(line));
}

t_texture	process_texture_line(char *line)
{
	char	id[3];
	char	*path;

	ft_memcpy(id, line, 2);
	id[2] = '\0';
	if (!check_texture_line(line, id))
		return (create_texture("", NULL));
	path = extract_texture_path(line);
	if (!path)
		return (create_texture("", NULL));
	if (!check_texture_path(path))
	{
		free(path);
		return (create_texture("", NULL));
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

int	get_line_len_no_newline(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
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

void	print_textures(t_texture texture[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("%s %s\n", texture[i].id, texture[i].path);
		i++;
	}
}

int	is_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);	
	else
		return (parser_error("char is not part of the map charset") & 0);
}

char	*identify_map_line(char *line)
{
	if (ft_strchr(" 1", line[0]))
		return (line);
	return (NULL);
}

int	check_map_line(char *map_line)
{
	int	i;

	i = 0;
	if (map_line[i] == '\n')
		return (parser_error("empty line in map") & 0);
	while (map_line[i] && map_line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", map_line[i]))
			return (parser_error("invalid char in map") & 0);
		i++;
	}
	if (map_line[i] == '\n' && map_line[i + 1] != '\0')
		return (parser_error("invalid char after map newline") & 0);
	return (1);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_walkable_char(char c)
{
	if (c == '0' || is_player_char(c))
		return (1);
	return (0);
}

int	validate_map_size(t_map_2d *map_2d)
{
	if (map_2d->height < 3 || map_2d->width < 3)
		return (parser_error("map too small") & 0);
	return (1);
}

int	get_map_width(t_file *file, t_config *config)
{
	int	max_width;
	int	i;
	int	line_len;

	i = config->map_start;
	max_width = 0;
	while (i < config->map_start + config->map_height)
	{
		line_len = get_line_len_no_newline(file->lines[i]);
		if (line_len > max_width)
			max_width = line_len;
		i++;
	}
	return (max_width);
}

void	init_map_matrix(t_map_2d *map_2d)
{
	int	i;

	i = 0;
	map_2d->matrix = (char **) ft_calloc(map_2d->height + 1, sizeof(char *));
	while (i < map_2d->height)
	{
		map_2d->matrix[i] = (char *) ft_calloc(map_2d->width + 1, sizeof(char));
		ft_memset(map_2d->matrix[i], ' ', map_2d->width);
		i++;
	}
	
}

t_map_2d *init_map(t_file *file, t_config *config)
{
	t_map_2d *map_2d;

	map_2d = ft_calloc(1, sizeof(t_map_2d));
	map_2d->first_line = config->map_start;
	map_2d->height = config->map_height;
	map_2d->width = get_map_width(file, config); // <
	init_map_matrix(map_2d);
	map_2d->player_x = 0;
	map_2d->player_y = 0;
	map_2d->player_dir = 0;
	return (map_2d);		
}

void	fill_map_matrix(t_map_2d *map_2d, t_config *config, t_file *file)
{
	int	i;
	int	j;
	int	len;

	i = config->map_start;
	j = 0;
	while (j < map_2d->height)
	{
		len = ft_strlen(file->lines[i]);
		if (file->lines[i][len - 1] == '\n')
			len--;
		ft_memcpy(map_2d->matrix[j], file->lines[i], len);
		i++;
		j++;
	}
}

int	validate_player(t_map_2d *map_2d)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map_2d->height)
	{
		j = 0;
		while (j < map_2d->width)
		{
			if (is_player_char(map_2d->matrix[i][j]))
			{
				player_count++;
				map_2d->player_y = i;
				map_2d->player_x = j;
				map_2d->player_dir = map_2d->matrix[i][j];
				if (i == 0 || i == map_2d->height - 1 || j == 0 || j == map_2d->width - 1)
					return (parser_error("player on map edge") & 0);
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (parser_error("missing player") & 0);
	if (player_count > 1)
		return (parser_error_count("multiple players", player_count) & 0);
	return (1);
}

int	flood_fill_player_area(t_map_2d *map_2d, char *visited, int y, int x)
{
	int	index;

	if (y < 0 || y >= map_2d->height || x < 0 || x >= map_2d->width)
		return (0);
	if (map_2d->matrix[y][x] == ' ')
		return (0);
	if (!is_walkable_char(map_2d->matrix[y][x]))
		return (1);
	index = y * map_2d->width + x;
	if (visited[index])
		return (1);
	visited[index] = 1;
	if (!flood_fill_player_area(map_2d, visited, y - 1, x))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y + 1, x))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y, x - 1))
		return (0);
	if (!flood_fill_player_area(map_2d, visited, y, x + 1))
		return (0);
	return (1);
}

int	validate_map_enclosure(t_map_2d *map_2d)
{
	char	*visited;
	int		is_closed;

	visited = ft_calloc(map_2d->height * map_2d->width, sizeof(char));
	if (!visited)
		return (parser_error("visited alloc failed") & 0);
	is_closed = flood_fill_player_area(map_2d, visited, map_2d->player_y, map_2d->player_x);
	free(visited);
	if (!is_closed)
		return (parser_error("player area open to void") & 0);
	return (1);
}

void	free_file_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	if (!lines[0])
	{
		free(lines);
		return ;
	}
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

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

void	free_map_data(t_map_2d *map_2d)
{
	int	i;

	if (!map_2d)
		return ;
	if (map_2d->matrix)
	{
		i = 0;
		while (i < map_2d->height)
		{
			free(map_2d->matrix[i]);
			i++;
		}
		free(map_2d->matrix);
	}
	free(map_2d);
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

void	free_file_attributes(t_file *file) // the caller that's gonna call every free func
{
	if (!file)
		return ;
	free_file_lines(file->lines);
	free(file->name);
	free(file);
}

int	rgb_to_hex(int rgb[3])	
{
	int	hex;

	hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];

	return hex;
}


t_map_3d	*init_map_3d(t_map_2d *map_2d, t_config *config, t_texture texture_list[4])
{
	t_map_3d	*map_3d;

	map_3d = ft_calloc(1, sizeof(t_map_3d));
	map_3d->grid = map_2d->matrix;
	map_3d->width = map_2d->width;
	map_3d->height = map_2d->height;
	map_3d->no_tex = texture_list[0].path;
	map_3d->so_tex = texture_list[1].path;
	map_3d->we_tex = texture_list[2].path;
	map_3d->ea_tex = texture_list[3].path;

	map_3d->floor_color = rgb_to_hex(config->floor.rgb);
	map_3d->ceil_color = rgb_to_hex(config->ceiling.rgb);

	map_3d->player_x = (double)map_2d->player_x;
	map_3d->player_y = (double)map_2d->player_y;
	map_3d->player_dir = map_2d->player_dir;

	return (map_3d);
}


int main(int argc, char *argv[])
{
	t_file	*file;
	t_map_2d	*map_2d;
	t_map_3d	*map_3d;
	t_texture	texture_list[4];
	t_config	config;
	int		status;
	int		i;

	if (argc != 2)
		return (print_error(ERR_MSG_ARGC));
	if (!check_argv(argv))
		return (1);
	i = 0;
	while (i < 4)
	{
		texture_list[i].path = NULL;
		i++;
	}
	file = NULL;
	map_2d = NULL;
	status = 1;
	file = init_file(argv[1]);
	config = init_config();
	if (get_file_size(file) && get_file_lines(file) && parse_lines(file, &config))
	{
		map_2d = init_map(file, &config);
		fill_map_matrix(map_2d, &config, file);
		if (validate_map_size(map_2d) && validate_player(map_2d)
			&& validate_map_enclosure(map_2d))
		{
			init_textures(texture_list, file);
			status = 0;
		}
	}
	map_3d = init_map_3d(map_2d, &config, texture_list);
	free_texture_list(texture_list);
	free_map_data(map_2d);
	free(map_3d);
	free_file_attributes(file);
	return (status);
}
