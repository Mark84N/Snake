#include "gamefield.h"

const int DEFAULT_FLDSIZE = 20;

//[1]
GameField::GameField()
    :scoreValue(0), levelValue(1), millisecDelay(350),
      cherry(0, 0, 3), scoreMessage("\t\tScore: "),
      levelMessage("\t\tLevel: "), greeting(),
      snake(), gameField()
{
    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::vector<Point>lineOfPointsOnField;

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j)
            lineOfPointsOnField.emplace_back(Point(i, j, ' '));

        this->gameField.emplace_back(lineOfPointsOnField);
        lineOfPointsOnField.clear();
    }

    setSnakeStartCoordinates(); // calls once: set start coordinates to snake
    generateCherry();
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
    std::vector<Point> snakeBodyPoints = snake.getSnakeBody();

    std::for_each(snakeBodyPoints.rbegin(),
                  snakeBodyPoints.rend(),
                  [this](Point& point)
    {
        std::pair<int, int> coord = point.getCoordinates();
        this->gameField[coord.first][coord.second] = point;
    });
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
        std::cout << "##";

    std::cout << std::endl;

    /* field + side borders */
    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
    {
        std::cout << "  #";

        for (int j = 0; j < DEFAULT_FLDSIZE; ++j)
            std::cout << gameField[i][j] << ' ';

         std::cout << "#" << std::endl;
    }

    /* bottom border */
    std::cout << "   ";

    for(int i = 0; i < DEFAULT_FLDSIZE; ++i)
        std::cout << "##";

    std::cout << std::endl;

    showScore();
    showLevel();
}
//[5]

//[6]
void GameField::showScore()const
{
    std::cout << scoreMessage + std::to_string(scoreValue)
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
void GameField::setSnakeStartCoordinates()
{
    std::vector<Point> snakeBody = snake.getSnakeBody();
    int x = DEFAULT_FLDSIZE/2;

    for (int y = 0; y < snake.getCurrentLength(); ++y)
    {
        this->gameField[x][y].setSymbol(snakeBody[y].getSymbol());
        snakeBody[y].setCoordinates(std::make_pair(x, y));
    }

    this->snake.setSnakeBody(snakeBody);
}
//[8]

//[9]
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
//[9]

//[10]
bool GameField::didGainCherry()
{
    auto snakeHead = *(snake.getSnakeBody().rbegin());
    auto snakeHeadCoord = snakeHead.getCoordinates();
    auto cherryCoord = cherry.getCoordinates();

    return (snakeHeadCoord == cherryCoord);
}
//[10]

//[11]
void GameField::initGreeting()
{
    greeting = (" _______  __    _  _______  ___   _  _______ \n"
                "|       ||  |  | ||   _   ||   | | ||       |\n"
                "|  _____||   |_| ||  |_|  ||   |_| ||    ___|\n"
                "| |_____ |       ||       ||      _||   |___ \n"
                "|_____  ||  _    ||       ||     |_ |    ___|\n"
                " _____| || | |   ||   _   ||    _  ||   |___ \n"
                "|_______||_|  |__||__| |__||___| |_||_______|\n");
}
//[11]

//[12]
size_t GameField::getCurrLevel()const
{
    return millisecDelay;
}
//[12]

//[13]
DIRECTIONS GameField::getSnakeDirection()const
{
    return snake.getCurrentDirection();
}
//[13]


//[14]
void GameField::showLevel()const
{
    std::cout << levelMessage + std::to_string(levelValue)
              << std::endl;
}
//[14]
