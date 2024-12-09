#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


typedef struct s_item
{
	int is_empty;
	unsigned int value;
	t_item *next;
} t_item;


t_item *create_item(int is_empty, unsigned int value)
{
	t_item *retval = calloc(1, sizeof(t_item));
	retval->is_empty = is_empty;
	retval->value = value;
	retval->next = NULL;
	return (retval);
}


int main()
{
	int	fd = open("day9/input2.txt", O_RDONLY);
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

	close(fd);


	printf("%s\n", full_text);

	t_item *items = NULL;
	t_item *last = NULL;
	int current_data_value = 0;

	for (int idx = 0; full_text[idx]; idx++)
	{
		for (int curr_idx_value = 0; curr_idx_value < full_text[idx] + '0'; curr_idx_value++)
		{
			if (!items)
			{
				items = create_item(0, current_data_value);
				last = items;
			}
			else
			{
				
			}
		}
	}


	free(full_text);


	return (0);
}



