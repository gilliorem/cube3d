#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"
#define DEBUG_MODE 1

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

typedef struct s_map
{
	int	width;
	int	height;
	int	first_line;
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

typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	char	**lines; 
	t_color floor; // no need
	t_color ceiling; // no need
	t_texture textures[4]; // no need
	int	max_width;
	int	height;
	int	size; // no need

	//TODO: re-structure the file attributes
	int	line_count_color;// > make this var a tmp in the check function
	int	n_color_lines;// > make this var a tmp in the check function
	char	*color_lines[2];//> make this var a tmp in the check function
	char 	*color_codes[2];//> make this var a tmp in the check function
	char	**rgb[2];//> make this var a tmp in the check function
	int	line_count_texture;//> make this var a tmp in the check function
	char	*texture_lines[4];//> make this var a tmp in the check function
	char	*texture_paths[4];//> make this var a tmp in the check function
	char	*texture_names[4];//> make this var a tmp in the check function
	int	textures_fds[4];//> make this var a tmp in the check function
	int	longest_map_line;//> make this var a tmp in the check function
	int	map_lines;//> make this var a tmp in the check function
	t_map	*map;//> file should not point to map
	//char	**map;// // as it is in the file (with the '\n')
}	t_file;


char	*get_color_value(char *color_line, char color_id);
char	get_color_id(char *line);
int	check_map_line(char *map_line);
t_texture	process_texture(t_file *file, char *id);
t_texture	process_texture_line(char *line);
int	check_texture_path(char *path);
int	get_rgb_component(char *color_value, int index);
int	is_player_char(char c);
int	validate_player(t_map *map);
int	is_walkable_char(char c);
int	validate_map_size(t_map *map);
int	flood_fill_player_area(t_map *map, char *visited, int y, int x);
int	validate_map_enclosure(t_map *map);
void	free_color_lines(char *color_lines[]);
void	free_color_codes(int n, char *color_codes[]);
void	free_rgbs(char **rgb[]);
void	free_file_attributes(t_file *file); // the caller that's gonna call every free func

//int	check_color_attributes(t_file *file, t_color *floor, t_color *ceil);
int	parse_color(t_file *file, char *cur_line, t_config *config);

int	print_debug(char *err_msg, int n, char *s)
{
	if (DEBUG_MODE == 1)
	{
		if (s != NULL && n != -1)
		{
			printf("%s", err_msg);
			printf("%d", n);
			printf("%s", s);
			return 0;
		}
		if (n != -1)
		{
			printf("%s[%d]\n", err_msg, n);
			return 0;
		}
		if (n == -1 && s != NULL)
		{
			printf("%s %s\n", err_msg, s);
			return 0;
		}
		else
			printf("%s\n", err_msg);
	}
	return 0;
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
		return (print_debug("file name has to be at least 1 char long + extension chars", (int)len, NULL) & 0);
	while (filename[i])
		i++;
	if (filename[i-1] != extension[3] || filename[i-2] != extension[2] || 
		filename[i-3] != extension[1] || filename[i-4] != extension[0])
		return (print_debug("wrong extension\n", -1, filename) & 0);
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

	fd = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("invalid file\n");
		return 0;
	}
	return fd;
}

t_file	*init_file(char *argv_one)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	file->name = ft_strdup(argv_one);
	file->n_color_lines = 2;
	file->max_width = 0;
	file->height = 0;
	
	//printf("file init\n");
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

// should this fn returns a pointer to config instead ?
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
			return (print_debug("duplicate floor color", -1, NULL) & 0);
		config->has_floor = 1;
	}
	else if (color_id == 'C')
	{
		if (config->has_ceiling)
			return (print_debug("duplicate ceiling color", -1, NULL) & 0);
		config->has_ceiling = 1;
	}
	else
		return (print_debug("invalid color id", -1, NULL) & 0);
	config->color_count++;
	config->count++;
	return (1);
}

int	register_texture_id(t_config *config, char texture_id[3])
{
	if (ft_strncmp(texture_id, "NO", 2) == 0)
	{
		if (config->has_north)
			return (print_debug("duplicate north texture", -1, NULL) & 0);
		config->has_north = 1;
	}
	else if (ft_strncmp(texture_id, "SO", 2) == 0)
	{
		if (config->has_south)
			return (print_debug("duplicate south texture", -1, NULL) & 0);
		config->has_south = 1;
	}
	else if (ft_strncmp(texture_id, "EA", 2) == 0)
	{
		if (config->has_east)
			return (print_debug("duplicate east texture", -1, NULL) & 0);
		config->has_east = 1;
	}
	else if (ft_strncmp(texture_id, "WE", 2) == 0)
	{
		if (config->has_west)
			return (print_debug("duplicate west texture", -1, NULL) & 0);
		config->has_west = 1;
	}
	else
		return (print_debug("invalid texture id", -1, NULL) & 0);
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

// I need to have 6 config lines
// 	2 color
// 	4 textures
// 	config->count => color_count+text_count
// 	config->color_count 
// 	config->text_count

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
				return (print_debug("map started before 6 config elements",
						config->count, NULL) & 0);
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
		return (print_debug("missing config elements at EOF", config->count, NULL) & 0);
	if (config->map_height == 0)
		return (print_debug("missing map block", -1, NULL) & 0);
	return (1);
}

t_texture	create_texture(char id[3], char *path)
{
	t_texture texture;
	ft_memcpy(texture.id, id, 3);
	//ft_memcpy(texture.path, path, ft_strlen(path));
	texture.path = path;
	texture.fd = -1;
	return (texture);
}

void	get_file_size(t_file *file)
{
	int	i;
	int	j;

	file->fd = try_open_file(file->name);
	i = 0;
	file->max_width = 0;
	while (1)
	{
		j = 0;
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		while (file->cur_line[j])
			j++;
		free(file->cur_line);
		i++;
		if (j > file->max_width)
			file->max_width = j;
	}
	file->height = i;
	file->size = i * file->max_width;
	close(file->fd);
}

void	get_file_lines(t_file *file)
{
	int	i;

	file->lines = ft_calloc(file->height + 1, sizeof(char *));
	file->fd = try_open_file(file->name);
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
}

void	print_file_lines(t_file *file)
{
	for (int i = 0; file->lines[i]; i++)
	{
		printf("%s", file->lines[i]);
	}
}

// ["FC ,0123456789"]


// switch file to line
// in the function call, use file->lines

// call identify_color_line() in this function or find a way to keep the color_line local (tmp)
// return the checked color_line or have another funciton

/* COLOR */

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
		return (printf("error: missing color_line\n") & 0);
	if (color_line[0] != color_id)
		return (printf("error: wrong color id\n") & 0);
	i = 1;
	if (color_line[i] != ' ')
		return (printf("error: missing space after color id\n") & 0);
	while (color_line[i] == ' ')
		i++;
	if (!color_line[i])
		return (printf("error: missing color value\n") & 0);
	while (color_line[i] && color_line[i] != ' ' && color_line[i] != '\n')
	{
		if (!ft_strchr("0123456789,", color_line[i]))
			return (printf("error: invalid char in color value:%c\n",color_line[i]) & 0);
		i++;
	}
	while (color_line[i] == ' ')
		i++;
	if (color_line[i] != '\0' && color_line[i] != '\n')
		return (printf("error: invalid trailing chars in color line\n") & 0);
	return (1);
}
		/* END OF COLOR LINE*/

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
		return (printf("error rgb commas count\n") & 0);
	return (1);
}
	/* END OF COLOR ATTRIBUTE[1] */

	/* COLOR CODE (RGB) */
char	**get_rgbs(char *color_value)
{
	int	i;
	char	**rgb;

	i = 0;
	rgb = ft_split(color_value, ',');
	while (rgb[i])
	{
		if (rgb[i][0] == '\0')
		{
			printf("error: rgb format\n");
			return (NULL);
		}
		if (ft_strlen(rgb[i]) > 3)
		{
			printf("error: rgb format\n");
			return (NULL);
		}
		i++;
	}
	if (i != 3)
	{
		printf("error: rgb format, i:%d\n", i);
		return (NULL);
	}
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
	/* END OF COLOR CODE (RGB) */

/*
int	check_color_attributes(t_file *file, t_color *floor, t_color *ceil)
{
	char	*floor_color;
	char	*ceiling_color;

	floor_color = get_color_value(file, 'F');
	if (!floor_color)
		return (printf("error processing color line\n") & 0);
	ceiling_color = get_color_value(file, 'C');
	if (!ceiling_color)
		return (printf("error processing color line\n") & 0);

	if (!process_rgb(floor, floor_color))
		return (0);
	if (!process_rgb(ceil, ceiling_color))
		return (0);
	floor[0].id = 'F';
	ceil[0].id = 'C';
	return (1);
}
*/

int	check_color(char *cur_line, char color_id)
{
	char	*color_value;

	if (!check_color_line(cur_line, color_id))
		return (printf("Error in color line\n") & 0);
	color_value = get_color_value(cur_line, color_id);
	if (!color_value)
		return (printf("Error extracting color value\n") & 0);
	if (!check_color_value(color_value))
		return (free(color_value), printf("Error in color value\n") & 0);
	if (!check_rgbs(color_id, color_value))
		return (free(color_value), printf("Error in RGB value\n") & 0);
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

//TODO: Convert into hex code (color)
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

// now that colors are checked, need their attributes
// need to store in config data struct C and F
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
	{
		printf("Error color id\n");
		return (0);
	}
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

/* TEXTURES */

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

int check_texture_line(char *line, char *id)
{
	int i;
       
	i = 0;
	if (!line)
		return (printf("missing texture\n") & 0);
	if (ft_strncmp(line, id, 2) != 0)
		return (printf("wrong texture id\n") & 0);
	i = 2;
	if (line[i] != ' ')
		return (printf("missing space\n") & 0);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && line[i] == '\n')	
		return (printf("wrong char\n") & 0);
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (printf("wrong char\n") & 0);
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

// check filename was doing:
// if there is a `/`, jump to it
// if not filemane is the path (str passed)
// check extension
// check presence of special char

// check filenames: checked the filenames in the 4 xpm files

int	check_valid_fd(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		return (print_debug("could not open file:", -1, file_path) & 0);
	}
	close(fd);
	return (1);
}

int	check_texture_path(char *path)
{
	struct stat	path_stat;

	if (!path || path[0] == '\0')
		return (print_debug("missing texture path", -1, NULL) & 0);
	if (!check_file_extension(path, ".xpm"))
		return (print_debug("texture is not .xpm", -1, path) & 0);
	if (stat(path, &path_stat) == -1)
		return (print_debug("texture path stat failed", -1, path) & 0);
	if (S_ISDIR(path_stat.st_mode))
		return (print_debug("texture path is a directory", -1, path) & 0);
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

// we can go through our file content line by line and check the lines:
// it can be
// - empty line
// - config line
// 	- color
// 	- texture
// - map line (0 1NSEW)


int	is_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);	
	else
		return (print_debug("Error. char is not part of the map charset", -1, NULL) & 0);
}

// no empty line: no \n alone
// can have \n after map char
// do I want to trim the new line ?
// 	first identify
// 	validate
// 	parse

// should this function return void instead ?
/*
char	*identify_map_line(char *line, char map_id)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
	{
		printf("error: find empty line in map line\n");
		return (NULL);
	}
	if (ft_strchr(line, '\n'))
		trim_new_line(line);
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
		{
			printf("invalid char in map\n");
			return (NULL);
		}
		i++;
	}
	return (line);
}
*/

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
	{
		printf("error: find empty line in map.\n");
		return (0);
	}
	while (map_line[i] && map_line[i] != '\n')
	{
		if (!ft_strchr(" 01NSEW", map_line[i]))
		{
			printf("invalid char in map\n");
			return (0);
		}
		i++;
	}
	if (map_line[i] == '\n' && map_line[i + 1] != '\0')
		return (printf("invalid char after map newline\n") & 0);
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

int	validate_map_size(t_map *map)
{
	if (map->height < 3 || map->width < 3)
		return (print_debug("map too small", -1, NULL) & 0);
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

void	init_map_matrix(t_map *map)
{
	int	i;

	i = 0;
	map->matrix = (char **) ft_calloc(map->height + 1, sizeof(char *));
	while (i < map->height)
	{
		map->matrix[i] = (char *) ft_calloc(map->width + 1, sizeof(char));
		ft_memset(map->matrix[i], ' ', map->width);
		i++;
	}
	
}

t_map *init_map(t_file *file, t_config *config)
{
	t_map *map;

	map = ft_calloc(1, sizeof(t_map));
	map->first_line = config->map_start;
	map->height = config->map_height;
	map->width = get_map_width(file, config); // <
	init_map_matrix(map);
	//for (int i = 0; map->matrix[i]; i++)
	//	printf("%s\n", map->matrix[i]);
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
	return (map);		
}

void	fill_map_matrix(t_map *map, t_config *config, t_file *file)
{
	int	i;
	int	j;
	int	len;

	i = config->map_start;
	j = 0;
	while (j < map->height)
	{
		len = ft_strlen(file->lines[i]);
		if (file->lines[i][len - 1] == '\n')
			len--;
		ft_memcpy(map->matrix[j], file->lines[i], len);
		i++;
		j++;
	}
}

int	validate_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player_char(map->matrix[i][j]))
			{
				player_count++;
				map->player_y = i;
				map->player_x = j;
				map->player_dir = map->matrix[i][j];
				if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
					return (print_debug("player on map edge", -1, NULL) & 0);
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (print_debug("missing player", -1, NULL) & 0);
	if (player_count > 1)
		return (print_debug("multiple players", player_count, NULL) & 0);
	return (1);
}

int	flood_fill_player_area(t_map *map, char *visited, int y, int x)
{
	int	index;

	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map->matrix[y][x] == ' ')
		return (0);
	if (!is_walkable_char(map->matrix[y][x]))
		return (1);
	index = y * map->width + x;
	if (visited[index])
		return (1);
	visited[index] = 1;
	if (!flood_fill_player_area(map, visited, y - 1, x))
		return (0);
	if (!flood_fill_player_area(map, visited, y + 1, x))
		return (0);
	if (!flood_fill_player_area(map, visited, y, x - 1))
		return (0);
	if (!flood_fill_player_area(map, visited, y, x + 1))
		return (0);
	return (1);
}

int	validate_map_enclosure(t_map *map)
{
	char	*visited;
	int		is_closed;

	visited = ft_calloc(map->height * map->width, sizeof(char));
	if (!visited)
		return (print_debug("visited alloc failed", -1, NULL) & 0);
	is_closed = flood_fill_player_area(map, visited, map->player_y, map->player_x);
	free(visited);
	if (!is_closed)
		return (print_debug("player area open to void", -1, NULL) & 0);
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

void	free_rgbs(char **rgb[])
{
	int	i;
	int	j;

	if (!rgb || !rgb[0] || !rgb[0][0])
		return ;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 3)
		{
			free(rgb[i][j]);
			j++;
		}
		free(rgb[i]);
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

void	free_texture_paths(char *texture_paths[])
{
	int	i;

	if (!texture_paths || !texture_paths[0])
		return ;
	i = 0;
	while (i < 4)
	{
		free(texture_paths[i]);
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

void	free_map_data(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->matrix)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->matrix[i]);
			i++;
		}
		free(map->matrix);
	}
	free(map);
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

int main(int argc, char *argv[])
{
	t_file	*file;
	t_map	*map;
	t_texture	texture_list[4];
	t_config	config;
	int		status;
	int		i;

	if (argc != 2 || !check_argv(argv))
		return (print_error(ERR_MSG_ARGC));
	i = 0;
	while (i < 4)
	{
		texture_list[i].path = NULL;
		i++;
	}
	file = NULL;
	map = NULL;
	status = 1;
	file = init_file(argv[1]);
	get_file_size(file);
	get_file_lines(file);
	config = init_config();
	if (parse_lines(file, &config))
	{
		map = init_map(file, &config);
		fill_map_matrix(map, &config, file);
		if (validate_map_size(map) && validate_player(map)
			&& validate_map_enclosure(map))
		{
			init_textures(texture_list, file);
			status = 0;
		}
	}
	free_texture_list(texture_list);
	free_map_data(map);
	free_file_attributes(file);
	return (status);
}
