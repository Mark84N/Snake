#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <snake.h>
#include <random>
#include <string>

const int DEFAULT_FLDSIZE = 20;

class GameField
{
public:

    GameField();

    void makeStep(DIRECTIONS d);
    void locateSnakeOnField();
    void removeSnakeFromField();
    DIRECTIONS getSnakeDirection()const;
    void showField()const;
    void showScoreAndLevel()const;
    void showGreeting()const;
    size_t getCurrLevel()const;

private:

    void initSnakeOnField();
    bool setSnakeCoordWithinField(std::pair<int, int>& coord);
    void generateCherry();
    bool didGainCherry();
    void initGreeting();

private:

    size_t scoreValue;
    size_t levelValue;
    size_t millisecDelay;
    Point cherry;
    std::string scoreMessage;
    std::string levelMessage;
    std::string greeting;
    Snake snake;
    std::vector<std::vector<Point>> gameField;
};

#endif // GAMEFIELD_H
