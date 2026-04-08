#include <stdio.h>
#include <string.h>
char	*trim_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
		}
		i++;
	}
	return (line);
}

int main()
{
	//char *line = "C    70,1,1\n" << Why is this giving me seg fault ?
	char *line = strdup("C    70,1,1\n");

	line = trim_new_line(line);
	printf("%s", line);
}
