#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class Tile
{
	public:
		Tile				*north;
		Tile				*east;
		Tile				*south;
		Tile				*west;
		Tile				*it_next;
		bool				has_antenna;
		char				antenna;
		bool				has_antinode;
		std::vector<char>	antinodes;
		int					loc_x;
		int					loc_y;

		Tile();
		Tile(char value);
		~Tile();

};