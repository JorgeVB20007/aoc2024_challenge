#include "day15.hpp"

static void error_and_exit(std::string reason)
{
	std::cerr << reason << std::endl;
	exit (1);
}

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	type = EMPTY;
}

Tile::Tile(char _type)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	switch (_type)
	{
		case '.':
			type = EMPTY;
			break;
		case '@':
			type = ROBOT;
			break;
		case 'O':
			type = BOX;
			break;
		case '#':
			type = WALL;
			break;
	}
}


Tile::~Tile()
{
	if (it_next)
		delete (it_next);
}


std::string read_file(std::string filename)
{
	std::string full_text;
	std::string line;
	std::ifstream file(filename);
	if (file.is_open()) {
		while (std::getline(file, line)) {
			full_text.append(line);
			full_text.append("\n");
		}
		file.close();
	}
	return (full_text);
}



void print(Tile *first)
{
	Tile *current;
	Tile *first_from_row = first;

	while (first_from_row)
	{
		current = first_from_row;
		while (current)
		{
			switch (current->type)
			{
				case EMPTY:
					std::cout << ".";
					break;
				case ROBOT:
					std::cout << "@";
					break;
				case BOX:
					std::cout << "O";
					break;
				case WALL:
					std::cout << "#";
					break;
				default:
					std::cout << current->type;
			}
			current = current->east;
		}
		std::cout << std::endl;
		first_from_row = first_from_row->south;
	}
}


Tile *create_map(std::string input_text, Tile **robot_location)
{
	Tile	*first = NULL;
	Tile	*current = NULL;
	Tile	*first_from_row = NULL;
	Tile	*current_prev_row = NULL;
	Tile	*previous = NULL;

	for (std::string::iterator i = input_text.begin(); i + 1 != input_text.end(); i++)
	{
		if (*i == '\n')
		{
			if (!first_from_row)
			{
				first_from_row = first;
				current_prev_row = first;
			}
			else
			{
				first_from_row = first_from_row->south;
				current_prev_row = first_from_row;
			}
			current = NULL;
		}
		else
		{
			if (!first)
			{
				current = new Tile(*i);
				first = current;
				previous = current;
			}
			else if (!current)
			{
				current = new Tile(*i);
				previous->it_next = current;
				previous = current;
				current->north = first_from_row;
				first_from_row->south = current;
			}
			else
			{
				current->east = new Tile(*i);
				current->east->west = current;
				current = current->east;
				previous->it_next = current;
				previous = current;

				if (current_prev_row)
				{
					current_prev_row = current_prev_row->east;
					current->north = current_prev_row;
					current_prev_row->south = current;
				}
			}
			if (current->type == ROBOT)
				*robot_location = current;
		}
	}

	return (first);
}

static int find_separation(const std::string &full_text)
{
	int idx = 0;

	while (!(full_text[idx] == '\n' && full_text[idx + 1] == '\n'))
		idx++;
	return idx;
}

static Tile *move_robot(Tile *loc, char move)
{
	if (move == '^')
	{
		Tile *aux = loc->north;
		while (aux && aux->type != EMPTY && aux->type != WALL)
			aux = aux->north;
		if (aux->type == EMPTY)
		{
			while (aux != loc)
			{
				aux->type = aux->south->type;
				aux = aux->south;
			}
			loc->type = EMPTY;
			return (loc->north);
		}
		return (loc);
	}
	else if (move == '>')
	{
		Tile *aux = loc->east;
		while (aux && aux->type != EMPTY && aux->type != WALL)
			aux = aux->east;
		if (aux->type == EMPTY)
		{
			while (aux != loc)
			{
				aux->type = aux->west->type;
				aux = aux->west;
			}
			loc->type = EMPTY;
			return (loc->east);
		}
		return (loc);
	}
	else if (move == 'v')
	{
		Tile *aux = loc->south;
		while (aux && aux->type != EMPTY && aux->type != WALL)
			aux = aux->south;
		if (aux->type == EMPTY)
		{
			while (aux != loc)
			{
				aux->type = aux->north->type;
				aux = aux->north;
			}
			loc->type = EMPTY;
			return (loc->south);
		}
		return (loc);
	}
	else if (move == '<')
	{
		Tile *aux = loc->west;
		while (aux && aux->type != EMPTY && aux->type != WALL)
			aux = aux->west;
		if (aux->type == EMPTY)
		{
			while (aux != loc)
			{
				aux->type = aux->east->type;
				aux = aux->east;
			}
			loc->type = EMPTY;
			return (loc->west);
		}
		return (loc);
	}
	else
	{
		std::cout << "(" << move << ")" << std::endl;;
		error_and_exit("Error: Unknown move.");
		return (NULL);
	}
}

static int get_result(Tile *map)
{
	Tile *current = map;
	Tile *first_from_line = map;
	int x = 0;
	int y = 0;
	int result = 0;

	while (first_from_line)
	{
		x = 0;
		while (current)
		{
			if (current->type == BOX)
				result += y * 100 + x;
			current = current->east;
			x++;
		}
		first_from_line = first_from_line->south;
		current = first_from_line;
		y++;
	}
	return (result);
}

int main()
{
	std::string full_text = read_file("day15/input.txt");

	std::string map_text;
	std::string instructions_text;

	{
		int separator = find_separation(full_text);
		map_text = full_text.substr(0, separator + 1);
		instructions_text = full_text.substr(separator + 2, full_text.size() - separator - 3);
		instructions_text.erase(std::remove(instructions_text.begin(), instructions_text.end(), '\n'), instructions_text.end());
	}

	Tile *loc;
	Tile *map = create_map(map_text, &loc);

	for (std::string::iterator c = instructions_text.begin(); c != instructions_text.end(); c++)
	{
		loc = move_robot(loc, *c);
	}
	print(map);
	int result = get_result(map);
	std::cout << ">>> " << result << std::endl;
	delete map;
}

