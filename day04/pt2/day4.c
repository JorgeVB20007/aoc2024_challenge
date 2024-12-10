#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

static int get_line_len(char *c)
{
	int	len = 0;
	while (c[len] && c[len] != '\n')
		len++;
	return (len);
}


static int get_total_lines(char *c)
{
	int	len = 0;
	int result = 0;
	while (c[len])
	{
		if (c[len] == '\n')
			result++;
		len++;
	}
	result++;
	return (result);
}

static char	**get_matrix(char *full_text)
{
	int 	width = get_line_len(full_text);
	int 	height = get_total_lines(full_text);
	char 	**result = calloc(width, sizeof(char *) + 1);

	for (int idx = 0; idx < width; idx++)
	{
		result[idx] = calloc(width, sizeof(char) + 1);
		for (int idx2 = 0; idx2 < height; idx2++)
		{
			result[idx][idx2] = *full_text;
			full_text++;
		}
		full_text++;
	}
	return (result);
}

static void free_matrix(char **matrix)
{
	for (int idx = 0; matrix[idx]; idx++)
	{
		free(matrix[idx]);
	}
	free(matrix);
}

void print_matrix(char **matrix)
{
	for (int idx = 0; matrix[idx]; idx++)
	{
		for (int idx2 = 0; matrix[idx][idx2]; idx2++)
		{
			write(1, &(matrix[idx][idx2]), 1);
		}
		write(1, "\n", 1);
	}
}

static int	check_coincidence(char **matrix, int init_x, int init_y, int dir_x, int dir_y)
{
	char	coincidence[] = "MAS";
	for (int idx = 0; idx < (int)strlen(coincidence); idx++)
	{
		if (!(init_x + idx * dir_x >= 0 && init_y + idx * dir_y >= 0 && \
		matrix[init_x + idx * dir_x] && \
		matrix[init_x + idx * dir_x][init_y + idx * dir_y] == coincidence[idx]))
		{
			return (0);
		}
	}
	return (1);
}

static int	get_xmas(char **matrix)
{
	int	result = 0;
	for (int x = 1; matrix[x + 1]; x++)
	{
		for (int y = 1; matrix[x][y + 1]; y++)
		{
			int case_result = 0;
			case_result += check_coincidence(matrix, x-1, y-1, 1, 1);
			case_result += check_coincidence(matrix, x+1, y-1, -1, 1);
			case_result += check_coincidence(matrix, x+1, y+1, -1, -1);
			case_result += check_coincidence(matrix, x-1, y+1, 1, -1);
			if (case_result == 2)
				result++;
		}
	}
	return (result);
}


int main()
{
	int	fd = open("day04/input.txt", O_RDONLY);
	char *buff = calloc(101, 1);
	char *full_text = malloc(0);
	unsigned int	cumulative_size = 0;

	do
	{
		unsigned int	readsize;
		buff = memset(buff, 0, 101);
		readsize = read(fd, buff, 100);
		cumulative_size += readsize;
		full_text = realloc(full_text, cumulative_size + readsize + 1);
		full_text = strcat(full_text, buff);
	}
	while (strlen(buff) == 100);


	char	**matrix = get_matrix(full_text);
	free(full_text);
//	print_matrix(matrix);
	int result = get_xmas(matrix);
	printf(">>> %d\n", result);



	free_matrix(matrix);
	close(fd);
	return (0);
}




