#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
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


char	*process_color_line(t_file *file, char color_id);
t_texture	process_texture(t_file *file, char *id);
void	free_color_lines(char *color_lines[]);
void	free_color_codes(int n, char *color_codes[]);
void	free_rgbs(char **rgb[]);
void	free_file_attributes(t_file *file); // the caller that's gonna call every free func

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

int	check_first_arg(char *argv_zero)
{
	if (ft_strncmp(argv_zero, "./cub3D", ft_strlen("./cub3D")) != 0)
		return 0;
	return 1;
}

int	check_file_extension(char *filename, char extension[4])
{
	int	len; 
	int	i;

	len = ft_strlen(filename);
	i = 0;

	if (len <= ft_strlen(extension))
		return (print_debug("file name has to be at least 1 char long + extension chars", len, NULL) & 0); 
	while (filename[i])
		i++;
	if (filename[i-1] != extension[3] || filename[i-2] != extension[2] || 
		filename[i-3] != extension[1] || filename[i-4] != extension[0])
		return (print_debug("wrong extension\n", -1, filename) & 0);
	return (1);
}

int	check_argv(char *argv[])
{
	if (!check_first_arg(argv[0]) ||
		!check_file_extension(argv[1], ".cub"))
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

void	init_colors(t_color color_list[2])
{
	t_color floor = init_floor();	
	t_color ceiling = init_ceiling();	
	color_list[0] = floor;
	color_list[1] = ceiling;
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
	config.map_height = 0;

	return (config);
}

enum	e_line_type classify_line(char *line)
{
	if (line[0] == '\n')	
		return (EMPTY);
	else if (line[0] == 'F' || line[0] == 'C')
		return (COLOR);
	else if ((line[0] == 'N' && line[1] == 'O')
	|| (line[0] == 'E' && line[1] == 'A')
	|| (line[0] == 'W' && line[1] == 'E')
	|| (line[0] == 'S' && line[1] == 'O'))
	return (TEXTURE);
	else if (line[0] == ' ' || line[0] == '1')
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

int	parse_lines(t_file *file, t_config *config)
{
	enum	e_state file_state;
	enum	e_line_type line_type;
	int	i;
	char	texture_id[3];
	texture_id[2] = '\0';

	i = 0;
	file_state = CONFIG;
	while (file->lines[i])
	{
		line_type = classify_line(file->lines[i]);
		while (file_state == CONFIG)
		{
			line_type = classify_line(file->lines[i]);
			if (line_type == EMPTY)
			{
				//printf("empty line\n");
				i++;
				continue;
			}
			if (line_type == COLOR)
			{
				if (process_color_line(file, file->lines[i][0]) == 0)
				{
					//printf("error parsing color line\n");
					return 0;
				}
				//printf("color line\n");
				i++;
				continue;
			}
			if (line_type == TEXTURE)
			{
				process_texture(file, ft_memcpy(texture_id, file->lines[i], 3));
				//printf("texture line\n");
				i++;
				continue;
			}
			if (line_type == MAP)
			{
				file_state = IN_MAP;
				//printf("first map line>>>:%s",file->lines[i]);
				config->map_start = i;
				config->map_height++;
				// parse_map_line()

				//printf("first map line\n");
				i++;
				continue;
			}
		}
		if (line_type != MAP)
		{
			printf("Error. not a map line\n");
			return 0;
		}
		else 
		{
			//printf("map line\n");
			config->map_height++;
		}
		i++;
	}
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
	int	j;

	file->lines = ft_calloc(file->height + 1, sizeof(char *));
	file->fd = try_open_file(file->name);
	i = 0;
	while (1)
	{
		j = 0;
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
char	*identify_color_line(char **line, char color_id)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == color_id)
		{
			return (line[i]);
		}
		i++;
	}
	return (NULL);
}

// call identify_color_line() in this function or find a way to keep the color_line local (tmp)
// return the checked color_line or have another funciton

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

	trim_new_line(color_line);

	if (!color_line)
		return (printf("error: missing color color_line\n") & 0);
	if (color_line[0] != color_id)
		return (printf("error: wrong color id\n") & 0);
	i = 1;
	if (color_line[i] != ' ')
		return (printf("error: missing space after color id\n") & 0);
	while (color_line[i] == ' ')
		i++;
	if (!color_line[i])
		return (printf("error: missing color value\n") & 0);
	while (color_line[i])
	{
		if (!ft_strchr("0123456789,", color_line[i]))
			return (printf("error: invalid char in color value:%c\n",color_line[i]) & 0);
		i++;
	}
	return (1);
}

char	**split_color_line(char *line)
{
	if (!line)
		return (NULL);
	return (ft_split(line, ' '));
}

char	*process_color_line(t_file *file, char color_id)
{
	char	*color_line;
	char	**color_attributes;
	char	*color_value;
	
	//split_content_in_lines(file);
	color_line = identify_color_line(file->lines, color_id);
	if (!color_line)
		return (NULL);
	if (!check_color_line(color_line, color_id))
		return (NULL);
	color_attributes = split_color_line(color_line);
	color_value = color_attributes[1];
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

char	**split_color_value(char *color_value)
{
	int	i;
	char	**rgb;

	i = 0;
	rgb = ft_split(color_value, ',');
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3)
		{
			printf("error: rgb format");
			return (NULL);
		}
		i++;
	}
	if (i > 3)
	{
		printf("error: rgb format, i:%d\n",i);
		return (NULL);
	}
	return (rgb);
}

void	convert_rgb(t_color *color, char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		color->rgb[i] = ft_atoi (rgb[i]);
		i++;
	}
}

int	is_rgb_range(int value)
{
	if (value >= 0 && value <= 255)
		return (1);
	return (0);
}

int	check_rgb_range(int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_rgb_range(rgb[i]))
			return (printf("rgb not in range\n") & 0);
		i++;
	}
	return (1);
}

int	process_rgb(t_color *color, char *color_value)
{
	char **rgb = split_color_value(color_value);
	if (!check_color_value(color_value))
		return (0);
	convert_rgb(color, rgb);
	if (!check_rgb_range(color->rgb))
		return (0);
	return (1);
}

int	check_color_attributes(t_file *file, t_color color[2])
{
	char	*floor_color;
	char	*ceiling_color;

	floor_color = process_color_line(file, 'F');
	if (!floor_color)
		return (printf("error processing color line\n") & 0);
	ceiling_color = process_color_line(file, 'C');
	if (!ceiling_color)
		return (printf("error processing color line\n") & 0);

	if (!process_rgb(&color[0], floor_color))
		return (0);
	if (!process_rgb(&color[1], ceiling_color))
		return (0);
	color[0].id = 'F';
	color[1].id = 'C';
	return (1);
}

void	print_color(t_color color_list[2])
{
	printf("%c ", color_list[0].id);
	printf("%i,", color_list[0].rgb[0]);
	printf("%i,", color_list[0].rgb[1]);
	printf("%i\n", color_list[0].rgb[2]);

	printf("%c ", color_list[1].id);
	printf("%i,", color_list[1].rgb[0]);
	printf("%i,", color_list[1].rgb[1]);
	printf("%i\n", color_list[1].rgb[2]);
}

/* TEXTURES */

char *identify_texture_line(char **lines, char *id)
{
	int i = 0;

	while (lines[i])
	{
		if (ft_strncmp(lines[i], id, 2) == 0)
			return (lines[i]);
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

char *extract_texture_path(char *line)
{
	int i = 2;

	while (line[i] == ' ')
		i++;

	//printf("%s\n", &line[i]);
	return (&line[i]);
}

t_texture	process_texture(t_file *file, char *id)
{
	char *line;
	char *path;

	line = identify_texture_line(file->lines, id);
	if (!check_texture_line(line, id))
		return (create_texture("", NULL));
	path = extract_texture_path(line);
	t_texture texture = create_texture(id, path);
	return (texture);
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
	if (ft_strchr(map_line, '\n'))
		trim_new_line(map_line);
	while (map_line[i])
	{
		if (!ft_strchr(" 01NSEW\n", map_line[i]))
		{
			printf("invalid char in map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_map_width(t_file *file, t_config *config)
{
	int	max_width;
	int	i;
	int	j;

	i = 0;
	j = 0;
	i+= config->map_start;
	printf("map starts at line:%d\n",i);
	while (file->lines[i])
	{
		j = 0;
		while (file->lines[i][j])
			j++;
		max_width = j - 1;
		if (j > max_width)
			max_width = j - 1;
		i++;
	}
	printf("max width of the map is %d\n", max_width);
	return (max_width);
}

void	init_map_matrix(t_map *map)
{
	int	i;

	i = 0;
	map->matrix = (char **) ft_calloc(map->height + 1, sizeof(char *));
	while (i < map->height)
	{
		map->matrix[i] = (char *) ft_calloc(map->width + 1, sizeof(char *));
		ft_memset(map->matrix[i], ' ', map->width);
		i++;
	}
	
}

t_map *init_map(t_file *file, t_config *config)
{
	t_map *map;
	int	i;

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
	i = 0;
	return (map);		
}

void	fill_map_matrix(t_map *map, t_config *config, t_file *file)
{
	int	i;
	int	j;
	int	len;

	i = config->map_start;
	printf("lines[%d]:%s\n",i, file->lines[i]);
	printf("file height:%d\n", file->height);
	printf("i:%d\n", i);
	j = 0;
	while (j < map->height)
	{
		len = ft_strlen(file->lines[i]);
		if (file->lines[i][len - 1] == '\n')
			len--;
		ft_memcpy(map->matrix[j], file->lines[i], len);
		printf("%s\n", map->matrix[j]);
		i++;
		j++;
	}
}

void	free_file_lines(char **lines)
{
	int	i;

	if (!lines || !lines[0])
		return ;
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

void	free_file_attributes(t_file *file) // the caller that's gonna call every free func
{
	free_color_lines(file->color_lines);
	free_color_codes(file->n_color_lines, file->color_codes);
	free_rgbs(file->rgb);
	free_texture_lines(file->texture_lines);
	free_texture_paths(file->texture_paths);
	free_texture_paths(file->texture_names);

	free_file_lines(file->lines);
	free(file->name);
	free(file);
}

int main(int argc, char *argv[])
{
	t_file	*file;

	if (argc != 2 || !check_argv(argv))
		return (print_error(ERR_MSG_ARGC));
	file = init_file(argv[1]);
	get_file_size(file);
	get_file_lines(file);
	t_config config;
	config = init_config();
	//print_line_type(file);
	parse_lines(file, &config);
	t_map *map = init_map(file, &config);
	fill_map_matrix(map, &config, file);

	return 0;
	t_color color_list[2];
	init_colors(color_list);
	if (!check_color_attributes(file, color_list))
		return (0);
	print_color(color_list);
	t_texture texture_list[4];
	init_textures(texture_list, file);	
	print_textures(texture_list);
}
