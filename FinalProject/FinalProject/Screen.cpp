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
	gotoxy(36, 14);
	cout << "Loading..." << endl;
	gotoxy(30, 16);
	for (int r = 1; r <= 20; r++)
	{
		cout << a;
		Sleep(100);
	}
}

void changeColor(int i) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
