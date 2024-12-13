#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


enum directions
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum checkings
{
	UNNECESSARY,
	UNCHECKED,
	CHECKED
};

class Tile
{
	public:
		Tile	*north;
		Tile	*east;
		Tile	*south;
		Tile	*west;
		Tile	*it_next;
		char	region;
		int		id;
		int		borders[4];

		Tile();
		Tile(char _region);
		~Tile();

};