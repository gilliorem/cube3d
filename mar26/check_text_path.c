int	check_valid_fd(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (print_debug("could not open file:", -1, file_path) & 0);
	}
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
