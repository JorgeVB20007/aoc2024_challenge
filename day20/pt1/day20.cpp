#include "day20.hpp"


Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	wall = false;
	score = -1;
	is_path = false;
	coming_from = NULL;
	going_to = NULL;
}

Tile::Tile(bool _wall)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	wall = _wall;
	score = -1;
	is_path = false;
	coming_from = NULL;
	going_to = NULL;
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



void print(Tile *first, Tile *loc, Tile *end)
{
	Tile *current;
	Tile *first_from_row = first;

	while (first_from_row)
	{
		current = first_from_row;
		while (current)
		{
			if (current->is_path)
				std::cout << "\033[1;36m";
			if (current == loc)
				std::cout << "\033[1;33mS\033[0m";
			else if (current == end)
				std::cout << "\033[1;32mE\033[0m";
			else
			{
				if (current->is_path)
					std::cout << "\033[0;36m";
				if (current->wall)
					std::cout << "#";
				else
					std::cout << ".";
				std::cout << "\033[0m";
			}
			std::cout << "\033[0m";
			
			current = current->east;
		}
		std::cout << std::endl;
		first_from_row = first_from_row->south;
	}
}


Tile *create_map(std::string input_text, Tile **loc, Tile **end)
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
				current = new Tile(*i == '#');
				first = current;
				previous = current;
			}
			else if (!current)
			{
				current = new Tile(*i == '#');
				previous->it_next = current;
				previous = current;
				current->north = first_from_row;
				first_from_row->south = current;
			}
			else
			{
				current->east = new Tile(*i == '#');
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
			if (*i == 'S')
			{
				*loc = current;
				current->score = 0;
			}
			if (*i == 'E')
			{
				*end = current;
			}
		}
	}

	return (first);
}

void explore(Tile *loc, Tile *end, Tile *map)
{
	if (loc == end)
		return ;
	if (loc->north && !loc->north->wall && (loc->north->score == -1 || loc->north->score > loc->score + 1))
	{
		loc->north->coming_from = loc;
		loc->north->score = loc->score + 1;
		explore(loc->north, end, map);
	}
	if (loc->east && !loc->east->wall && (loc->east->score == -1 || loc->east->score > loc->score + 1))
	{
		loc->east->coming_from = loc;
		loc->east->score = loc->score + 1;
		explore(loc->east, end, map);
	}
	if (loc->south && !loc->south->wall && (loc->south->score == -1 || loc->south->score > loc->score + 1))
	{
		loc->south->coming_from = loc;
		loc->south->score = loc->score + 1;
		explore(loc->south, end, map);
	}
	if (loc->west && !loc->west->wall && (loc->west->score == -1 || loc->west->score > loc->score + 1))
	{
		loc->west->coming_from = loc;
		loc->west->score = loc->score + 1;
		explore(loc->west, end, map);
	}
}

void path_back(Tile *end, Tile *init)
{
	Tile *curr = end;
	while (curr != init)
	{
		curr->is_path = true;
		curr->coming_from->going_to = curr;
		curr = curr->coming_from;
	}
	init->is_path = true;
}

int try_cheats(Tile *init, Tile *end, Tile *map, int diff_min)
{
	int		result = 0;
	Tile	*curr = init;
	while (curr != end)
	{
		if (curr->north && curr->north->wall && curr->north->north && !curr->north->north->wall)
		{
			if (curr->north->north->score - curr->score - 2 >= diff_min)
			{
				result++;
			}
		}
		if (curr->east && curr->east->wall && curr->east->east && !curr->east->east->wall)
		{
			if (curr->east->east->score - curr->score - 2 >= diff_min)
			{
				result++;
			}
		}
		if (curr->south && curr->south->wall && curr->south->south && !curr->south->south->wall)
		{
			if (curr->south->south->score - curr->score - 2 >= diff_min)
			{
				result++;
			}
		}
		if (curr->west && curr->west->wall && curr->west->west && !curr->west->west->wall)
		{
			if (curr->west->west->score - curr->score - 2 >= diff_min)
			{
				result++;
			}
		}
		curr = curr->going_to;
	}
	(void)map;
	return (result);
}

int main()
{
	std::string full_text = read_file("day20/input.txt");

	Tile *loc = NULL;
	Tile *end = NULL;
	Tile *map = create_map(full_text, &loc, &end);

	explore(loc, end, map);
	path_back(end, loc);
	// print(map, loc, end);


	int result = try_cheats(loc, end, map, 100);
	std::cout << ">>> " << result << std::endl;

	delete(map);
}

