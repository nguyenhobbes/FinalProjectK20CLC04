#include "CourseRegistrationSystem.h"

void gotoxy(int x, int y)
{
	COORD d;
	d.X = x;
	d.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
}

void loadingScreen() {
	char a = 219;
	gotoxy(50, 14);
	cout << "Loading..." << endl;
	gotoxy(44, 16);
	for (int r = 1; r <= 20; r++)
	{
		cout << a;
		Sleep(50);
	}
}

void changeColor(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
