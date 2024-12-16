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
	other_box = NULL;
	boxtype = -1;
}

Tile::Tile(char _type)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	other_box = NULL;
	boxtype = -1;
	switch (_type)
	{
		case '.':
			type = EMPTY;
			east = new Tile('.', NULL);
			east->west = this;
			it_next = east;
			break;
		case '@':
			type = ROBOT;
			east = new Tile('.', NULL);
			east->west = this;
			it_next = east;
			break;
		case 'O':
			type = BOX;
			east = new Tile('O', this);
			east->west = this;
			other_box = east;
			it_next = east;
			boxtype = 0;
			break;
		case '#':
			type = WALL;
			east = new Tile('#', NULL);
			east->west = this;
			it_next = east;
			break;
	}
}

Tile::Tile(char _type, Tile *other)
{
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	it_next = NULL;
	other_box = other;
	boxtype = -1;
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
			boxtype = 1;
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



void print(Tile *first, Tile *robot)
{
	Tile *current;
	Tile *first_from_row = first;

	while (first_from_row)
	{
		current = first_from_row;
		while (current)
		{
			if (current == robot)
				std::cout << "\033[1;33m";
			else if (!robot)
				std::cout << "\033[0;91m";
			switch (current->type)
			{
				case EMPTY:
					std::cout << ".";
					break;
				case ROBOT:
					std::cout << "@";
					break;
				case BOX:
					if (!current->boxtype)
						std::cout << "[";
					else
						std::cout << "]";
					break;
				case WALL:
					std::cout << "#";
					break;
				default:
					std::cout << current->type;
			}
			if (current == robot)
				std::cout << "\033[0m";
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
				current_prev_row = first->east;
			}
			else
			{
				first_from_row = first_from_row->south;
				current_prev_row = first_from_row->east;
			}
			current = NULL;
		}
		else
		{
			if (!first)
			{
				current = new Tile(*i);
				first = current;
				current = current->east;
				previous = current;
			}
			else if (!current)
			{
				current = new Tile(*i);
				previous->it_next = current;
				current->north = first_from_row;
				first_from_row->south = current;
				current = current->east;
				current->north = first_from_row->east;
				first_from_row->east->south = current;
				previous = current;

			}
			else
			{
				current->east = new Tile(*i);
				current->east->west = current;
				current = current->east;
				previous->it_next = current;

				if (current_prev_row)
				{
					current_prev_row = current_prev_row->east;
					current->north = current_prev_row;
					current_prev_row->south = current;
				}
				current = current->east;
				if (current_prev_row)
				{
					current_prev_row = current_prev_row->east;
					current->north = current_prev_row;
					current_prev_row->south = current;
				}
				previous = current;

			}
			if (current->west->type == ROBOT)
				*robot_location = current->west;
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

Tile *g_full_map = NULL;

int collides_with_wall(Tile *box, char move)
{
	int result = 0;
	if (move == '^')
	{
		if (box->north->type == EMPTY && box->other_box->north->type == EMPTY)
			return (0);
		else if (box->north->type == WALL || box->other_box->north->type == WALL)
			return (1);
		else
		{
			if (box->north->type == BOX)
				result += collides_with_wall(box->north, move);
			if (box->other_box->north->type == BOX)
				result += collides_with_wall(box->other_box->north, move);
		}
	}
	else if (move == '>')
	{
		if (box->east->east->type == BOX)
			result += collides_with_wall(box->east->east, move);
		else if (box->east->east->type == WALL)
			return (1);
		else
			return (0);
	}
	else if (move == 'v')
	{
		if (box->south->type == EMPTY && box->other_box->south->type == EMPTY)
			return (0);
		else if (box->south->type == WALL || box->other_box->south->type == WALL)
			return (1);
		else
		{
			if (box->south->type == BOX)
				result += collides_with_wall(box->south, move);
			if (box->other_box->south->type == BOX)
				result += collides_with_wall(box->other_box->south, move);
		}
	}
	else if (move == '<')
	{
		if (box->west->west->type == BOX)
			result += collides_with_wall(box->west->west, move);
		else if (box->west->west->type == WALL)
			return (1);
		else
			return (0);
	}
	return (result);
}

void move_boxes(Tile *box, char move)
{
	if (move == '^')
	{
		if (box->north->type == BOX && box->other_box->north->type == BOX && box->north == box->other_box->north->other_box)
			move_boxes(box->north, move);
		else
		{
			if (box->north->type == BOX)
				move_boxes(box->north, move);
			if (box->other_box->north->type == BOX)
				move_boxes(box->other_box->north, move);
		}
		if (box->north->type != BOX && box->other_box->north->type != BOX)
		{
			box->north->type = box->type;
			box->other_box->north->type = box->other_box->type;

			box->north->other_box = box->other_box->north;
			box->other_box->north->other_box = box->north;

			box->north->boxtype = box->boxtype;
			box->other_box->north->boxtype = box->other_box->boxtype;

			box->other_box->type = EMPTY;
			box->other_box->boxtype = -1;
			box->other_box->other_box = NULL;

			box->type = EMPTY;
			box->boxtype = -1;
			box->other_box = NULL;
		}
	}
	else if (move == '>')
	{
		if (box->east->east->type == BOX)
			move_boxes(box->east->east, move);
		if (box->east->east->type != BOX)
		{
			box->east->east->type = box->east->type;
			box->east->east->other_box = box->east;
			box->east->east->boxtype = 1;

			box->east->type = box->type;
			box->east->other_box = box->east->east;
			box->east->boxtype = 0;

			box->type = EMPTY;
			box->other_box = NULL;
			box->boxtype = -1;
		}
	}
	else if (move == 'v')
	{
		if (box->south->type == BOX && box->other_box->south->type == BOX && box->south == box->other_box->south->other_box)
			move_boxes(box->south, move);
		else
		{
			if (box->south->type == BOX)
				move_boxes(box->south, move);
			if (box->other_box->south->type == BOX)
				move_boxes(box->other_box->south, move);
		}
		if (box->south->type != BOX && box->other_box->south->type != BOX)
		{
			box->south->type = box->type;
			box->other_box->south->type = box->other_box->type;

			box->south->other_box = box->other_box->south;
			box->other_box->south->other_box = box->south;

			box->south->boxtype = box->boxtype;
			box->other_box->south->boxtype = box->other_box->boxtype;

			box->other_box->type = EMPTY;
			box->other_box->boxtype = -1;
			box->other_box->other_box = NULL;

			box->type = EMPTY;
			box->boxtype = -1;
			box->other_box = NULL;
		}
	}
	else if (move == '<')
	{
		if (box->west->west->type == BOX)
			move_boxes(box->west->west, move);
		if (box->west->west->type != BOX)
		{
			box->west->west->type = box->west->type;
			box->west->west->other_box = box->west;
			box->west->west->boxtype = 0;

			box->west->type = box->type;
			box->west->other_box = box->west->west;
			box->west->boxtype = 1;

			box->type = EMPTY;
			box->other_box = NULL;
			box->boxtype = -1;
		}
	}
}

static Tile *move_robot(Tile *loc, char move)
{
	if (move == '^')
	{
		if (loc->north->type == EMPTY)
		{
			loc->north->type = ROBOT;
			loc->type = EMPTY;
			return (loc->north);
		}
		else if (loc->north->type == BOX && !collides_with_wall(loc->north, move))
		{
			move_boxes(loc->north, move);
			loc->north->type = ROBOT;
			loc->type = EMPTY;
			return (loc->north);
		}
	}
	else if (move == '>')
	{
		if (loc->east->type == EMPTY)
		{
			loc->east->type = ROBOT;
			loc->type = EMPTY;
			return (loc->east);
		}
		else if (loc->east->type == BOX && !collides_with_wall(loc->east, move))
		{
			move_boxes(loc->east, move);
			loc->east->type = ROBOT;
			loc->type = EMPTY;
			return (loc->east);
		}
	}
	else if (move == 'v')
	{
		if (loc->south->type == EMPTY)
		{
			loc->south->type = ROBOT;
			loc->type = EMPTY;
			return (loc->south);
		}
		else if (loc->south->type == BOX && !collides_with_wall(loc->south, move))
		{
			move_boxes(loc->south, move);
			loc->south->type = ROBOT;
			loc->type = EMPTY;
			return (loc->south);
		}
	}
	else if (move == '<')
	{
		if (loc->west->type == EMPTY)
		{
			loc->west->type = ROBOT;
			loc->type = EMPTY;
			return (loc->west);
		}
		else if (loc->west->type == BOX && !collides_with_wall(loc->west, move))
		{
			move_boxes(loc->west, move);
			loc->west->type = ROBOT;
			loc->type = EMPTY;
			return (loc->west);
		}
	}
	else
	{
		error_and_exit("Error: Unknown move.");
		return (NULL);
	}
	return (loc);
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
			if (current->type == BOX && !current->boxtype)
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

	Tile *loc = NULL;
	Tile *map = create_map(map_text, &loc);

	g_full_map = map;


	for (std::string::iterator c = instructions_text.begin(); c != instructions_text.end(); c++)
	{
		loc = move_robot(loc, *c);
	}


	print(map, loc);
	int result = get_result(map);
	std::cout << ">>> " << result << std::endl;
	delete map;
}

