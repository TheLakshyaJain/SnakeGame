#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[400], tailY[400], ntail;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void Settings()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Visual()
{
    system("cls");
    for (int i = 0; i < width + 2; ++i)
        cout << '#';
    cout << '\n';
    for (int i = 0; i < height; ++i)
    {
        cout << '#';
        for (int j = 0; j < width; ++j)
        {
            if (i == x && j == y)
                cout << 0;
            else if (i == fruitX && j == fruitY)
                cout << "*";
            else
            {
                bool printTail = false;
                for (int k = 0; k < ntail; ++k)
                    if (tailX[k] == i && tailY[k] == j)
                    {
                        cout << 'o';
                        printTail = true;
                        break;
                    }
                if (!printTail)
                    cout << ' ';
            }
        }
        cout << '#';
        cout << '\n';
    }
    for (int i = 0; i < width + 2; ++i)
        cout << '#';
    cout << '\n';
    cout << "Score: " << score << '\n';
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X = x;
    int prev2Y = y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < ntail; ++i)
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
        y--;
        break;
    case RIGHT:
        y++;
        break;
    case UP:
        x--;
        break;
    case DOWN:
        x++;
        break;
    default:
        break;
    }
    if (x == fruitX && y == fruitY)
    {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }
    if (x >= width)
        x = 0;
    if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    if (y < 0)
        y = height - 1;
    for (size_t i = 0; i < ntail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
}

void Input()
{
    if (_kbhit())
    {
        switch (getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    Settings();
    while (!gameOver)
    {
        Visual();
        Input();
        Logic();
        Sleep(90);
    }
    return 0;
}
