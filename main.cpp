#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y,score;
COORD fruit;
int tailX[100],tailY[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RÝGHT, UP, DOWN};
eDirection dir;

void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position); // set the cursor position

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);
}


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruit.X = rand() % width;
	fruit.Y = rand() % height;
	score = 0;
}
void Draw() {
	clearScreen();
	//system("cls");

	for (int i = 0; i < width+1; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (j == 0 || j == width-1)
				cout << "#";

			if (i == y && j == x)
				cout << "O";
			else if (i == fruit.Y && j == fruit.X)
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
	if (x == fruit.X && y == fruit.Y) {
		score += 10;
		fruit.X = rand() % width;
		fruit.Y = rand() % height;
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
		Sleep(50);
	}
	return 0;
}
