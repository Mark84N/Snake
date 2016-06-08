#include "field.h"
//[1]
Field::Field()
    :scoreValue(0), levelValue(1), millisecDelay(350),
      cherry(0, 0, 3), scoreMessage("\t\tScore: "),
      levelMessage("\t\tLevel: "), greeting(){

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i){

        std::vector<Point>pointsLine;

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j){

            pointsLine.emplace_back(Point(i, j, ' '));
        }

        this->gameField.emplace_back(pointsLine);
        pointsLine.clear();
    }

    firstLocateSnakeOnField();
    initGreeting();
}
//[1]

//[2]
void Field::makeStep(DIRECTIONS d){

    removeSnakeFromField();
    snake.makeSnakeMove(d);
    locateSnakeOnField();

    if (didGainCherry()){

        scoreValue++;

        if(!(scoreValue % 3)){
            millisecDelay -= 25;
            levelValue++;
        }

        snake.increase();
        generateCherry();
    }else if (didGainItself()){

    }
}
//[2]

//[3]
void Field::locateSnakeOnField(){

    std::vector<Point> snakePoints = snake.getSnakePoints();
    /* move along snake points from head to tail */

    bool isCorrectedFlag = false;

    std::for_each(snakePoints.rbegin(),
                  snakePoints.rend(),
                  [this, &isCorrectedFlag](Point& point){

        std::pair<int, int> coord = point.getCoordinates();

        /* check if coordinates are within field and correct if not */

        if (setSnakeCoordWithinField(coord)) {

            point.setCoordinates(coord);
            isCorrectedFlag = true;
        }
        /* assign the snake's point(node) to field */
        this->gameField[coord.first][coord.second] = point;
    });

    if (isCorrectedFlag){

        /* assign modified coordinates */
       snake.setSnakePoints(snakePoints);
    }
}
//[3]

//[4]
void Field::removeSnakeFromField(){

    std::vector<Point> snakePoints = snake.getSnakePoints();

    std::for_each(snakePoints.rbegin(), snakePoints.rend(),
                  [&](const Point& point){

        std::pair<int, int> c = point.getCoordinates();
        this->gameField[c.first][c.second].setSymbol(' ');
    });
}
//[4]

//[5]
void Field::showField()const{

    showGreeting();

    /* upper border */
    std::cout << "   ";

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i){

        std::cout << "##";
    }
    std::cout << std::endl;

    /* field + side borders */
    for(int i = 0; i < DEFAULT_FLDSIZE; ++i){

        std::cout << "  #";

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j){

            std::cout << gameField[i][j] << ' ';
        }

         std::cout << "#" << std::endl;
    }

    /* bottom border */
    std::cout << "   ";

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i){

        std::cout << "##";
    }

    std::cout << std::endl;

    showScoreAndLevel();
}
//[5]

//[6]
void Field::showScoreAndLevel()const{

    std::cout << scoreMessage + std::to_string(scoreValue)
              << std::endl;
    std::cout << levelMessage + std::to_string(levelValue)
              << std::endl;
}
//[6]

//[7]
void Field::showGreeting()const{

    std::cout << greeting;
}
//[7]

//[8]
void Field::firstLocateSnakeOnField(){

    std::vector<Point> snakePoints = this->snake.getSnakePoints();

    int x = DEFAULT_FLDSIZE/2;

    for (int y = 0; y < snake.currentLength(); ++y){

        this->gameField[x][y].setSymbol( snakePoints[y].getSymbol() );
        snakePoints[y].setCoordinates(std::make_pair(x, y));
    }

    this->snake.setSnakePoints(snakePoints);
    generateCherry();
}
//[8]

//[9]
bool Field::setSnakeCoordWithinField(std::pair<int, int>& coord){

    bool isCorrectedFlag = false;

    if (coord.first == DEFAULT_FLDSIZE){

        coord.first = 0;
        isCorrectedFlag = true;
    }
    else if(coord.second == DEFAULT_FLDSIZE){

        coord.second = 0;
        isCorrectedFlag = true;
    }
    else if(coord.first == -1){

        coord.first = DEFAULT_FLDSIZE-1;
        isCorrectedFlag = true;
    }
    else if(coord.second == -1){

        coord.second = DEFAULT_FLDSIZE-1;
        isCorrectedFlag = true;
    }

    return isCorrectedFlag;
}
//[9]

//[10]
void Field::generateCherry(){

    std::vector<Point> snakePoints = snake.getSnakePoints();

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> intDistrib(0, DEFAULT_FLDSIZE-1);

    int x ;
    int y;

    do {

        x = intDistrib(re);
        y = intDistrib(re);

    }while(std::find_if(snakePoints.begin(), snakePoints.end(),
                        [&x, &y](const auto& point){
                            auto coord = point.getCoordinates();

                            return(coord.first == x) || (coord.second == y);
    }) != snakePoints.end());

    this->gameField[x][y].setSymbol(3);
    cherry.setCoordinates(std::make_pair(x, y));

}
//[10]

//[11]
bool Field::didGainCherry(){

    auto snakeHead = snake.getSnakePoints()[snake.currentLength()-1];
    snakeHead.getSymbol();
    auto snakeHeadCoord = snakeHead.getCoordinates();
    auto cherryCoord = cherry.getCoordinates();

    return (snakeHeadCoord == cherryCoord);
}
//[11]

//[12]
void Field::initGreeting(){

    greeting = (" _______  __    _  _______  ___   _  _______ \n"
                "|       ||  |  | ||   _   ||   | | ||       |\n"
                "|  _____||   |_| ||  |_|  ||   |_| ||    ___|\n"
                "| |_____ |       ||       ||      _||   |___ \n"
                "|_____  ||  _    ||       ||     |_ |    ___|\n"
                " _____| || | |   ||   _   ||    _  ||   |___ \n"
                "|_______||_|  |__||__| |__||___| |_||_______|\n");

}
//[12]

//[13]
size_t Field::getCurrLevel()const{

    return millisecDelay;
}
//[13]

//[14]
bool Field::didGainItself(){

    return false;
}
//[14]
