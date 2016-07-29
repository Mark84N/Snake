#ifndef POINT_H
#define POINT_H

#include <utility>
#include <iostream>

class Point
{
public:

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend void swapPoints(Point& left, Point& right);

    Point()
        :coordinates(0, 0), symbol('\0') { }

    Point(const int x, const int y, const char s)
        : coordinates(x, y), symbol(s) { }

    const char getSymbol()const;
    void setSymbol(const char s);

    const std::pair<int, int> Point::getCoordinates() const;
    void setCoordinates(const std::pair<int, int>& x_y);

private:

    char symbol;
    std::pair<int,int> coordinates;
};

#endif // POINT_H

