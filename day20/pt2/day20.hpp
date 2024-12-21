#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


enum coords
{
	X,
	Y
};

enum minmax
{
	MIN,
	MAX
};


class Tile
{
	public:
		Tile	*north;
		Tile	*east;
		Tile	*south;
		Tile	*west;
		Tile	*it_next;
		bool	wall;
		int		score;
		bool	is_path;
		Tile	*coming_from;
		Tile	*going_to;

		Tile();
		Tile(bool _wall);
		~Tile();
};



