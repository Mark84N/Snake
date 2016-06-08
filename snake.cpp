#include "snake.h"

//[1]
Snake::Snake(const int len /* = 5 by default */ )
    :DEFAULT_DIRECTION(DIRECTIONS::RIGHT){

    body.assign(len, Point(0, 0, '*'));
    body[len-1].setSymbol('@');
}
//[1]

//[2]
std::vector<Point> Snake::getSnakePoints()const{

    return this->body;
}
//[2]

//[3]
void Snake::setSnakePoints(const std::vector<Point>& source){

    if (!source.empty()){
        body = source;
    }
}
//[3]

//[4]
void Snake::makeSnakeMove(DIRECTIONS d){

    DEFAULT_DIRECTION = d;

    /* move head and remember her last position */
    std::pair<int, int> coordinateToRepeat =
            body[currentLength() - 1].getCoordinates();

    if (d == DIRECTIONS::RIGHT){

        coordinateToRepeat.second++;
        body[currentLength() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.second--;

    }
    else if(d == DIRECTIONS::DOWN){

        coordinateToRepeat.first++;
        body[currentLength() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.first--;
    }
    else if(d == DIRECTIONS::LEFT){

        coordinateToRepeat.second--;
        body[currentLength() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.second++;
    }
    else{
        // DIRECTIONS::UP
        coordinateToRepeat.first--;
        body[currentLength() - 1].setCoordinates(coordinateToRepeat);
        coordinateToRepeat.first++;
    }


    std::for_each(body.rbegin()+1, body.rend(),
                  [&coordinateToRepeat](Point& point){

        std::pair<int, int> tempCoordinates = point.getCoordinates();
        point.setCoordinates(coordinateToRepeat);
        coordinateToRepeat = tempCoordinates;

    });
}
//[4]

//[5]
void Snake::increase(){

    body.push_back(Point(0,0,'*'));

    size_t len = this->currentLength();

    for (size_t i = len - 1; i > 0; i--){
        swapPoints(body[i], body[i-1]);
    }
}
//[5]
