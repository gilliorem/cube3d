#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("../maps/m.cub", O_RDONLY);
	if (fd == -1) return printf("file error\n") & 0;
	char *line;
	char *last_line;
	while (1)
	{
		line = get_next_line(fd);
		if (line[0] != '\n')
			break;
		last_line = ft_strdup(line);
		printf(">%s", last_line);
		free(line);
		free(last_line);
	}
	printf("last line:%s", last_line);
}

while (1)
{
	line = get_next_line(fd);
	if (!line)
		break;
	if (line[0] != '\n')
	{
		free(line);
		break;
	}
	if (last_line)
		free(last_line);
	last_line = ft_strdup(line);
	free(line);
}

if (last_line)
	printf("last line:%s", last_line);
free(last_line);
