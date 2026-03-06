#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	**create_matrix()
{
	char	**matrix;
	int	height = 5;
	int	width = 8;
	
	matrix = (char **)calloc(height, sizeof(char *));
	for (int i = 0; i < height; i++)
		matrix[i] = (char *) calloc (width, sizeof(char));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrix[i][j] = 'X';
			//printf("%c", matrix[i][j]);
		}
		//printf("\n");
	}
	return matrix;
}

void	free_matrix (char **matrix)
{
	int height = 5;
	for (int i = 0; i < height; i++)
	{
		free(matrix[i]);
	}

	free(matrix);
}

char	*join_matrix_lines(char **matrix, int h, int w)
{
	char	*map_str;
	int	i;

	//map_str = ft_strdup("");
	map_str = (char*)calloc((w * h + 1), sizeof (char));
	i = 0;
	while (i < h)
	{
		ft_memmove(map_str + i * w, matrix[i], w);
		i++;
	}
	map_str[(h * w)] = '\0';

	printf("map string:%s\n", map_str);
	return map_str;
}

int main()
{
	char **matrix;
	char *matrix_lines;

	matrix = create_matrix();
	matrix_lines = join_matrix_lines(matrix, 5, 8);
	
	free_matrix(matrix);
	free(matrix_lines);
}
