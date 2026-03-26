#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"
#define DEBUG_MODE 1

// TODO: get rid of all the temporary variables in this struct:
typedef struct s_color
{
	char	*line; // tmp var
	char	**line_content; // tmp var
	char	id; 
	char	*value; // tmp var
	int	rgb[3];
}	t_color;

typedef struct s_texture
{
	char 	*line; // ignore: tmp var
	char 	**line_content; // ignore: tmp var
	char	id[3];
	char	*path;
	int	fd;
}	t_texture;

typedef struct s_map
{
	int	first_line;
	int	width;
	int	height;
	char	**matrix;
	char	*map_str;
}	t_map;

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

	int	size;

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
	//file->color = ft_calloc(4 + 1, sizeof(char **));
	//file->texture = ft_calloc(4 + 1, sizeof(char **));
	
	printf("file init\n");
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

// does it make sense to init the north id with the actual value "NO\0" straight away
// or do we want to initialize with 0 before extracting it from the file 
// so we can check if the str from the file is correct ?

t_texture	init_north(void)
{
	t_texture north;
	ft_memcpy("\0\0\0", north.id, 3);
			
	return north;
}

// before calling create texture, 
// we need to validate id and path. 
/* Small important point:
	texture.path = path; only stores the pointer
	that is fine if path points inside file->lines / file->content and those stay alive long enough
*/
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
	int	max_width;
	int	height;

	file->fd = try_open_file(file->name);
	i = 0;
	max_width = 0;
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
		if (j > max_width)
			max_width = j;
	}
	height = i;
	file->size = i * max_width;
	close(file->fd);
}

void	store_file_content(t_file *file)
{
	int	i;
	int	j;
	int	total_bytes;

	i = 0;
	total_bytes = 0;
	file->fd = try_open_file(file->name);
	file->content = ft_calloc(file->size, 1);
	while (1)
	{
		j = 0;
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		while (file->cur_line[j])
			j++;
		ft_memcpy(file->content + total_bytes, file->cur_line, j);
		total_bytes += j;
		free(file->cur_line);
	}
	//printf("file content: %s", file->content);
	close(file->fd);
}

void	split_content_in_lines(t_file *file)
{
	file->lines = ft_split (file->content, '\n');
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
int	check_color_line(char *color_line, char color_id)
{
	int	i;

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
			return (printf("error: invalid char in color value\n") & 0);
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
	
	split_content_in_lines(file);
	color_line = identify_color_line(file->lines, color_id);
	if (!check_color_line(color_line, color_id))
		return (0);
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
	ceiling_color = process_color_line(file, 'C');

	if (!process_rgb(&color[0], floor_color))
		return (0);
	if (!process_rgb(&color[1], ceiling_color))
		return (0);
	return (1);
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

	printf("%s\n", &line[i]);
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

int	find_endline_first_part(t_file *file)
{
	int	end;

	if (file->line_count_color >= file->line_count_texture)
		end = file->line_count_color;
	else
		end = file->line_count_texture;
	return (end);
}

int	is_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0')
		return (1);	
	else
		return (print_debug("Error. char is not part of the map charset", -1, NULL) & 0);
}

int	find_map_first_line(t_file *file)
{
	int	first_line;
	int	end_first_part;
	int	i;
	int	start_flag;
	int	bad_char_flag;
	char	*last_line;
	
	last_line = NULL;
	start_flag = 0;
	bad_char_flag = 0;
	end_first_part = find_endline_first_part(file);
	i = 0;
	file->fd = try_open_file(file->name);
	while (i < end_first_part)
	{
		file->cur_line = get_next_line(file->fd);
		i++;
		if (i != end_first_part)
			free(file->cur_line);
	}
	print_debug("last text line of first part:", i, NULL);

	//TODO: This loop will also count the empty lines within the MAP. 
	//Fix it with a function that checks if we are in the map; if thats the case,
	//dont increment i.
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		if (file->cur_line[0] == '\n')
		{
			free(last_line);
			last_line = file->cur_line;
			i++;
			continue;
		}
		free(file->cur_line);
	}
	end_first_part = i;
	free(file->cur_line);
	print_debug("last line first part:", end_first_part, last_line);
	free(last_line);
	i = 0;
	close(file->fd);
	try_open_file(file->name);
	while (i < end_first_part)
	{
		file->cur_line = get_next_line(file->fd);
		i++;
	}
	int j = 0;
	while (1)
	{
		j = 0;
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break ;
		if (start_flag == 0 && is_map_char(file->cur_line[0]))
		{
			start_flag = 1;
			first_line = i;
			print_debug("map is starting at line:", first_line, file->cur_line);
		}
		if (bad_char_flag == 0 && start_flag == 1 && !is_map_char(file->cur_line[0]))
		{
			bad_char_flag = 1;
			print_debug("bad char found in map, in line:", i, NULL);
		}
		i++;
		file->map_lines++;
		while (file->cur_line[j] != '\n')
			j++;
		if (j > file->longest_map_line)
			file->longest_map_line = j;

		free(file->cur_line);
	}
	if (bad_char_flag == 1)
		return (print_debug("Error bad char in map", -1, NULL) & 0);
	if (start_flag == 0)
		return (print_debug("Error could not find map", -1, NULL) & 0);
	close(file->fd);
	//printf("map height:%d\nmap width:%d\n", file->map_lines, file->longest_map_line);
	return (first_line);
}

// what about I make a file containing the map only.
// toujours plussssss 
t_map	*init_map(t_file *file)
{
	t_map	*map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	map = ft_calloc(1, sizeof(t_map));
	map->first_line = find_map_first_line(file);
	if (map->first_line == 0)
		return (NULL);
	map->height = file->map_lines;
	map->width = file->longest_map_line;
	map->matrix = (char**)ft_calloc(map->height, sizeof(char *) + 1);
	while (i < map->height)
	{
		map->matrix[i] = (char*) ft_calloc(map->width, sizeof(char) + 1);
		i++;
	}
	i = 0;
	//printf("\nmap height:%d, map max-width:%d\n", map->height, map->width);
	while (i < map->height) 
	{
		j = 0;
		while (j < map->width)
		{
			map->matrix[i][j] = ' ';
			//printf("%c", map->matrix[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	file->fd = try_open_file(file->name);
	while (i < map->first_line)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		i++;
	}
	i = 0;
	int line_len;
	while (i < map->height)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		line_len = ft_strlen(file->cur_line);
		j = 0;
		while (j < (line_len - 1))
		{
			map->matrix[i][j] = file->cur_line[j];
			//printf("%c", map->matrix[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	printf("----MAP----\n");
	while (i < map->height) 
	{
		j = 0;
		while (j < map->width)
		{
			//map->matrix[i][j] = 'X';
			printf("%c", map->matrix[i][j]);
			j++;
		}
		putchar('\n');
		i++;
	}
	return (map);
}

void	check_for_all_char(t_map *map)
{
	char	*map_str;
	char	*temp;
	int	i;

	map_str = ft_strdup("");
	i = 0;
	while (i < map->height)
	{
		temp = ft_strjoin(map_str, map->matrix[i]);
		//printf("map str: %s\n", map_str);
		//printf("temp:%s", temp);
		map_str = ft_strdup(temp);
		free(temp);
		i++;
	}	
	printf("map string:%s\n", map_str);
}

int	check_map_valid_char(t_file *file, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_strchr(" 10NSEW", map->matrix[i][j]))
			{
				return (print_debug("error: wrong char found in map:", map->matrix[i][j], NULL) & 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
void	get_map_dimension(t_file *file, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	file->fd = try_open_file(file->name);
	while (i < map->first_line)
	{
		file->cur_line = get_next_line(file->fd);
		i++;
	}
	while (1)
	{
		j = 0;
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		while (file->cur_line[j])
			j++;
		map->width = j;
		if (j > map->width)
			map->width = j;
		free(file->cur_line);
		i++;
	}
	file->map_lines = i;
	close(file->fd);
	print_debug("longest line in map:", file->longest_map_line, NULL);
	print_debug("lines in map:", file->map_lines, NULL);
}
*/

//keep in mind that we now have 1 + (1 x lines) pointers to free
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
	free_data(file->content);
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
	store_file_content(file);
	t_color color_list[2];
	init_colors(color_list);
	if (!check_color_attributes(file, color_list))
		return (0);
	t_texture texture_list[4];
	init_textures(texture_list, file);	
}
