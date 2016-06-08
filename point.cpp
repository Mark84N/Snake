#include "point.h"

//[1]
std::ostream& operator<<(std::ostream& out, const Point& point){

    out << point.symbol;

    return out;
}
//[1]

void swapPoints(Point& left, Point& right){
    Point temp = right;
    right = left;
    left = temp;
}

//[3]
void Point::setSymbol(const char s){

    if (s >= 0 && s <= 255){
        this->symbol = s;
    }
    else{
        std::cerr << "Trying to set incorrect char value to the point!\n";
        exit(1);
    }
}
//[3]

//[4]
void Point::setCoordinates(const std::pair<int, int>& x_y){

    this->coordinates = x_y;
}
//[4]
