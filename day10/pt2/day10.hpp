#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class Tile
{
	public:
		Tile	*north;
		Tile	*east;
		Tile	*south;
		Tile	*west;
		Tile	*it_next;
		int		height;

		Tile();
		Tile(int _height);
		~Tile();

};