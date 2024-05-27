#include <ciso646>
#include "objects.h"


Snake::Snake(): snake_char('O'), snake_len(5), snake_direction(LEFT){}


Field::Field(int WIDTH_, int HEIGHT_): WIDTH(WIDTH_), HEIGHT(HEIGHT_)
{   
    std::string top_bottom_string;
    
    for (int i = 0; i < WIDTH - 1; ++i)
    {
        top_bottom_string += '#';
    }
    top_bottom_string += '\n';

    std::string middle_string;
    middle_string += '#';
    for (int i = 1; i < WIDTH - 2; ++i)
    {
        middle_string += ' ';
    }
    middle_string += "#\n";

    field_string += top_bottom_string;

    for (int i = 0; i < HEIGHT - 2; ++i)
        field_string += middle_string;
    field_string += top_bottom_string;

}


bool Coord::operator==(const Coord& rhs)
{
    if (x == rhs.x and y == rhs.y)
        return true;
    return false;
}

Coord::Coord(): x(0), y(0) {}
Coord::Coord(int x_, int y_): x(x_), y(y_) {}