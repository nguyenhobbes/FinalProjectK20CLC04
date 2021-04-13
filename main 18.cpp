#include "moodle.h"

void setScoreRandomly()
{
	academic_year* years = nullptr;
	int n_year;
	readSemesterTXT(years, n_year);
	for (int i = 0; i < n_year; i++)
	{
		for (int j = 0; j < years[i].n_term; j++)
		{
			for (int k = 0; k < years[i].terms[j].n_course; k++)
			{
				course c;
				student* s = nullptr;
				int n_student;
				//Đọc thông tin sv và course
				readCourseIDTXT(years[i].terms[j].courses[k].id, c, s, n_student, years[i].terms[j].courses[k].class_name);
				//Tạo điểm của từng sv
				for (int p = 0; p < n_student; p++)
				{
					s[p].bonus = rand() % 10 + 1;
					s[p].lab = rand() % 10 + 1;
					s[p].midterm = rand() % 10 + 1;
					s[p].final_point = rand() % 10 + 1;
					s[p].gpa = s[p].bonus * 0.1 + s[p].lab * 0.2 + s[p].midterm * 0.2 + s[p].final_point * 0.5;
				}
				saveCourseIDTXT(c, s, n_student, years[i].terms[j].courses[k].class_name);
			}
		}
	}
}
void setAttendanceRandomly()
{
	academic_year* years = nullptr;
	int n_year;
	readSemesterTXT(years, n_year);
	time_t w = time(0);
	tm now;
	localtime_s(&now, &w);
	for (int i = 0; i < n_year; i++)
	{
		for (int j = 0; j < years[i].n_term; j++)
		{
			for (int k = 0; k < years[i].terms[j].n_course; k++)
			{
				course c;
				student* s = nullptr;
				int n_student;
				//Đọc thông tin sv và course
				readCourseIDTXT(years[i].terms[j].courses[k].id, c, s, n_student, years[i].terms[j].courses[k].class_name);
				courseDateGenerator(c);
				//Tạo điểm của từng sv
				for (int p = 0; p < n_student; p++)
				{
					for (int q = 0; q < c.n_course_date; q++)
					{
						if (!((c.course_date[q].yyyy > now.tm_year + 1900) || (c.course_date[q].dd > now.tm_mday && c.course_date[q].mm == now.tm_mon + 1)))
						{
							int whatever = rand() % 10;
							if (whatever < 9)
							{
								s[p].attendance[q] = true;
							}
							else
								s[p].attendance[q] = false;
						}
						else
							break;
					}					
				}
				saveCourseIDTXT(c, s, n_student, years[i].terms[j].courses[k].class_name);
			}
		}
	}

}
int main()
{
	SetConsoleTitle("MOODLE");
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow,
		GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	loginMenu();
	_getch();
	return 0;
}