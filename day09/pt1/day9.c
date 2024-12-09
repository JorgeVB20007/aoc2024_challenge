#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


typedef struct s_item
{
	int is_empty;
	unsigned int value;
	struct s_item *next;
	struct s_item *prev;
} t_item;


t_item *create_item(int is_empty, unsigned int value, t_item *prev)
{
	t_item *retval = calloc(1, sizeof(t_item));
	retval->is_empty = is_empty;
	retval->value = value;
	retval->next = NULL;
	retval->prev = prev;
	return (retval);
}

void print_items(t_item *items)
{
	while (items)
	{
		if (items->is_empty)
			printf(". ");
		else
			printf("%d ", items->value);
		items = items->next;
	}
	printf("\n");
}

void sort_one(t_item *items)
{
	t_item *first = items;
	t_item *last = items;
	while (last->next)
		last = last->next;

	while (!first->is_empty)
		first = first->next;
	while (last->is_empty)
		last = last->prev;
	first->is_empty = 0;
	first->value = last->value;
	last->is_empty = 1;
	last->value = 0;
}


int is_sorted(t_item *items)
{
	int nums_ended = 0;
	while (items)
	{
		if (items->is_empty)
			nums_ended = 1;
		else if (nums_ended)
			return (0);
		items = items->next;
	}
	return (1);
}

int main()
{
	int	fd = open("day9/input.txt", O_RDONLY);
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

	t_item *items = NULL;
	t_item *last = NULL;
	int current_data_value = 0;

	for (int idx = 0; full_text[idx]; idx++)
	{
		for (int curr_idx_value = 0; curr_idx_value < full_text[idx] - '0'; curr_idx_value++)
		{
			if (!items)
			{
				items = create_item(0, current_data_value, NULL);
				last = items;
			}
			else
			{
				last->next = create_item(0, current_data_value, last);
				last = last->next;
			}
		}
		current_data_value++;
		if (!full_text[idx + 1])
			break;
		else
			idx++;
		for (int curr_idx_value = 0; curr_idx_value < full_text[idx] - '0'; curr_idx_value++)
		{
			last->next = create_item(1, 0, last);
			last = last->next;
		}
	}
	free(full_text);

	while (!is_sorted(items))
		sort_one(items);

	// print_items(items);


	unsigned long long	result = 0;
	int idx = 0;

	while (items)
	{
		result += idx * items->value;
		if (!items->next)
			free(items);
		else
			items = items->next;
		if (items)
			free(items->prev);
		idx++;
	}

	
	printf(">>> %llu\n", result);

	t_item *items_aux = items;
	while (items_aux)
	{
		t_item *prevaux = items_aux;
		items_aux = items_aux->next;
		free(prevaux);
	}

	return (0);
}



