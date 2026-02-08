#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define ERR_MSG_ARGC "usage: ./<cub3D> <path/to/map.cub>"


typedef struct s_file
{
	char *extension; // .cub
	char *path;	 // path/to/map
	char *name;	 // path/to/map.cub
} t_file;

int	print_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (0);
}

int	check_first_arg(char *argv_zero)
{
	if (ft_strncmp(argv_zero, "cub3D", ft_strlen("cube3D")) != 0)
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

t_file	*init_file(char *argv_one)
{
	t_file *file;

	file = ft_calloc(1, sizeof(file));
	file->extension = ft_calloc(4 + 1, sizeof(char));
	file->name = ft_calloc(ft_strlen(argv_one) + 1, sizeof(char));
	file->path = ft_calloc(ft_strlen(argv_one) - 5 + 1, sizeof(char));

	ft_memcpy(file->path, argv_one, ft_strlen(argv_one));
	printf("%s\n", file->path);
	return (file);
}

int	check_file_path(t_file *file)
{
	char *ptr = ft_strnstr(file->path, ".cub", ft_strlen(file->path));
	printf("%s\n", ptr);
	if (!ptr)
		return printf("no extension .cub\n") & 0;

	return 1;
}

int	check_argv()
{

	return 1;
}

int main(int argc, char *argv[])
{
	t_file	*file;

	if (argc != 2)
		return (print_error(ERR_MSG_ARGC));
	check_file_extension(argv[1]);
	file = init_file(argv[1]);
	check_file_path(file);
	return 0;
}
