#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


enum directions
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum returntype
{
	OUTSIDE,
	INSIDE
};

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
	char 	**result = calloc(width + 1, sizeof(char *));

	for (int idx = 0; idx < width; idx++)
	{
		result[idx] = calloc(height + 1, sizeof(char));
	}
	for (int idx = 0; idx < width; idx++)
	{
		for (int idx2 = 0; idx2 < height; idx2++)
		{
			result[idx2][idx] = *full_text;
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
			write(1, &(matrix[idx2][idx]), 1);
		}
		write(1, "\n", 1);
	}
}

void get_starting_coords(char **matrix, int *loc_x, int *loc_y)
{
	for (int x = 0; matrix[x]; x++)
	{
		for (int y = 0; matrix[x][y]; y++)
		{
			if (matrix[x][y] == '^')
			{
				*loc_x = x;
				*loc_y = y;
				return ;
			}
		}
	}
}

static int advance(char **matrix, int *x, int *y, int direction)
{
	int dif_x = 0;
	int dif_y = 0;

	switch (direction)
	{
		case UP:
			dif_x = 0;
			dif_y = -1;
			break;
		case RIGHT:
			dif_x = 1;
			dif_y = 0;
			break;
		case DOWN:
			dif_x = 0;
			dif_y = 1;
			break;
		case LEFT:
			dif_x = -1;
			dif_y = 0;
			break;
		default:
			dprintf(2, "Direction ERROR\n");
	}

	while (1)
	{
		if (*x + dif_x < 0 || *y + dif_y < 0 || matrix[*x + dif_x] == NULL || matrix[*x + dif_x][*y + dif_y] == 0)
		{
			printf("ENDED\n");
			return (OUTSIDE);
		}
		else if (matrix[*x + dif_x][*y + dif_y] == '#')
		{
			return (INSIDE);
		}
		else
		{
			*x += dif_x;
			*y += dif_y;
			matrix[*x][*y] = 'x';
		}
	}
}

static int get_occupied_tiles(char **matrix)
{
	int result = 0;
	for (int x = 0; matrix[x]; x++)
	{
		for (int y = 0; matrix[x][y]; y++)
		{
			if (matrix[x][y] == 'x')
				result++;
		}
	}
	return (result);
}


int main()
{
	int	fd = open("day6/input.txt", O_RDONLY);
	char *buff = calloc(101, 1);
	char *full_text = malloc(1);
	unsigned int	cumulative_size = 0;
	full_text[0] = 0;

	do
	{
		unsigned int	readsize;
		buff = memset(buff, 0, 101);
		readsize = read(fd, buff, 100);
		cumulative_size += readsize;
		full_text = realloc(full_text, cumulative_size + 1);
		full_text = strcat(full_text, buff);
	}
	while (strlen(buff) == 100);


	char	**matrix = get_matrix(full_text);
	free(full_text);
	free(buff);
	print_matrix(matrix);

	int init_x = 0;
	int init_y = 0;

	get_starting_coords(matrix, &init_x, &init_y);

	printf("> %d %d\n", init_x, init_y);


	int advancing_status = INSIDE;
	int direction = UP;

	matrix[init_x][init_y] = 'x';
	while (advancing_status == INSIDE)
	{
		advancing_status = advance(matrix, &init_x, &init_y, direction);
		direction++;
		if (direction > LEFT)
			direction = UP;
	}

	// print_matrix(matrix);


	int result = get_occupied_tiles(matrix);

	printf(">>> %d\n", result);

	free_matrix(matrix);
	close(fd);
	return (0);
}


