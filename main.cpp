// Author: Ryan O'Neill
// Date: 14/11/2020
// GitHub: Roneill985

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <ctime>

// initialise global variables
using namespace std;
bool gameOver;
const int width = 25;
const int height = 12;
int x, y, fruitX, fruitY, score, game;
int tailX[1000], tailY[1000];
int nTail;
enum eDirection{ STOP, UP, LEFT, RIGHT, DOWN};
eDirection dir;

// game setup function
void Setup() {
	// set global variables to their starting positions
	srand(time(0));
	gameOver = false;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	game = 1;
}
// function used to draw a frame to the console
void Draw() {
	// draw the wall along the top
	system("cls");
	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	// this is where most of the game is drawn
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			if (j == 0) {// draw the left wall
				cout << "#";
			}
			if (i == y && j == x) {// draw the head of the snake
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {// draw the fruit
				cout << "F";
			}
			else {// draw the tail
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}
			if (j == width - 1){// draw the right wall
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++) {// draw the wall along the bottom
		cout << "#";
	}

	cout << endl;
	cout << endl;
	
	cout << "score: " << score << endl; // draw the score to the screen
	
	
}
// function that checks for input and sets the enum dir accordingly
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': if (dir != RIGHT) { dir = LEFT; }
				break;
		case 'd': if (dir != LEFT) { dir = RIGHT; }
				break;
		case 'w': if (dir != DOWN) { dir = UP; }
				break;
		case 's': if (dir != UP) { dir = DOWN; }
				break;
		case 'x': dir = STOP;
			break;
		}
	}
}
// logic function that decides how most of the game works
void Logic() {
	if (dir != STOP) {// pause function
		// set the start position of the tail in the array
		int prevX = tailX[0];
		int prevY = tailX[0];
		int prev2X, prev2Y;
		// check and set for the rest of the tail at what position it should be at
		for (int i = nTail; i > 0; i--)
		{
			tailX[i] = tailX[i - 1];
			tailY[i] = tailY[i - 1];
		}
		tailX[0] = x;
		tailY[0] = y;


		switch (dir) {// this is the code that moves the snake
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
		default:
			break;
		}
		for (int i = 0; i < nTail; i++) {// if the player touches their tail end the game
			if (tailX[i] == x && tailY[i] == y)
			{
				gameOver = true;
			}
		}
		if (game == 1) {// this checks to see if the player has chosen game one or game 2
			// if its game one, the player cannot go through walls and will die
			if (x > width || x < 0 || y > height || y < 0) {
				gameOver = true;
			}
		}
		else {
			// if its game 2 the player will go through the wall and teleport to the other side
			if (x >= width) {
				x = 0;
			}
			else if (x < 0) {
				x = width - 1;
			}
			if (y >= height) {
				y = 0;
			}
			else if (y < 0) {
				y = height - 1;
			}

		}
		if (x == fruitX && y == fruitY) {// checks to see if the player has touched a fruit
			// if the player has touched a fruit, telelport the fruit elsewhere, increase the tail length and add 10 to the score
			score += 10;
			fruitX = rand() % width;
			fruitY = rand() % height;
			nTail++;
		}
	}
}
// main function
int main() {
	// call the setup function
	Setup();
	// before the game starts, explain the rules and ask for game 1 or 2
	cout << "W, A, S, D to move. X to pause the game." << endl;
	cout << endl;
	cout << "chose game 1 (walls kill you) or game 2 (walls dont kill you) by typing 1 or 2: " << endl;
	string failSafe;
	cin >> failSafe;
	if (failSafe != "1" && failSafe != "2") {// ensure that the player has chosen 1 or 2
		// if it is not 1 or 2, default to 1
		game = 1;
	}
	else {
		// if it is 1 or 2, set the game to the game the player chose
		game = std::stoi(failSafe);
	}

	// while gamover isnt true, keep running the game by calling the draw, iunput and logic functions in that order
	while (!gameOver) {
		Draw();
		// this slows the game down a bit as otherwise it is too fast
		if (dir == LEFT || dir == RIGHT)
		{
			Sleep(1);
		}
		Sleep(25);
		if (dir == UP || dir == DOWN)
		{
			Sleep(45);
		}
		Input();
		Logic();
	}
}