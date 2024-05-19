#pragma once
#include <string>
#include <vector>

const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

struct Coord
{
	int x;
	int y;
	bool operator==(const Coord& rhs);
	Coord();
	Coord(int x_, int y_);
};

struct Snake
{	
	std::vector<Coord> snake_coord;
	char snake_char;
	int snake_len;
	int snake_direction;
	Snake();
};

struct Food
{
	Coord food_coord;
	char food_char = '@';
};



class Field
{
	int WIDTH;
	int HEIGHT;
public:
	std::string field_string;
	Field(int WIDTH_, int HEIGHT_);
};