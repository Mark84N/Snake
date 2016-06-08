#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <algorithm>
#include <point.h>

const int DEFAULT_LENGTH = 5;
enum class DIRECTIONS{UP, DOWN, LEFT, RIGHT};

class Snake{

    DIRECTIONS DEFAULT_DIRECTION;
    std::vector<Point> body;

public:

    Snake(const int len = DEFAULT_LENGTH);
    std::vector<Point> getSnakePoints()const;
    void setSnakePoints(const std::vector<Point>& source);

    inline DIRECTIONS currentDirection()const{
        return DEFAULT_DIRECTION;
    }
    inline size_t currentLength()const{
        return body.size();
    }
    void makeSnakeMove(DIRECTIONS d);
    void increase();
};

#endif // SNAKE_H
