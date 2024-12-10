#include "day10.hpp"

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	height = -1;
}

Tile::Tile(int _height)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	height = _height;
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
			std::cout << current->height;
			current = current->east;
		}
		std::cout << std::endl;
		first_from_row = first_from_row->south;
	}
}


Tile *create_map(std::string input_text)
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
				current = new Tile(*i - '0');
				first = current;
				previous = current;
			}
			else if (!current)
			{
				current = new Tile(*i - '0');
				previous->it_next = current;
				previous = current;
				current->north = first_from_row;
				first_from_row->south = current;
			}
			else
			{
				current->east = new Tile(*i - '0');
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
		}
	}

	return (first);
}

int explore_path(Tile *map_it, std::vector<Tile *> *already_found)
{
	if (!map_it)
		return (0);

	int curr_height = map_it->height;
	int result = 0;

	if (curr_height == 9 && !std::count(already_found->begin(), already_found->end(), map_it))
	{
		already_found->push_back(map_it);
		return(1);
	}
	
	if (map_it->north && map_it->north->height == curr_height + 1)
		result += explore_path(map_it->north, already_found);
	if (map_it->east && map_it->east->height == curr_height + 1)
		result += explore_path(map_it->east, already_found);
	if (map_it->south && map_it->south->height == curr_height + 1)
		result += explore_path(map_it->south, already_found);
	if (map_it->west && map_it->west->height == curr_height + 1)
		result += explore_path(map_it->west, already_found);

	return (result);
}

int main() {
	std::string input_text = read_file("day10/input.txt");
	Tile *map = create_map(input_text);

	//print(map);


	Tile *map_it = map;
	unsigned long long result = 0;
	std::vector<Tile *> already_found;

	while (map_it)
	{
		if (map_it->height == 0)
		{
			result += explore_path(map_it, &already_found);
			already_found.clear();
		}
		map_it = map_it->it_next;
	}
	delete (map);


	std::cout << ">>> " << result << std::endl;

	return 0;
}

