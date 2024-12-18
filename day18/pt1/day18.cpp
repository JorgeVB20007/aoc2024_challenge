#include "day18.hpp"

Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	corrupted = false;
	score = -1;
	coming_from = NULL;
	is_path = false;
}

Tile::~Tile()
{
	if (it_next)
		delete (it_next);
}


std::vector<std::pair<int, int> > read_file(std::string filename)
{
	std::vector<std::pair<int, int> > list;
	std::string line_x;
	std::string line_y;
	std::ifstream file(filename);
	if (file.is_open())
	{
		while (std::getline(file, line_x, ','))
		{
			std::getline(file, line_y, '\n');
			list.push_back(std::pair<int, int>(std::stoi(line_x), std::stoi(line_y)));
		}
		file.close();
	}
	return (list);
}

// std::vector<std::pair<int, int> >parse_input(std::string filename)
// {
// 	std::vector<std::pair<int, int> > list;
// 	std::string line;

// 	do
// 	{
// 		line = std::getline(full_text);
// 		std::cout << line << std::endl;
// 	}
// 	while (line.length() > 0);
// 	return (list);
// }

Tile *access(Tile *map, int x, int y)
{
	int curr_x = 0;
	int curr_y = 0;
	Tile *result = map;

	while (curr_x++ < x)
		result = result->east;
	while (curr_y++ < y)
		result = result->south;
	return (result);
}

void print(Tile *first, Tile *highlight)
{
	Tile *current;
	Tile *first_from_row = first;

	while (first_from_row)
	{
		current = first_from_row;
		while (current)
		{
			if (current == highlight)
				std::cout << "\033[0;32m";
			if (current->corrupted)
				std::cout << "#";
			else if (current->is_path)
				std::cout << "\033[0;33mo";
			else
				std::cout << ".";
			std::cout << "\033[0m";
			current = current->east;
		}
		std::cout << std::endl;
		first_from_row = first_from_row->south;
	}
}

Tile *create_map(std::vector<std::pair<int, int> > list, Tile **end, int map_size, int bytes_dropped)
{
	Tile	*first = NULL;
	Tile	*current = NULL;
	Tile	*first_from_row = NULL;
	Tile	*current_prev_row = NULL;
	Tile	*previous = NULL;

	for (int y = 0; y < map_size; y++)
	{
		for (int x = 0; x <= map_size; x++)
		{
			if (x == map_size)
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
					current = new Tile();
					first = current;
					previous = current;
				}
				else if (!current)
				{
					current = new Tile();
					previous->it_next = current;
					previous = current;
					current->north = first_from_row;
					first_from_row->south = current;
				}
				else
				{
					current->east = new Tile();
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
				if (x == y && x == map_size - 1)
				{
					*end = current;
				}
		}
		}
	}
	for (int idx = 0; idx < bytes_dropped; idx++)
	{
		access(first, list[idx].first, list[idx].second)->corrupted = true;
	}

	return (first);
}

void explore(Tile *init, Tile *end)
{
	if (init == end)
		return ;
	if (init->north && !init->north->corrupted && (init->north->score == -1 || init->north->score > init->score + 1))
	{
		init->north->coming_from = init;
		init->north->score = init->score + 1;
		explore(init->north, end);
	}
	if (init->east && !init->east->corrupted && (init->east->score == -1 || init->east->score > init->score + 1))
	{
		init->east->coming_from = init;
		init->east->score = init->score + 1;
		explore(init->east, end);
	}
	if (init->south && !init->south->corrupted && (init->south->score == -1 || init->south->score > init->score + 1))
	{
		init->south->coming_from = init;
		init->south->score = init->score + 1;
		explore(init->south, end);
	}
	if (init->west && !init->west->corrupted && (init->west->score == -1 || init->west->score > init->score + 1))
	{
		init->west->coming_from = init;
		init->west->score = init->score + 1;
		explore(init->west, end);
	}
}

int count_steps(Tile *init, Tile *end)
{
	Tile	*curr = end;
	int		retval = 0;

	while (curr != init)
	{
		curr->is_path = true;
		curr = curr->coming_from;
		retval++;
	}
	return (retval);
}

int main()
{
	std::vector<std::pair<int, int> > input = read_file("day18/input.txt");


	Tile *end = NULL;
	Tile *map = create_map(input, &end, 71, 1024);
	explore(map, end);

	int steps = count_steps(map, end);
	print(map, NULL);
	std::cout << ">>> " << steps << std::endl;
	delete(map);

}