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
		char	region;
		bool	discovered;

		Tile();
		Tile(char _region);
		~Tile();

};