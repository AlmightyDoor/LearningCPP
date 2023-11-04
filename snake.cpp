#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup();
void Draw();
void Input();
void Logic();

int main()
{
    srand(time(0));
    eDirection joe = LEFT;
    std::cout << joe;
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls"); // clears console terminal

    //top row
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    //middle rows
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //left border
            if (j == 0)
            {
                std::cout << "#";
            }
            
            //snake head
            if (i == y && j == x)
            {
                std::cout << "O";
            }
            //fruit
            else if(i == fruitY && j == fruitX)
            {
                std::cout << "F";
            }
            //tail and empty spaces
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    std::cout << " ";
                }
            }
            
            //right border
            if(j == width - 1)
            {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }

    //bottom row
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    //score
    std::cout << "Score: " << score;
}
void Input()
{
    if (_kbhit()) // _kbhit returns 1 if kb pressed, 0 if not
    {
        switch (_getch()) // _getch gets ascii value of char pressed
        {
            case 'a':
                if (dir == RIGHT)
                {
                    break;
                }
                dir = LEFT;
                break;
            case 'd':
                if (dir == LEFT)
                {
                    break;
                }
                dir = RIGHT;
                break;
            case 'w':
                if (dir == DOWN)
                {
                    break;
                }
                dir = UP;
                break;
            case 's':
                if (dir == UP)
                {
                    break;
                }
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case STOP:
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY)
    {
        nTail++;
        score += 1;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}