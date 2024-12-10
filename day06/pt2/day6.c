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

enum response
{
	IN_PROGRESS,
	LOOP,
	EXITS
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

static char	**copy_matrix(char **matrix)
{
	int 	width = 0;
	char 	**result = NULL;

	for (int x = 0; matrix[x]; x++)
		width++;

	result = calloc(width + 1, sizeof(char *));
	for (int x = 0; matrix[x]; x++)
		result[x] = strdup(matrix[x]);

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
	write(1, "\n", 1);
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


static int is_loop(char **matrix, int x, int y, int direction)
{
	int dif_x = 0;
	int dif_y = 0;
	int response = IN_PROGRESS;

	while (response == IN_PROGRESS)
	{
		int path_break = 0;
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
		while (!path_break)
		{
			if (x + dif_x < 0 || y + dif_y < 0 || matrix[x + dif_x] == NULL || matrix[x + dif_x][y + dif_y] == 0)
			{
				return (0);
			}
			else if (matrix[x + dif_x][y + dif_y] == '^' && direction == UP)
			{
				return (1);
			}
			else if (matrix[x + dif_x][y + dif_y] == '>' && direction == RIGHT)
			{
				return (1);
			}
			else if (matrix[x + dif_x][y + dif_y] == 'v' && direction == DOWN)
			{
				return (1);
			}
			else if (matrix[x + dif_x][y + dif_y] == '<' && direction == LEFT)
			{
				return (1);
			}
			else if (matrix[x + dif_x][y + dif_y] == '#' || matrix[x + dif_x][y + dif_y] == 'O')
			{
				path_break = 1;
			}
			else
			{
				x += dif_x;
				y += dif_y;
				if (direction == UP)
					matrix[x][y] = '^';
				else if (direction == RIGHT)
					matrix[x][y] = '>';
				else if (direction == DOWN)
					matrix[x][y] = 'v';
				else if (direction == LEFT)
					matrix[x][y] = '<';
			}
		}
		direction++;
		if (direction > LEFT)
			direction = UP;
	}
	return (1);
}

static int attempt(char **matrix_cpy, int x, int y, int direction)
{
	switch (direction)
	{
		case UP:
			if (y == 0 || matrix_cpy[x][y - 1] == '#' || matrix_cpy[x][y - 1] == 'x')
				return (0);
			matrix_cpy[x][y - 1] = 'O';
			direction = RIGHT;
			break;
		case RIGHT:
			if (matrix_cpy[x] == NULL || matrix_cpy[x + 1][y] == '#' || matrix_cpy[x + 1][y] == 'x')
				return (0);
			matrix_cpy[x + 1][y] = 'O';
			direction = DOWN;
			break;
		case DOWN:
			if (matrix_cpy[x][y + 1] == 0 || matrix_cpy[x][y + 1] == '#' || matrix_cpy[x][y + 1] == 'x')
				return (0);
			matrix_cpy[x][y + 1] = 'O';
			direction = LEFT;
			break;
		case LEFT:
			if (x == 0 || matrix_cpy[x - 1][y] == '#' || matrix_cpy[x - 1][y] == 'x')
				return (0);
			matrix_cpy[x - 1][y] = 'O';
			direction = UP;
			break;
	}
	int response = is_loop(matrix_cpy, x, y, direction);
	return (response);
}

static int advance_one(char **matrix, int *x, int *y, int *direction)
{
	switch(*direction)
	{
		case UP:
			if (*y == 0)
				return (OUTSIDE);
			else if (matrix[*x][*y - 1] == '#' || matrix[*x][*y - 1] == 'O')
				*direction = RIGHT;
			else
				*y -= 1;
			break ;
		case RIGHT:
			if (matrix[*x + 1] == NULL)
				return (OUTSIDE);
			else if (matrix[*x + 1][*y] == '#' || matrix[*x + 1][*y] == 'O')
				*direction = DOWN;
			else
				*x += 1;
			break ;
		case DOWN:
			if (matrix[*x][*y + 1] == 0)
				return (OUTSIDE);
			else if (matrix[*x][*y + 1] == '#' || matrix[*x][*y + 1] == 'O')
				*direction = LEFT;
			else
				*y += 1;
			break ;
		case LEFT:
			if (*x == 0)
				return (OUTSIDE);
			else if (matrix[*x - 1][*y] == '#' || matrix[*x - 1][*y] == 'O')
				*direction = UP;
			else
				*x -= 1;
			break ;
	}
	return (INSIDE);
}


int main()
{
	int	fd = open("day06/input.txt", O_RDONLY);
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

	int x = 0;
	int y = 0;

	get_starting_coords(matrix, &x, &y);

	int advancing_status = INSIDE;
	int direction = UP;
	int result = 0;

	while (advancing_status == INSIDE)
	{
		char **matrix_cpy = copy_matrix(matrix);
		result += attempt(matrix_cpy, x, y, direction);
		free_matrix(matrix_cpy);
		matrix[x][y] = 'x';
		advancing_status = advance_one(matrix, &x, &y, &direction);
	}

	// print_matrix(matrix);

	printf(">>> %d\n", result);

	free_matrix(matrix);
	close(fd);
	return (0);
}


