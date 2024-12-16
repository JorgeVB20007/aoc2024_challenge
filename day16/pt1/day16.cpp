#include "day16.hpp"


Visit::Visit()
{
	score = -1;
	to_direction = -1;
}

Visit::Visit(int _to_direction)
{
	score = -1;
	to_direction = _to_direction;
}

Visit::~Visit()
{
}

Visit::operator bool() const
{
	return (score != -1);
}


Tile::Tile()
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	wall = false;
}

Tile::Tile(bool _wall)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	wall = _wall;
	for (int idx = 0; idx < 4; idx++)
	{
		visits[idx] = Visit(idx);
	}
}

Tile::operator bool() const
{
	for (int idx = 0; idx < 4; idx++)
	{
		if (visits[idx])
			return (true);
	}
	return (false);
}


Tile::~Tile()
{
	if (it_next)
		delete (it_next);
}

int Tile::best_score(int going_to) const
{
	int best = -1;
	for (int dir = 0; dir < 4; dir++)
	{
		int attempt = visits[dir].score + spin_cost(dir, going_to) * 1000 + 1;
		if (visits[dir] && (best == -1 || attempt < best))
			best = attempt;
	}
	// std::cout << "Going " << going_to << 
	return (best);
}


int Tile::best_score() const
{
	int best = -1;
	for (int dir = 0; dir < 4; dir++)
	{
		int attempt = visits[dir].score;
		if (visits[dir] && (best == -1 || attempt < best))
			best = attempt;
	}
	return (best);
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



void print(Tile *first, Tile *reindeer, Tile *end)
{
	Tile *current;
	Tile *first_from_row = first;

	while (first_from_row)
	{
		current = first_from_row;
		while (current)
		{
			if (current == reindeer)
				std::cout << "\033[1;33mS\033[0m";
			else if (current == end)
				std::cout << "\033[1;32mE\033[0m";
			else
			{
				if (*current)
					std::cout << "\033[0;36m";
				if (current->wall)
					std::cout << "#";
				else
					std::cout << ".";
				if (*current)
					std::cout << "\033[0m";
			}
			
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
				current->visits[EAST].score = 0;
				current->visits[EAST].previous = NULL;
				current->visits[EAST].to_direction = EAST;
			}
			if (*i == 'E')
			{
				*end = current;
			}
		}
	}

	return (first);
}

int spin_cost(int current, int desired)
{
	if (current - desired >= -1 && current - desired <= 1)
	{
		return  (!!(current - desired));
	}
	else if (current - desired == -3 || current - desired == 3)
	{
		return (1);
	}
	else
	{
		return (2);
	}
}

void explore(Tile *map, Tile *current, Tile *end)
{
	if (current == end)
		return ;
	if (!current->north->wall && (!current->north->visits[NORTH] || current->best_score(NORTH) < current->north->visits[NORTH].score))
	{
		current->north->visits[NORTH].score = current->best_score(NORTH);
		current->north->visits[NORTH].previous = current;
		explore(map, current->north, end);
	}
	if (!current->east->wall && (!current->east->visits[EAST] || current->best_score(EAST) < current->east->visits[EAST].score))
	{
		current->east->visits[EAST].score = current->best_score(EAST);
		current->east->visits[EAST].previous = current;
		explore(map, current->east, end);
	}
	if (!current->south->wall && (!current->south->visits[SOUTH] || current->best_score(SOUTH) < current->south->visits[SOUTH].score))
	{
		current->south->visits[SOUTH].score = current->best_score(SOUTH);
		current->south->visits[SOUTH].previous = current;
		explore(map, current->south, end);
	}
	if (!current->west->wall && (!current->west->visits[WEST] || current->best_score(WEST) < current->west->visits[WEST].score))
	{
		current->west->visits[WEST].score = current->best_score(WEST);
		current->west->visits[WEST].previous = current;
		explore(map, current->west, end);
	}
}

int main()
{
	std::string full_text = read_file("day16/input.txt");

	Tile *loc = NULL;
	Tile *end = NULL;
	Tile *map = create_map(full_text, &loc, &end);

	explore(map, loc, end);

	// print(map, loc, end);

	std::cout << ">>> " << end->best_score() << std::endl;

	delete(map);
}

