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

void	init_textures(t_texture texture_list[4], t_file *file, char *id)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture_list[i] = process_texture(file, id);
		i++;
	}
	t_texture no = process_texture(file, "NO\0");
	t_texture so = process_texture(file, "SO\0");
	t_texture ea = process_texture(file, "EA\0");
	t_texture we = process_texture(file, "WE\0");
}
