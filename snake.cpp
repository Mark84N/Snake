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
                           {DIRECTIONS::DOWN, DIRECTIONS::UP} };
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
    if (!source.empty())
        body = source;
}
//[3]

//[4]
void Snake::makeMove(DIRECTIONS newDirection)
{
    if (isOppositeDirection(newDirection))
        newDirection = DEFAULT_DIRECTION;
    else
        DEFAULT_DIRECTION = newDirection;

    auto headCoordinates = body.rbegin()->getCoordinates();
    int xHeadCoord = headCoordinates.first;
    int yHeadCoord = headCoordinates.second;

    auto lastHeadCoordinates = headCoordinates;

    switch (newDirection)
    {
        case DIRECTIONS::RIGHT:{ yHeadCoord = (yHeadCoord + 1 < DEFAULT_FLDSIZE ? yHeadCoord + 1 : 0); } break;
        case DIRECTIONS::DOWN: { xHeadCoord = (xHeadCoord + 1 < DEFAULT_FLDSIZE ? xHeadCoord + 1 : 0); } break;
        case DIRECTIONS::LEFT: { yHeadCoord = (yHeadCoord - 1 >= 0 ? yHeadCoord - 1 : DEFAULT_FLDSIZE-1); } break;
        case DIRECTIONS::UP:   { xHeadCoord = (xHeadCoord - 1 >= 0 ? xHeadCoord - 1 : DEFAULT_FLDSIZE-1); } break;
    }

    headCoordinates.first = xHeadCoord;
    headCoordinates.second = yHeadCoord;

    body.rbegin()->setCoordinates(headCoordinates);

    // continuonesly swap last head coordinate with nearby element, and so on
    std::for_each(body.rbegin()+1, body.rend(),
                  [&lastHeadCoordinates](Point& point)
    {
        std::pair<int, int> tempCoordinates = point.getCoordinates();
        point.setCoordinates(lastHeadCoordinates);
        lastHeadCoordinates = tempCoordinates;
    });
}
//[4]

//[5]
void Snake::increase()
{
    body.push_back(Point(0,0,'*'));

    for (size_t i = body.size() - 1; i > 0; i--)
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
