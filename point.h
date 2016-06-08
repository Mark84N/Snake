#ifndef POINT_H
#define POINT_H

#include <utility>
#include <iostream>

class Point {

    /* visual representation on the field */
    char symbol;

    std::pair<int,int> coordinates;

public:

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend void swapPoints(Point& left, Point& right);

    Point()
        :coordinates(0, 0), symbol('\0') { }

    Point(const int x, const int y, const char s)
        : coordinates(x, y), symbol(s){ }

    inline const char getSymbol()const{
        return symbol;
    }
    void setSymbol(const char s);

    inline const std::pair<int, int> Point::getCoordinates() const{

        return coordinates;
    }
    void setCoordinates(const std::pair<int, int>& x_y);

};

#endif // POINT_H

