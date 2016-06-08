#ifndef FIELD_H
#define FIELD_H

#include <snake.h>
#include <random>
#include <string>

const int DEFAULT_FLDSIZE = 20;

class Field{

    size_t scoreValue;
    size_t levelValue;
    size_t millisecDelay;
    Point cherry;
    std::string scoreMessage;
    std::string levelMessage;
    std::string greeting;
    Snake snake;
    std::vector<std::vector<Point>> gameField;


    void firstLocateSnakeOnField();
    bool setSnakeCoordWithinField(std::pair<int, int>& coord);
    void generateCherry();
    bool didGainCherry();
    void initGreeting();

public:

    Field();

    void makeStep(DIRECTIONS d);
    void locateSnakeOnField();
    void removeSnakeFromField();
    DIRECTIONS getSnakeDirection()const{
        return snake.currentDirection();
    }

    void showField()const;
    void showScoreAndLevel()const;
    void showGreeting()const;
    size_t getCurrLevel()const;
};

#endif // FIELD_H
