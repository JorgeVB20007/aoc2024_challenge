#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


typedef struct s_item
{
	int is_empty;
	unsigned int value;
	int size;
	struct s_item *next;
	struct s_item *prev;
} t_item;


t_item *create_item(int is_empty, unsigned int value, int size, t_item *prev)
{
	t_item *retval = calloc(1, sizeof(t_item));
	retval->is_empty = is_empty;
	retval->value = value;
	retval->size = size;
	retval->next = NULL;
	retval->prev = prev;
	return (retval);
}

void print_items(t_item *items)
{
	while (items)
	{
		for (int idx = 0; idx < items->size; idx++)
		{
			if (items->is_empty)
				printf(". ");
			else
				printf("%d ", items->value);
		}
		items = items->next;
	}
	printf("\n");
}

void sort_all(t_item *items)
{
	t_item *first = items;
	t_item *last = items;
	while (last->next)
		last = last->next;

	int idx = last->value;

	while (idx)
	{
		t_item *auxfirst = first;
		int searching_size = last->size;
		while (auxfirst)
		{
			if (auxfirst == last)
				break;
			if (auxfirst->is_empty && auxfirst->size >= searching_size)
			{
				if (auxfirst->size == searching_size)
				{
					auxfirst->is_empty = 0;
					auxfirst->value = idx;
				}
				else
				{
					int diff = auxfirst->size - searching_size;
					t_item *next_aux = auxfirst->next;
					auxfirst->next = create_item(1, 0, diff, auxfirst);
					auxfirst->next->next = next_aux;
					next_aux->prev = auxfirst->next;
					auxfirst->size = searching_size;
					auxfirst->value = idx;
					auxfirst->is_empty = 0;
				}
				last->is_empty = 1;
				last->value = 0;

				break;
			}
			auxfirst = auxfirst->next;
		}
		idx--;
		while (!(!last->is_empty && last->value == (unsigned int)idx))
			last = last->prev;
	}

}

int main()
{
	int	fd = open("day09/input.txt", O_RDONLY);
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
		if (!items)
		{
			items = create_item(0, current_data_value, full_text[idx] - '0', NULL);
			last = items;
		}
		else
		{
			last->next = create_item(0, current_data_value, full_text[idx] - '0', last);
			last = last->next;
		}
		current_data_value++;
		if (!full_text[idx + 1])
			break;
		else
			idx++;
		last->next = create_item(1, 0, full_text[idx] - '0', last);
		last = last->next;
	}
	free(full_text);

	sort_all(items);

	// print_items(items);

	unsigned long long	result = 0;
	int idx = 0;


	while (items)
	{
		if (!items->is_empty)
		{
			for (int idx2 = 0; idx2 < items->size; idx2++)
			{
				result += idx * items->value;
				idx++;
			}
		}
		else
			idx += items->size;
		items = items->next;
	}

	t_item *items_aux = items;
	while (items_aux)
	{
		t_item *prevaux = items_aux;
		items_aux = items_aux->next;
		free(prevaux);
	}
	
	printf(">>> %llu\n", result);


	return (0);
}



