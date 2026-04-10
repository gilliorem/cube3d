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
