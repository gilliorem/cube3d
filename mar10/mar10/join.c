#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char	**create_matrix()
{
	char	**matrix;
	int	height = 5;
	int	width = 8;

	matrix = (char **)calloc(height, sizeof(char *));
	for (int i = 0; i < height; i++)
		matrix[i] = (char *) calloc (width, sizeof(char));
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			matrix[i][j] = 'X';
	return matrix;
}

void	free_matrix (char **matrix, int h)
{
	for (int i = 0; i < h; i++)
		free(matrix[i]);
	free(matrix);
}

char	*join_matrix_lines(char **matrix, int h, int w)
{
	char	*map_str;
	int	i;

	//map_str = strdup("");
	map_str = (char*)calloc((w * h + 1), sizeof (char));
	i = 0;
	while (i < h)
	{
		memmove(map_str + i * w, matrix[i], w);
		i++;
	}
	printf("map string:%s\n", map_str);
	return map_str;
}

int main()
{
	char **matrix;
	int h = 5;
	int w = 8;
	char *matrix_lines;

	matrix = create_matrix();
	matrix_lines = join_matrix_lines(matrix, h, w);
	
	free_matrix(matrix, h);
	free(matrix_lines);
}
