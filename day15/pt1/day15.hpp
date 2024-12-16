#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


enum tiletype
{
	EMPTY,
	ROBOT,
	BOX,
	WALL
};

class Tile
{
	public:
		Tile	*north;
		Tile	*east;
		Tile	*south;
		Tile	*west;
		Tile	*it_next;
		int		type;

		Tile();
		Tile(char _type);
		~Tile();

};
