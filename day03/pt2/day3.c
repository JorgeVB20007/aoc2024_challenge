#include <regex.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char			*buf = calloc(101, sizeof(char));
	int				fd = open("day3/input.txt", O_RDONLY);
	char			*full_input = malloc(0);
	unsigned long	result = 0;

	do
	{
		memset(buf, 0, 101);
		unsigned int size = read(fd, buf, 100);
		full_input = realloc(full_input, strlen(full_input) + size + 1);
		strcat(full_input, buf);
	}
	while (strlen(buf) == 100);
	close(fd);
	free(buf);

	regex_t	mul_regex_expression;
	regex_t	do_regex_expression;
	regex_t	dont_regex_expression;

	if (regcomp(&mul_regex_expression, "^mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED))
	{
		dprintf(2, "mul() Regex wrongly created.\n");
		exit(1);
	}
	if (regcomp(&do_regex_expression, "^do\\(\\)", REG_EXTENDED))
	{
		dprintf(2, "do() Regex wrongly created.\n");
		exit(1);
	}
	if (regcomp(&dont_regex_expression, "^don\'t\\(\\)", REG_EXTENDED))
	{
		dprintf(2, "don't() Regex wrongly created.\n");
		exit(1);
	}

	int enabled = 1;
	for (int idx = 0; full_input[idx]; idx++)
	{
		if (!regexec(&do_regex_expression, &(full_input[idx]), 0, NULL, 0))
			enabled = 1;
		else if (!regexec(&dont_regex_expression, &(full_input[idx]), 0, NULL, 0))
			enabled = 0;
		else if (enabled && !regexec(&mul_regex_expression, &(full_input[idx]), 0, NULL, 0))
		{
			idx += 4;
			int first = atoi(&(full_input[idx]));
			while (full_input[idx] != ',')
				idx++;
			idx++;
			int second = atoi(&(full_input[idx]));
			result += first * second;
			while (full_input[idx] != ')')
				idx++;
		}
	}
	printf(">>> %ld\n", result);
	free(full_input);
}
