#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"
#define DEBUG_MODE 1

typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	char	*floor_line;
	char	*ceiling_line;
	int	n_color_lines;
	char	*color_lines[2];
	char 	*color_codes[2];
	char	**rgb[2];
	char	***textures;
	char	**colours;
	char	**map;
}	t_file;

typedef struct s_element
{
	char	type_id[2];
	char	information[100];
}	t_element;


int	print_debug(char *err_msg, int n, char *s)
{
	if (DEBUG_MODE == 1)
	{
		if (n != -1)
		{
			printf("%s[%d]\n", err_msg, n);
			return 0;
		}
		else if (s != NULL)
		{
			printf("%s[%s]\n", err_msg, s);
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

int	error(char *msg)
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

int	check_file_extension(char *argv_one)
{
	char	*extension;
	int	argv_one_len; 
	int	i;

	extension = ".cub";
	argv_one_len = ft_strlen(argv_one);
	i = 0;

	if (argv_one_len <= ft_strlen(extension)) // has to be longer than '.cub'
		return printf("less than 4 char.\n") & 0;
	
	while (argv_one[i])
		i++;
	if (argv_one[i-1] != 'b' || argv_one[i-2] != 'u' || 
		argv_one[i-3] != 'c' || argv_one[i-4] != '.')
		return (printf("wrong extension 'last char' \n") & 0);
	return 1;	
}

int	check_argv(char *argv[])
{
	if (!check_first_arg(argv[0]) ||
		!check_file_extension(argv[1]))
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
	file->fd = try_open_file(argv_one);
	file->n_color_lines = 2;
	//file->textures = ft_calloc(4 + 1, sizeof(char **));
	return file;
}

int	check_color_type_id(t_file *file)
{
	bool	color_type_id[2];
	int	count;

	color_type_id[0] = false;
	color_type_id[1] = false;
	count = 0;
	while (1)
	{
		file->cur_line = get_next_line(file->fd);
		if (!file->cur_line)
			break;// reach EOF
		if (file->cur_line[0] == 'F' && file->cur_line[1] == ' ')
		{
			count++;
			color_type_id[0] = true;
			//file->floor_line = ft_strdup(file->cur_line);
			file->color_lines[0] = ft_strdup(file->cur_line);
		}
		if (file->cur_line[0] == 'C' && file->cur_line[1] == ' ')
		{
			count++;
			color_type_id[1] = true;
			//file->ceiling_line = ft_strdup(file->cur_line);
			file->color_lines[1] = ft_strdup(file->cur_line);
		}
		free(file->cur_line);
	}
	if (color_type_id[0] == true && color_type_id[1] == true && count == 2)
	{
		print_debug("valid colors type ID F C.\nColor-lines stored.", -1, NULL);
		//printf("color line[0]:%s\n", file->color_lines[0]);
		//!! the line include the \n ! have to trim the \n off the line.!! -> libft strudp_newline added
//		print_debug("F:", -1, file->color_lines[0]);
//		print_debug("C:", -1, file->color_lines[1]);
		return (1);
	}
	print_debug("Invalid colors type id; count=", count, NULL);
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
	//printf("color_code:%s\n", substr);
	print_debug("color code:", -1, substr);
	return (substr);
}

void	extract_color_codes(t_file *file)
{
	int	i;
	
	if (!check_color_type_id(file))
		return ;
	i = 0;
	while (i < 2)
	{
		file->color_codes[i] = extract_color_code(file, file->color_lines[i]);
		i++;
	}
}

// TODO case like `2 comas "122,,22,,,,,,2"

int	check_color_format(t_file *file, char *color_code)
{
	int	i;

	i = 0;
	print_debug(">color code:", -1, color_code);
	while (color_code[i])
	{
		if (!ft_strchr("0123456789,",color_code[i]))
			return (print_debug("Error", -1, "RGB Wrong format") & 0);
		i++;
	}
	return (1);
}

int	check_colors_format(t_file *file)
{
	int	i;

	i = 0;
	while (i < file->n_color_lines)
	{
		if(!check_color_format(file, file->color_codes[i]))
			return (0);
		i++;
	}
	return (1);
}

void	split_rgb(t_file *file)
{
	int	i;

	i = 0;
	while (i < file->n_color_lines)
	{
		file->rgb[i] = ft_split(file->color_codes[i], ',');
		i++;
	}
	for (int i = 0; file->rgb[i]; i++)
	{
		for (int j = 0; file->rgb[i][j]; j++)
			print_debug(">", -1, file->rgb[i][j]);
	}

}
int	check_rgb(t_file *file)
{
	split_rgb(file);

	int	i;
	int	j;
	int	n_rgb;

	i = 0;
	j = 0;
	n_rgb = 0;
	while (file->rgb[i])
	{
		while (file->rgb[i][j])
		{
			n_rgb = ft_atoi(file->rgb[i][j]);	
			if (!is_rgb_range(n_rgb))
				return (print_debug("Error: RGB value out of range:",n_rgb,NULL) & 0);
			j++;
		}
		i++;
	}
	if (i != 2)
		return (print_debug("Error: must have exactly 3 RGB values:", i, NULL) & 0);
	return (1);
}

/*
int	check_texture_type_id(t_file *file)
{
	int	i;
	char	type_id_one[2];
	bool	textures_id[4];

	while (1)
	{
		if (!file->cur_line)
			break;
		file->cur_line = get_next_line(file->fd);
		type_id_one[0] = file->cur_line[0];
		type_id_one[1] = file->cur_line[1];
		if (!ft_strchr("NSWE", type_id_one[0]) || !(ft_strchr("OEA", type_id_one[1])))
			return (printf("Type identifier is wrong.\n") & 0);
		else
		{
			if (file->cur_line[0] == 'N' && file->cur_line[1] == 'O')
			{
				textures_id[0] = true;
				file->textures[0] = ft_split(file->cur_line, ' ');
			}
			if (file->cur_line[0] == 'S' && file->cur_line[1] == 'O') 
			{
				textures_id[1] = true;
				file->textures[1] = ft_split(file->cur_line, ' ');
			}
			if (file->cur_line[0] == 'E' && file->cur_line[1] == 'A') 
			{
				textures_id[2] = true;
				file->textures[2] = ft_split(file->cur_line, ' ');
			}
			if (file->cur_line[0] == 'W' && file->cur_line[1] == 'E') 
			{
				textures_id[3] = true;
				file->textures[3] = ft_split(file->cur_line, ' ');
			}
		}
		i = 0;
		while (i < 4)
		{
			if (textures_id[i] == false)
			{
				close(file->fd);
				return (printf("Missing one of the first type id.\n") & 0);
			}
			else if (i == 3)
				return (1);
			i++;
		}
	}
	close(file->fd);
	return (1);
}
*/
/*
int	check_xpm_extension(t_file *file, char *extension)
{
	int	path_len;
	int	i;
	int	j;

	j = 0;
	i = 0;

	while (i < 4)
	{
		printf("%s", file->textures[i][1]);
		i++;
	}
	return 0;
	while (i < 4)
	{
		path_len = ft_strlen(file->textures[i][1]);
		i = 0;
		if (path_len <= ft_strlen(extension)) // has to be longer than '.xpm'
			return printf("less than 4 char.\n") & 0;
		i++;
	}
	
	while (file->textures[2][i])
		i++;
	if (file->textures[2][i-1] != 'b' || file->textures[2][i-2] != 'u' || 
		file->textures[2][i-3] != 'c' || file->textures[2][i-4] != '.')
		return (printf("wrong extension 'last char' \n") & 0);
	return 1;	
}
*/

int main(int argc, char *argv[])
{
	t_file	*file;

	if (argc != 2 || !check_argv(argv))
		return (error(ERR_MSG_ARGC));
	file = init_file(argv[1]);
	extract_color_codes(file);	
	if (!check_colors_format(file)) return 0;
	if (!check_rgb(file)) return 0;
	//check_texture_type_id(file);
	//check_color_type_id(file);
	//check_xpm_extension(file, ".xpm");
		
	free(file->floor_line);
	free(file->ceiling_line);
	free(file);
	return 0;
}
