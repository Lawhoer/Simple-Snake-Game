#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RÝGHT, UP, DOWN};
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");

	for (int i = 0; i < width+1; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (j == 0 || j == width-1)
				cout << "#";

			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
			}
				
		}
		cout << endl;
	}

	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RÝGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}	
	}
}
void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;
	for (int i = 1; i < nTail; i++) {
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
	case RÝGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x == width-1 || x < 0 || y == height || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
		
}


int main() {
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}