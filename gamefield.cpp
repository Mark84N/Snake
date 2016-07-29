#include "gamefield.h"
//[1]
GameField::GameField()
    :scoreValue(0), levelValue(1), millisecDelay(350),
      cherry(0, 0, 3), scoreMessage("\t\tScore: "),
      levelMessage("\t\tLevel: "), greeting(),
      snake(), gameField()
{
    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::vector<Point>pointsLine;

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j)
        {
            pointsLine.emplace_back(Point(i, j, ' '));
        }

        this->gameField.emplace_back(pointsLine);
        pointsLine.clear();
    }

    initSnakeOnField();
    initGreeting();
}
//[1]

//[2]
void GameField::makeStep(DIRECTIONS d)
{
    removeSnakeFromField();
    snake.makeMove(d);
    locateSnakeOnField();

    if (snake.didGainBody())
    {
        std::cerr << "Gained body, game over!\n";
        exit(1);
    }

    if (didGainCherry())
    {
        scoreValue++;

        if(!(scoreValue % 3))
        {
            millisecDelay -= 25;
            levelValue++;
        }

        snake.increase();
        generateCherry();
    }
}
//[2]

//[3]
void GameField::locateSnakeOnField()
{
    std::vector<Point> snakePoints = snake.getSnakeBody();
    /* move along snake points from head to tail */

    bool wereCoordinatesAdjusted = false;

    std::for_each(snakePoints.rbegin(),
                  snakePoints.rend(),
                  [this, &wereCoordinatesAdjusted](Point& point)
    {
        std::pair<int, int> coord = point.getCoordinates();

        /* check if coordinates are within field and correct if not */

        if (setSnakeCoordWithinField(coord))
        {
            point.setCoordinates(coord);
            wereCoordinatesAdjusted = true;
        }
        /* transfer snake's point(node) to the field */
        this->gameField[coord.first][coord.second] = point;
    });

    if (wereCoordinatesAdjusted)
    {
       snake.setSnakeBody(snakePoints);
    }
}
//[3]

//[4]
void GameField::removeSnakeFromField()
{
    std::vector<Point> snakePoints = snake.getSnakeBody();

    std::for_each(snakePoints.rbegin(), snakePoints.rend(),
                  [&](const Point& point){

        std::pair<int, int> c = point.getCoordinates();
        this->gameField[c.first][c.second].setSymbol(' ');
    });
}
//[4]

//[5]
void GameField::showField()const
{
    showGreeting();

    /* upper border */
    std::cout << "   ";

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::cout << "##";
    }
    std::cout << std::endl;

    /* field + side borders */
    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::cout << "  #";

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j)
        {
            std::cout << gameField[i][j] << ' ';
        }

         std::cout << "#" << std::endl;
    }

    /* bottom border */
    std::cout << "   ";

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::cout << "##";
    }

    std::cout << std::endl;

    showScoreAndLevel();
}
//[5]

//[6]
void GameField::showScoreAndLevel()const
{
    std::cout << scoreMessage + std::to_string(scoreValue)
              << std::endl;
    std::cout << levelMessage + std::to_string(levelValue)
              << std::endl;
}
//[6]

//[7]
void GameField::showGreeting()const
{
    std::cout << greeting;
}
//[7]

//[8]
void GameField::initSnakeOnField()
{
    std::vector<Point> snakeBody = snake.getSnakeBody();
    int x = DEFAULT_FLDSIZE/2;

    for (int y = 0; y < snake.getCurrentLength(); ++y)
    {
        this->gameField[x][y].setSymbol(snakeBody[y].getSymbol());
        snakeBody[y].setCoordinates(std::make_pair(x, y));
    }

    this->snake.setSnakeBody(snakeBody);
    generateCherry();
}
//[8]

//[9]
bool GameField::setSnakeCoordWithinField(std::pair<int, int>& coord)
{
    bool wereCoordinatesAdjusted = false;

    if (coord.first == DEFAULT_FLDSIZE)
    {
        coord.first = 0;
        wereCoordinatesAdjusted = true;
    }
    else if(coord.second == DEFAULT_FLDSIZE)
    {
        coord.second = 0;
        wereCoordinatesAdjusted = true;
    }
    else if(coord.first == -1)
    {
        coord.first = DEFAULT_FLDSIZE-1;
        wereCoordinatesAdjusted = true;
    }
    else if(coord.second == -1)
    {
        coord.second = DEFAULT_FLDSIZE-1;
        wereCoordinatesAdjusted = true;
    }

    return wereCoordinatesAdjusted;
}
//[9]

//[10]
void GameField::generateCherry()
{
    std::vector<Point> snakeBody = snake.getSnakeBody();

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> intDistrib(0, DEFAULT_FLDSIZE-1);

    int xCoord, yCoord;

    do
    {
        xCoord = intDistrib(re);
        yCoord = intDistrib(re);
    }
    while(std::find_if(snakeBody.begin(), snakeBody.end(),
                        [&xCoord, &yCoord](const auto& point)
                        {
                            auto coord = point.getCoordinates();
                            return(coord.first == xCoord) && (coord.second == yCoord);

                        }) != snakeBody.end());

    this->gameField[xCoord][yCoord].setSymbol(3);
    cherry.setCoordinates(std::make_pair(xCoord, yCoord));

}
//[10]

//[11]
bool GameField::didGainCherry(){

    auto snakeHead = (*snake.getSnakeBody().rbegin());
    auto snakeHeadCoord = snakeHead.getCoordinates();
    auto cherryCoord = cherry.getCoordinates();

    return (snakeHeadCoord == cherryCoord);
}
//[11]

//[12]
void GameField::initGreeting(){

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
size_t GameField::getCurrLevel()const{

    return millisecDelay;
}
//[13]

//[14]
DIRECTIONS GameField::getSnakeDirection()const
{
    return snake.getCurrentDirection();
}
//[14]


//[15]

//[15]
