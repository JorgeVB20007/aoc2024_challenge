#include "day12.hpp"

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	region = ' ';
	discovered = false;
}

Tile::Tile(char _region)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	region = _region;
	discovered = false;
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
			std::cout << current->region;
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
		}
	}

	return (first);
}


void flood_fill(Tile *map, int *area, int *perimeter)
{
	*area += 1;
	map->discovered = true;
	if (map->north && map->north->region == map->region && map->north->discovered == false)
	{
		flood_fill(map->north, area, perimeter);
	}
	else if (!map->north || map->north->region != map->region)
	{
		*perimeter += 1;
	}
	if (map->east && map->east->region == map->region && map->east->discovered == false)
	{
		flood_fill(map->east, area, perimeter);
	}
	else if (!map->east || map->east->region != map->region)
	{
		*perimeter += 1;
	}
	if (map->south && map->south->region == map->region && map->south->discovered == false)
	{
		flood_fill(map->south, area, perimeter);
	}
	else if (!map->south || map->south->region != map->region)
	{
		*perimeter += 1;
	}
	if (map->west && map->west->region == map->region && map->west->discovered == false)
	{
		flood_fill(map->west, area, perimeter);
	}
	else if (!map->west || map->west->region != map->region)
	{
		*perimeter += 1;
	}

}

int main() {
	std::string input_text = read_file("day12/input.txt");
	Tile *map = create_map(input_text);

	// print(map);

	Tile *map_it = map;
	int result = 0;

	while (map_it)
	{
		int temp_areas = 0;
		int temp_perimeters = 0;
		if (!map_it->discovered)
		{
			flood_fill(map_it, &temp_areas, &temp_perimeters);
		}
		map_it = map_it->it_next;
		result += temp_areas * temp_perimeters;
	}



	std::cout << ">>> " << result << std::endl;


	delete(map);
	return 0;
}

