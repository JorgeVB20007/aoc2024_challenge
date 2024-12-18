#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


class Tile
{
	public:
		Tile	*north;
		Tile	*east;
		Tile	*south;
		Tile	*west;
		Tile	*it_next;
		bool	corrupted;
		int		score;
		Tile	*coming_from;
		bool	is_path;

		Tile();
		~Tile();
};