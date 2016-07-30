#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <algorithm>
#include <point.h>

const int DEFAULT_SNAKELENGTH = 5;
extern const int DEFAULT_FLDSIZE;
enum class DIRECTIONS{UP, DOWN, LEFT, RIGHT};

class Snake
{
public:

    Snake(const int len = DEFAULT_SNAKELENGTH);

    std::vector<Point> getSnakeBody()const;
    void setSnakeBody(const std::vector<Point>& source);
    DIRECTIONS getCurrentDirection()const;
    size_t getCurrentLength()const;
    void makeMove(DIRECTIONS newDirection);
    void increase();
    bool didGainBody()const;

private:

    bool isOppositeDirection(DIRECTIONS d);

private:

    DIRECTIONS DEFAULT_DIRECTION;
    std::vector<std::pair<DIRECTIONS, DIRECTIONS>> oppositeDirections;
    std::vector<Point> body;
};

#endif // SNAKE_H
