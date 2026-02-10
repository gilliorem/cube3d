#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"

typedef struct s_file
{
	char	*name;
	int	fd;
	char	*cur_line;
	char	**textures;
	char	**colours;
	char	**map;
}	t_file;

typedef struct s_element
{
	char	type_id[2];
	char	information[100];
}	t_element;

int	error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (0);
}

int	check_first_arg(char *argv_zero)
{
	if (ft_strncmp(argv_zero, "./cub3D", ft_strlen("./cube3D")) != 0)
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
	return file;
}

int	check_first_type_id(t_file *file)
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
				textures_id[0] = true;
			if (file->cur_line[0] == 'S' && file->cur_line[1] == 'O') 
				textures_id[1] = true;
			if (file->cur_line[0] == 'E' && file->cur_line[1] == 'A') 
				textures_id[2] = true;
			if (file->cur_line[0] == 'W' && file->cur_line[1] == 'E') 
				textures_id[3] = true;
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

int	check_xpm_extension(t_file *file, char *extension)
{
	int	path_len;
	int	i;

	path_len = ft_strlen(file->textures[2]);
	i = 0;
	if (path_len <= ft_strlen(extension)) // has to be longer than '.cub'
		return printf("less than 4 char.\n") & 0;
	
	while (file->textures[2][i])
		i++;
	if (file->textures[2][i-1] != 'b' || file->textures[2][i-2] != 'u' || 
		file->textures[2][i-3] != 'c' || file->textures[2][i-4] != '.')
		return (printf("wrong extension 'last char' \n") & 0);
	return 1;	
}

void	read_first_line(t_file *file)
{
	file->cur_line = get_next_line(file->fd);
	printf("%s", file->cur_line);
}

int	check_color_type_id(t_file *file)
{
	int		i;
	char	color_type_id;
	bool	colors_id[2];

	while (1)
	{
		if (file->cur_line == NULL)
			break;
		file->cur_line = get_next_line(file->fd);
		color_type_id = file->cur_line[0];
		if (color_type_id != 'F' || color_type_id != 'C')
			return (printf("color type id is wrong\n") & 0 );
		if (color_type_id == 'F')
			colors_id[0] = true;
		if (color_type_id == 'C')
			colors_id[1] = true;
		i = 0;
		while (i < 2)
		{
			if (colors_id[i] == false)
				return (printf("missing one color id\n") & 0);
			else if (i == 1)
				return (1);
			i++;
		}
	}
	return (1);
}	

int main(int argc, char *argv[])
{
	t_file	*file;

	if (argc != 2 || !check_argv(argv))
		return (error(ERR_MSG_ARGC));
	file = init_file(argv[1]);
	check_first_type_id(file);
	check_color_type_id(file);
	return 0;
}
