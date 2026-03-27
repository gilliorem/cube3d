int check_texture_line(char *line, char *id)
{
	int i = 0;

	if (!line)
		return (printf("missing texture\n") & 0);

	if (ft_strncmp(line, id, 2) != 0)
		return (printf("wrong texture id\n") & 0);

	i = 2;
	if (line[i] != ' ')
		return (printf("missing space\n") & 0);

	while (line[i] == ' ')
		i++;

	if (!line[i])
		return (printf("missing path\n") & 0);

	while (line[i] != ' ')
		i++;
	if (line[i] == ' ')
		return (printf("invalid char in path\n") & 0);
		

	return (1);
}
