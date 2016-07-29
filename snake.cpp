#include "snake.h"

//[1]
Snake::Snake(const int len /* = 5 by default */ )
    :DEFAULT_DIRECTION(DIRECTIONS::RIGHT)
{
    body.assign(len, Point(0, 0, '*'));
    body[len-1].setSymbol('@');

    oppositeDirections = { {DIRECTIONS::RIGHT, DIRECTIONS::LEFT},
                           {DIRECTIONS::LEFT, DIRECTIONS::RIGHT},
                           {DIRECTIONS::UP, DIRECTIONS::DOWN},
                           {DIRECTIONS::DOWN, DIRECTIONS::UP}};
}
//[1]

//[2]
std::vector<Point> Snake::getSnakeBody()const
{
    return this->body;
}
//[2]

//[3]
void Snake::setSnakeBody(const std::vector<Point>& source)
{
    if (!source.empty()){
        body = source;
    }
}
//[3]

//[4]
void Snake::makeMove(DIRECTIONS d)
{
    if (isOppositeDirection(d))
        d = DEFAULT_DIRECTION;
    else
        DEFAULT_DIRECTION = d;

    /* move head and remember her last position */
    std::pair<int, int> coordinateToRepeat =
            body[body.size() - 1].getCoordinates();

    if (d == DIRECTIONS::RIGHT)
    {
        coordinateToRepeat.second++;
        body[body.size() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.second--;
    }
    else if(d == DIRECTIONS::DOWN)
    {
        coordinateToRepeat.first++;
        body[body.size() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.first--;
    }
    else if(d == DIRECTIONS::LEFT)
    {
        coordinateToRepeat.second--;
        body[body.size() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.second++;
    }
    else
    {
        coordinateToRepeat.first--;
        body[body.size() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.first++;
    }

    std::for_each(body.rbegin()+1, body.rend(),
                  [&coordinateToRepeat](Point& point)
    {
        std::pair<int, int> tempCoordinates = point.getCoordinates();
        point.setCoordinates(coordinateToRepeat);
        coordinateToRepeat = tempCoordinates;
    });
}
//[4]

//[5]
void Snake::increase()
{
    body.push_back(Point(0,0,'*'));

    size_t len = body.size();

    for (size_t i = len - 1; i > 0; i--)
        swapPoints(body[i], body[i-1]);
}
//[5]

//[6]
bool Snake::didGainBody()const
{
    bool didGainBody = false;
    auto headCoord = body.rbegin()->getCoordinates();

    for(auto &bodyNode = body.rbegin() + 2;
        bodyNode != body.rend();
        bodyNode++)
    {
        if (headCoord == bodyNode->getCoordinates())
        {
            didGainBody = true;
            break;
        }
    }

    return didGainBody;
}
//[6]

//[7]
bool Snake::isOppositeDirection(DIRECTIONS d)
{
    bool isNewOppositeDirection = false;

    for (const auto& oppositesPair: oppositeDirections)
    {
        if (oppositesPair.first == d && oppositesPair.second == DEFAULT_DIRECTION)
        {
            isNewOppositeDirection = true;
            break;
        }
    }

    return isNewOppositeDirection;
}
//[7]

//[8]
DIRECTIONS Snake::getCurrentDirection()const
{
    return DEFAULT_DIRECTION;
}
//[8]

//[9]
size_t Snake::getCurrentLength()const
{
    return body.size();
}
//[9]


