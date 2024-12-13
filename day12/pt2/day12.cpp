#include "day12.hpp"

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	region = ' ';
	id = 0;
	borders[0] = 0;
	borders[1] = 0;
	borders[2] = 0;
	borders[3] = 0;
}

Tile::Tile(char _region)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	region = _region;
	id = 0;
	borders[0] = 0;
	borders[1] = 0;
	borders[2] = 0;
	borders[3] = 0;
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
			// std::cout << std::endl << current->borders[0] << " " << current->borders[1] << " " << current->borders[2] << " " << current->borders[3] << std::endl;
			std::cout << current->borders[0] << " " << current->borders[1] << " " << current->borders[2] << " " << current->borders[3] << " " << current->id;
			if (current->borders[0] + current->borders[1] * 100 + current->borders[2] * 10000 + current->borders[3] * 1000000)
				std::cout << "\033[1;33m";
			std::cout << current->region << "\033[0m ";
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



void flood_fill(Tile *map, int *area, int current_id)
{
	*area += 1;
	map->id = current_id;
	if (map->north && map->north->region == map->region && map->north->id == 0)
	{
		flood_fill(map->north, area, current_id);
	}
	if (map->east && map->east->region == map->region && map->east->id == 0)
	{
		flood_fill(map->east, area, current_id);
	}
	if (map->south && map->south->region == map->region && map->south->id == 0)
	{
		flood_fill(map->south, area, current_id);
	}
	if (map->west && map->west->region == map->region && map->west->id == 0)
	{
		flood_fill(map->west, area, current_id);
	}
}



int main() {
	std::string input_text = read_file("day12/input.txt");
	Tile *map = create_map(input_text);

	// print(map);

	Tile *map_it = map;
	int result = 0;
	std::map<int, std::pair<int, int> > results;
	int current_id = 1;

	while (map_it)
	{
		int temp_areas = 0;
		if (!map_it->id)
		{
			flood_fill(map_it, &temp_areas, current_id);
			results[current_id] = std::pair<int, int>(temp_areas, 0);
			current_id++;
		}
		map_it = map_it->it_next;
	}

	map_it = map;
	while (map_it)
	{
		if (!map_it->north)
			map_it->borders[NORTH] = -1;
		else if (map_it->region != map_it->north->region)
			map_it->borders[NORTH] = map_it->north->id;

		if (!map_it->east)
			map_it->borders[EAST] = -1;
		else if (map_it->region != map_it->east->region)
			map_it->borders[EAST] = map_it->east->id;

		if (!map_it->south)
			map_it->borders[SOUTH] = -1;
		else if (map_it->region != map_it->south->region)
			map_it->borders[SOUTH] = map_it->south->id;

		if (!map_it->west)
			map_it->borders[WEST] = -1;
		else if (map_it->region != map_it->west->region)
			map_it->borders[WEST] = map_it->west->id;

		map_it = map_it->it_next;
	}


	map_it = map;
	while (map_it)
	{
		if (map_it->borders[NORTH])
		{
			results[map_it->id].second += 1;	
			Tile *map_aux = map_it;
			while (map_aux && map_aux->id == map_it->id && !map_aux->borders[EAST] && map_aux->borders[NORTH])
			{
				map_aux->borders[NORTH] = 0;
				map_aux = map_aux->east;
			}
			if (map_aux && map_aux->id == map_it->id)
				map_aux->borders[NORTH] = 0;
		}

		if (map_it->borders[EAST])
		{
			results[map_it->id].second += 1;	
			Tile *map_aux = map_it;
			while (map_aux && map_aux->id == map_it->id && !map_aux->borders[SOUTH] && map_aux->borders[EAST])
			{
				map_aux->borders[EAST] = 0;
				map_aux = map_aux->south;
			}
			if (map_aux && map_aux->id == map_it->id)
				map_aux->borders[EAST] = 0;
		}

		if (map_it->borders[SOUTH])
		{
			results[map_it->id].second += 1;	
			Tile *map_aux = map_it;
			while (map_aux && map_aux->id == map_it->id && !map_aux->borders[EAST] && map_aux->borders[SOUTH])
			{
				map_aux->borders[SOUTH] = 0;
				map_aux = map_aux->east;
			}
			if (map_aux && map_aux->id == map_it->id)
				map_aux->borders[SOUTH] = 0;
		}
		if (map_it->borders[WEST])
		{
			results[map_it->id].second += 1;	
			Tile *map_aux = map_it;
			while (map_aux && map_aux->id == map_it->id && !map_aux->borders[SOUTH] && map_aux->borders[WEST])
			{
				map_aux->borders[WEST] = 0;
				map_aux = map_aux->south;
			}
			if (map_aux && map_aux->id == map_it->id)
				map_aux->borders[WEST] = 0;
		}
		map_it = map_it->it_next;
	}


	for (std::map<int, std::pair<int, int> >::iterator it = results.begin(); it != results.end(); it++)
	{
		// std::cout << "> " << it->first << ": " << it->second.first << " * " << it->second.second << " = " << it->second.first * it->second.second << std::endl;
		result += it->second.first * it->second.second;
	}


	std::cout << ">>> " << result << std::endl;


	delete(map);
	return 0;
}

