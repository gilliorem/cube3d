int	parse_lines(t_file *file, t_config *config)
{
	enum	e_state file_state;
	enum	e_line_type line_type;
	int	i;
	char	texture_id[3];

	i = 0;
	file_state = CONFIG;
	while (file->lines[i])
	{
		line_type = classify_line(file->lines[i]);
		if (line_type == MAP && file_state == CONFIG)
			return (printf("Error within line%d:%s\n",i+1, file->lines[i]) & 0);
		if (line_type == EMPTY && file_state == CONFIG)
		{
			continue;
		}
		else if (line_type == COLOR && file_state == CONFIG)
			process_color_line(file, file->lines[i][0]); 
		else if (line_type == TEXTURE && file_state == CONFIG)
			process_texture(file, ft_memcpy(texture_id, file->lines[i], 3));
		else if (line_type == MAP && file_state == CONFIG)
		{
			file_state = IN_MAP;
			// process_map_line()
		}
		else if (line_type == MAP && file_state == IN_MAP)
		{
			break;
			// process_map_line()
		}
		else if (file_state == IN_MAP && line_type != MAP)
		{
			return (printf("Error within line%d:%s\n",i+1, file->lines[i]) & 0);
		}
		else
			return (printf("Error within line%d:%s\n",i+1, file->lines[i]) & 0);
		i++;
	}
	return (1);
}
