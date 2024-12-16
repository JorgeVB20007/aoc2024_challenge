#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


enum tiletype
{
	EMPTY,
	WALL
};

enum directions
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Tile;

class Visit
{
	public:
		int score;
		int to_direction;
		Tile *previous;

		Visit();
		Visit(int _to_direction);
		~Visit();

		operator bool() const;

		
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
		Visit	visits[4];
		bool	viewable;

		Tile();
		Tile(bool _wall);
		~Tile();

		const Visit &best_score_prev() const;
		int best_score_coming_from(int coming_from) const;
		int best_score(int going_to) const;
		int best_score() const;
		operator bool() const;

};

int spin_cost(int current, int desired);


