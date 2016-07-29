#include "point.h"

//[1]
std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << point.symbol;

    return out;
}
//[1]

//[2]
void swapPoints(Point& left, Point& right)
{
    Point temp = right;
    right = left;
    left = temp;
}
//[2]

//[3]
void Point::setSymbol(const char s)
{
    if (s >= 0 && s <= 255)
    {
        this->symbol = s;
    }
    else
    {
        std::cerr << "Trying to set incorrect char value to the point!\n";
        exit(1);
    }
}
//[3]

//[4]
void Point::setCoordinates(const std::pair<int, int>& x_y)
{
    coordinates = x_y;
}
//[4]

//[5]
const char Point::getSymbol()const
{
    return symbol;
}
//[5]

//[6]
const std::pair<int, int> Point::getCoordinates() const
{
    return coordinates;
}
//[6]
