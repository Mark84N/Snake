#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <snake.h>
#include <random>
#include <string>

extern const int DEFAULT_FLDSIZE;

class GameField
{
public:

    GameField();

    void makeStep(DIRECTIONS d);
    void locateSnakeOnField();
    void removeSnakeFromField();
    DIRECTIONS getSnakeDirection()const;
    void showField()const;
    void showScore()const;
    void showLevel()const;
    void showGreeting()const;
    size_t getCurrLevel()const;

private:

    void setSnakeStartCoordinates();
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
