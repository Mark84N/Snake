#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <algorithm>
#include <point.h>

const int DEFAULT_LENGTH = 5;
enum class DIRECTIONS{UP, DOWN, LEFT, RIGHT};

class Snake
{
public:

    Snake(const int len = DEFAULT_LENGTH);

    std::vector<Point> getSnakeBody()const;
    void setSnakeBody(const std::vector<Point>& source);

    DIRECTIONS getCurrentDirection()const;
    size_t getCurrentLength()const;
    void makeMove(DIRECTIONS d);
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
