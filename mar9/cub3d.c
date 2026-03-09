#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"
#define DEBUG_MODE 1

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

	int	size;

	//TODO: re-structure the file attributes
	int	line_count_color;
	int	n_color_lines;
	char	*color_lines[2];
	char 	*color_codes[2];
	char	**rgb[2];
	int	line_count_texture;
	char	*texture_lines[4];
	char	*texture_paths[4];
	char	*texture_names[4];
	int	textures_fds[4];
	int	longest_map_line;
	int	map_lines;
	t_map	*map;
	//char	**map; // as it is in the file (with the '\n')
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
			//printf("%s[%d][%s]\n", err_msg, n, s);
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
		else
			printf("%s\n", err_msg);
	}
	return 0;
}

void	free_data(void *data)
{
	if (data)
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

	if (len <= ft_strlen(extension)) // has to be longer than '.cub'
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

// NO SO WE EA
// 	open file <- check
// 	check first line <- (empty/wrong char/misplace/no space/ 2 spaces.../

int	try_open_file(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return printf("invalid file\n") & 0;
	return fd;
}

t_file	*init_file(char *argv_one)
{
	t_file	*file;

	file = ft_calloc(1, sizeof(t_file));
	file->name = ft_strdup(argv_one);
	file->n_color_lines = 2;
	//file->textures = ft_calloc(4 + 1, sizeof(char **));
	return file;
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
	printf("map size = h * w = %d * %d = %d\n", height, max_width, file->size);
	close(file->fd);
}

void	store_file_data(t_file *file)
{
	int	i;
	int	j;
	int	total_bytes;

	i = 0;
	total_bytes = 0;
	file->fd = try_open_file(file->name);
	printf("file fd:%d\n", file->fd);
	file->content = ft_calloc(file->size, 1);
	printf("file size:%d\n", file->size);
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
	printf("file content: %s", file->content);
	free(file->content);
}


//TODO: Remove the read file part: only check the color_type_id on
//	a already existing buffer
int	check_color_type_id(t_file *file)
{
	bool	color_type_id[2];
	int	count;
	int	i;
	int	flag;

	color_type_id[0] = false;
	color_type_id[1] = false;
	count = 0;
	i = 1;
	flag = 0;
	file->fd = try_open_file(file->name);
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;// reach EOF
		if (file->cur_line[0] == 'F' && file->cur_line[1] == ' ')
		{
			count++;
			color_type_id[0] = true;
			file->color_lines[0] = ft_strdup(file->cur_line);
		}
		if (file->cur_line[0] == 'C' && file->cur_line[1] == ' ')
		{
			count++;
			color_type_id[1] = true;
			file->color_lines[1] = ft_strdup(file->cur_line);
		}
		if (color_type_id[0] == true && color_type_id[1] == true && count == 2 && flag == 0)
		{
			file->line_count_color = i;
			flag = 1;
		}
		free(file->cur_line);
		i++;
	}
	if (color_type_id[0] == true && color_type_id[1] == true && count == 2)
	{
		//print_debug("valid colors type ID F C.\ncolor lines stored", -1, NULL);
		print_debug("Line of the last color found:", file->line_count_color, NULL);
		close(file->fd);
		return (1);
	}
	print_debug("Invalid colors type id; count=", count, NULL);
	close(file->fd);
	free_file_attributes(file);
	return (0);
}

int	check_texture_type_id(t_file *file)
{
	bool	texture_type_id[4];
	int	count;
	int	i;
	int	flag;

	count = 0;
	i = 1;
	flag = 0;
	while (count < 4)
		texture_type_id[count++] = false;
	count = 0;
	file->fd = try_open_file(file->name);
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;
		if (file->cur_line[0] == 'N' && file->cur_line[1] == 'O' && file->cur_line[2] == ' ')
		{
			count++;
			texture_type_id[0] = true;
			file->texture_lines[0] = ft_strdup(file->cur_line);
		}
		if (file->cur_line[0] == 'S' && file->cur_line[1] == 'O' && file->cur_line[2] == ' ')
		{
			count++;
			texture_type_id[1] = true;
			file->texture_lines[1] = ft_strdup(file->cur_line);
		}
		if (file->cur_line[0] == 'E' && file->cur_line[1] == 'A' && file->cur_line[2] == ' ')
		{
			count++;
			texture_type_id[2] = true;
			file->texture_lines[2] = ft_strdup(file->cur_line);
		}
		if (file->cur_line[0] == 'W' && file->cur_line[1] == 'E' && file->cur_line[2] == ' ')
		{
			count++;
			texture_type_id[3] = true;
			file->texture_lines[3] = ft_strdup(file->cur_line);
		}
		if (texture_type_id[0] == true && texture_type_id[1] == true 
		&& texture_type_id[2] == true && texture_type_id[3] == true 
		&& count == 4 && flag == 0)
		{
			flag = 1;
			file->line_count_texture = i;
		}
		i++;
		free(file->cur_line);
	}
	if (texture_type_id[0] == true && texture_type_id[1] == true 
		&& texture_type_id[2] == true && texture_type_id[3] == true 
		&& count == 4)
	{
		//print_debug("valid textures type id.\ntextures lines stored", -1, NULL);
		print_debug("Line number of last texture line:", file->line_count_texture, NULL);
		close(file->fd);
		return (1);
	}
	print_debug("Error\nInvalid textures type id; count:", count, NULL);
	close(file->fd);
	free_file_attributes(file);
	return (0);
}

int	is_rgb_range(int value)
{
	if (value >= 0 && value <= 255)
		return (1);
	return (0);
}

// skip the spaces in the color line and store the pointer to the first character that is not a <space>
char	*extract_color_code(t_file *file, char *color_line)
{
	char	*substr;
	int	start;
	int	len;
	int	i;

	start = 1;
	i = 0;
	len = 0;
	while (color_line[start] == ' ')
		start++;
	while (color_line[i + start] != '\n')
	{
		len++;
		i++;
	}
	substr = (ft_substr(color_line, start, len));
	//print_debug("color code:", -1, substr);
	return (substr);
}

char	*extract_texture_path(t_file *file, char *texture_line)
{
	char	*texture_path;
	int	start;
	int	len;
	int	i;

	start = 2;
	i = 0;
	len = 0;
	while (texture_line[start] == ' ')
		start++;
	while (texture_line[i + start] != '\n')
	{
		len++;
		i++;
	}
	texture_path = (ft_substr(texture_line, start, len));
	//print_debug("texture path:", -1, texture_path);
	return (texture_path);
}

void	extract_texture_paths(t_file *file)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		file->texture_paths[i] = extract_texture_path(file, file->texture_lines[i]);
		i++;
	}
}

// check the filename independanlty from the extension
// 'I am not responsible for the user's directory, I should only check for the filename' ./dir/dir/filename.xpm
//  Separate the filename from the rest of the path: I can 'walk backwards' from the .xpm; look for the next '/' or, the '<space>' 
//  from forward: mark the last '/' if there is one or mark the first char after the last '<space>' go until the ".xpm"
// make a substr out of the filename 


// simplify this function: start from the last char and go back to the extension.
int	check_filename(char *path, char extension[4], char *texture_name)
{
	// jump to the last slash
	int	i;
	char	*filename;
	char	*extension_ptr;

	i = 0;
	if (!ft_strchr(path, '/'))
		filename = &path[i];
	while (ft_strchr(&path[i], '/'))
	{
		filename = ft_strchr(&path[i], '/');
		filename++;
		i++;
	}
	//print_debug("filename:", -1, filename);
	if (!check_file_extension(filename, extension))
		return (0);
	extension_ptr = ft_strnstr(filename, extension, ft_strlen(filename));
	/*
	if (ft_strncmp(extension_ptr, extension, ft_strlen(extension)) != 0)
	{
		extension_ptr += ft_strlen(extension_ptr);
		extension_ptr = ft_strnstr(extension_ptr, extension, ft_strlen(extension_ptr));
	}
	*/
	if (!extension_ptr)
		return (print_debug("error, extension.", -1, NULL) & 0);
	//print_debug("extension ptr:", -1, extension_ptr);

	int ext_len = 4;
	int name_len = ft_strlen(filename) - ext_len;

	texture_name = ft_calloc(name_len + 1, sizeof(char));
	ft_memmove(texture_name, filename, name_len);
	//print_debug("Texture name:", -1, texture_name);
	
	i = 0;
	while (texture_name[i])
	{
		if (ft_strchr("#%&{}\\<>*?/$!'\":@+`|= ", texture_name[i]))
		{
			return (print_debug("Error:invalid char in texture filename", -1, texture_name) & 0);
		}
		i++;
	}
	free(texture_name);
	return (1);
}

int	check_filenames(t_file *file)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_filename(file->texture_paths[i], ".xpm", file->texture_names[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_valid_fd(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	else
		return (print_debug("could not open file:", -1, file_path) & 0);
}

int	check_textures_fds(t_file *file)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!check_valid_fd(file->texture_paths[i]))
			return (0);
		i++;
	}
	return (1);
}

void	extract_color_codes(t_file *file)
{
	int	i;
	
	i = 0;
	while (i < 2)
	{
		file->color_codes[i] = extract_color_code(file, file->color_lines[i]);
		i++;
	}
}

int	check_color_format(t_file *file, char *color_code)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	//print_debug(">color code:", -1, color_code);
	while (color_code[i])
	{
		if (!ft_strchr("0123456789,",color_code[i]))
		{
			free_file_attributes(file);
			return (print_debug("Error", -1, "RGB Wrong format") & 0);
		}
		else if (color_code[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
	{
		free_file_attributes(file);
		return (print_debug("Error", -1, "RGB wrong format(need to have 2 commas)") & 0);
	}
	return (1);
}

int	check_colors_format(t_file *file)
{
	int	i;

	i = 0;
	while (i < file->n_color_lines)
	{
		if (!check_color_format(file, file->color_codes[i]))
			return (0);
		i++;
	}
	return (1);
}

void	split_rgb(t_file *file)
{
	int	i;
	int	j;

	i = 0;
	while (i < file->n_color_lines)
	{
		file->rgb[i] = ft_split(file->color_codes[i], ',');
		i++;
	}
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 3)
		{
			//print_debug(">", -1, file->rgb[i][j]);
			j++;
		}
		i++;
	}
}

int	check_rgb(t_file *file)
{

	int	i;
	int	j;
	int	n_rgb;

	i = 0;
	n_rgb = 0;
	split_rgb(file);
	while (i < 2)
	{
		j = 0;
		while (j < 3)
		{
			n_rgb = ft_atoi(file->rgb[i][j]);	
			if (!is_rgb_range(n_rgb))
			{
				free_file_attributes(file);	
				return (print_debug("Error: RGB value out of range:", n_rgb, NULL) & 0);
			}
			j++;
		}
		if (j != 2 + 1)
		{
			free_file_attributes(file);	
			return (print_debug("Error: must have exactly 3 RGB values:", j, NULL) & 0);
		}
		i++;
	}
	if (i != 2)
	{
		free_file_attributes(file);	
		return (print_debug("Error: must have exactly 2 colors:", i, NULL) & 0);
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
	free_file_attributes(file);
	store_file_data(file);
	return 0;
	if (!check_color_type_id(file)) return 0;
	extract_color_codes(file);	
	if (!check_colors_format(file)) return 0;
	if (!check_rgb(file)) return 0;
	
	if (!check_texture_type_id(file)) return 0;
	extract_texture_paths(file);
	if (!check_filenames(file)) return 0;
	if (!check_textures_fds(file)) return 0;
	
	file->map = init_map(file);
	if (!check_map_valid_char(file, file->map)) return 0;
	check_for_all_char(file->map);

	free_file_attributes(file);
	return 0;
}
