#include "day8.hpp"

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	has_antenna = false;
	antenna = 0;
	has_antinode = false;
	loc_x = 0;
	loc_y = 0;
}

Tile::Tile(char value)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	if (value == '.')
	{
		has_antenna = false;
		antenna = 0;
	}
	else
	{
		has_antenna = true;
		antenna = value;
	}
	has_antinode = false;
	loc_x = 0;
	loc_y = 0;
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
			if (current->has_antinode)
			{
				std::cout << "\033[0;33m";
			}
			if (current->has_antenna)
				std::cout << current->antenna;
			else
				std::cout << ".";
			std::cout << "\033[0m";
			current = current->east;
		}
		std::cout << std::endl;
		first_from_row = first_from_row->south;
	}
}

Tile *access(Tile *map, int x, int y)
{
	int curr_x = 0;
	int curr_y = 0;
	Tile *result = map;

	if (x < 0 || y < 0)
		return (NULL);
	while (curr_x < x)
	{
		result = result->east;
		if (!result)
			return (NULL);
		curr_x++;
	}
	while (curr_y < y)
	{
		result = result->south;
		if (!result)
			return (NULL);
		curr_y++;
	}
	return (result);
}

Tile *create_map(std::string input_text)
{
	Tile	*first = NULL;
	Tile	*current = NULL;
	Tile	*first_from_row = NULL;
	Tile	*current_prev_row = NULL;
	Tile	*previous = NULL;
	int		x = 0;
	int		y = 0;

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
			x = 0;
			y++;
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
			current->loc_x = x;
			current->loc_y = y;
			x++;
		}
	}

	return (first);
}

void set_current_antinodes(Tile *map, Tile *loc)
{
	Tile *aux = loc->it_next;

	while (aux)
	{
		if (aux->has_antenna && aux->antenna == loc->antenna)
		{
			Tile *new_antinode1 = access(map, loc->loc_x - (aux->loc_x - loc->loc_x), loc->loc_y - (aux->loc_y - loc->loc_y));
			Tile *new_antinode2 = access(map, aux->loc_x + (aux->loc_x - loc->loc_x), aux->loc_y + (aux->loc_y - loc->loc_y));
			if (new_antinode1)
			{
				new_antinode1->has_antinode = true;
				if (std::find(new_antinode1->antinodes.begin(), new_antinode1->antinodes.end(), loc->antenna) == new_antinode1->antinodes.end())
					new_antinode1->antinodes.push_back(loc->antenna);
			}
			if (new_antinode2)
			{
				new_antinode2->has_antinode = true;
				if (std::find(new_antinode2->antinodes.begin(), new_antinode2->antinodes.end(), loc->antenna) == new_antinode2->antinodes.end())
					new_antinode2->antinodes.push_back(loc->antenna);
			}
		}
		aux = aux->it_next;
	}
}

void set_antinodes(Tile *map)
{
	Tile *map_it = map;

	while (map_it)
	{
		if (map_it->has_antenna)
		{
			set_current_antinodes(map, map_it);
		}
		map_it = map_it->it_next;
	}
}

int count_antinodes(Tile *map)
{
	int result = 0;
	while (map)
	{
		if (map->has_antinode)
			result++;
		map = map->it_next;
	}
	return (result);
}

int main() {
	std::string input_text = read_file("day8/input.txt");
	Tile *map = create_map(input_text);

	set_antinodes(map);
	// print(map);
	
	std::cout << ">>> " << count_antinodes(map) << std::endl;

	delete (map);

	return 0;
}

