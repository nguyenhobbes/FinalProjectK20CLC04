#pragma once
#ifndef _MOODLE_H_
#define _MOODLE_H_

#define _WIN32_WINNT 0x0500
#define OInfo 7
#define WOInfo 8
#define Notice 14
#define NormalT 15
#define TitleFunc 78
#define InBoard 112
#define MidP 112
#define AboveP 124
#define BelowP 126
#define TitleBoard 128
#define SpTitleFunc 142
#define DucTuan 223
#define Input__ 232
#define Attendance_Absent 116
#define Attendance_Checkin 114

#define KEY_UP		72
#define KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_DOWN	80
#define ENTER		13
#define BACK_SPACE	8

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <direct.h>
#include <iomanip>
#include <Windows.h>
#include <filesystem>
#include "sha2.h"
#include <malloc.h>
#include <memory.h>
#include <sstream>


using namespace std;
class	student;
struct	date
{
	int	dd;
	int	mm;
	int	yyyy;
	bool operator == (const date &d1)
	{
		return (dd == d1.dd && mm == d1.mm && yyyy == d1.yyyy);
	}
	bool operator != (const date &d1)
	{
		return !(dd == d1.dd && mm == d1.mm && yyyy == d1.yyyy);
	}
	bool operator > (const date& d1)
	{
		if (yyyy > d1.yyyy)
			return true;
		else if (yyyy < d1.yyyy)
			return false;
		if (mm > d1.mm)
			return true;
		else if (mm < d1.mm)
			return false;
		if (dd > d1.dd)
			return true;
		return false;
	}
	bool operator < (const date& d1)
	{
		if (yyyy < d1.yyyy)
			return true;
		else if (yyyy > d1.yyyy)
			return false;
		if (mm < d1.mm)
			return true;
		else if (mm > d1.mm)
			return false;
		if (dd < d1.dd)
			return true;
		return false;
	}
	
};
struct	hour
{
	int	hh;
	int	mm; //

	bool operator == (const hour &h1)
	{
		return (h1.hh == hh && h1.mm == mm);
	}
	bool operator != (const hour &h1)
	{
		return !(h1.hh == hh && h1.mm == mm);
	}
	bool operator < (const hour &h1)
	{
		if (hh < h1.hh)
			return true;
		if (hh > h1.hh)
			return false;
		if (mm < h1.mm)
			return true;
		return false;
	}
	bool operator > (const hour &h1)
	{
		if (hh > h1.hh)
			return true;
		if (hh < h1.hh)
			return false;
		if (mm > h1.mm)
			return true;
		return false;
	}
	bool operator >= (const hour& h1)
	{
		return operator > (h1) || operator == (h1);
	}
	bool operator <= (const hour& h1)
	{
		return operator < (h1) || operator == (h1);
	}

	
};
struct	dayhour
{
	int	 dd;
	int	 mm;
	int	 yyyy;
	int	 start_hh;
	int	 start_min;
	int	 end_hh;
	int	 end_min;
	/*bool operator == (const dayhour &d1)
	{
		return (dd == d1.dd && mm == d1.mm && yyyy == d1.yyyy
			&& start_hh == d1.start_hh && start_min == d1.start_min
			&& end_hh == d1.end_hh && end_min == d1.end_min);
	}*/
	
};
class	studentID
{
public:
	studentID();
	int			id;
	string		class_name;
	string		last_name;
	string		first_name;

	template <class T>void	operator = (const T &s1)
	{
		id = s1.id;
		class_name = s1.class_name;
		last_name = s1.last_name;
		first_name = s1.first_name;
	}
	template <class T>bool	operator > (const T &s1)
	{
		return (id > s1.id);
	}
	template <class T>bool	operator < (const T &s1)
	{
		return (id < s1.id);
	}
	template <class T>bool	operator == (const T &s1)
	{
		return (id == s1.id);
	}
	template <class T>bool	operator !=(const T &s1)
	{
		return (id != s1.id);
	}
};
class	student
{
public:
	student();
	~student();

	int			no;
	int			id;
	string		last_name;
	string		first_name;
	int			gender; //0: Male, 1: Female, */-1: Other/* :d	
	date		dob;
	string		account;
	string		default_password;
	string		class_name;  //ký tự lưu trữ nên để dưới dạng chữ hoa

	// Struct student lưu trữ trong course
	double		midterm; // Điểm giữa kỳ
	double		final_point; // Điểm cuối kỳ
	double		lab; // Điểm thực hành
	double		bonus; // Điểm cộng
	double		gpa; // Điểm trung bình (Nếu có)
	bool*		attendance; // điểm danh hs trong một khóa học, dùng kèm trong course date
	int			n_date;
	string		password;

	void	operator = (const student &s1)
	{
		no			= s1.no;
		id			= s1.id;
		gender		= s1.gender;		
		dob			= s1.dob;
		last_name	= s1.last_name;
		first_name	= s1.first_name;
		account		= s1.account;
		default_password = s1.default_password;
		class_name	= s1.class_name;
		password	= s1.password;

		// Struct student lưu trữ trong course
		midterm		= s1.midterm;		// Điểm giữa kỳ
		final_point = s1.final_point;	// Điểm cuối kỳ
		lab			= s1.lab;			// Điểm thực hành
		bonus		= s1.bonus;			// Điểm cộng
		gpa			= s1.gpa;			// Điểm trung bình (Nếu có)
		n_date		= s1.n_date;
		if (s1.attendance != NULL)
		{
			if (attendance != NULL)
				delete[] attendance;
			attendance = new bool[s1.n_date];
			for (int i = 0; i < s1.n_date; i++)
			{
				attendance[i] = s1.attendance[i];
			}
		}
		else
		{
			delete[] attendance;
			attendance = NULL;
		}
	}
	void	operator = (const studentID &s1)
	{
		id = s1.id;
		class_name = s1.class_name;
		last_name = s1.last_name;
		first_name = s1.first_name;
	}
	template <class T>bool	operator > (const T &s1)
	{
		return (id > s1.id);
	}
	template <class T>bool	operator < (const T &s1)
	{
		return (id < s1.id);
	}
	template <class T>bool	operator == (const T &s1)
	{
		return (id == s1.id);
	}
	template <class T>bool	operator != (const T &s1)
	{
		return (id != s1.id);
	}
};
struct	courseID
{
	// Struct chỉ lưu thông tin ID course, tên lớp
	string		id;
	string		class_name;
	template <class T> void operator = (T &c)
	{
		id = c.id;
		class_name = c.class_name;
	}
	template <class COURSE> bool operator ==(COURSE &c)
	{
		return (id == c.id && class_name == c.class_name);
	}
	template <class COURSE> bool operator !=(COURSE &c)
	{
		return (id != c.id || class_name != c.class_name);
	}
};
class	term
{
public:
	term();
	~term();

	int		no; // HK1, HK2. HK3 - (Autumn, Spring, Summer)
	int		n_course; // SL course trong một term
	courseID* courses;
	void	operator=(term &t)
	{
		no = t.no;
		n_course = t.n_course;
		if (t.n_course == 0)
		{
			if (courses != NULL)
				delete[] courses;
			courses = NULL;
		}
		else
		{
			if (courses != NULL)
				delete[]courses;
			courses = new courseID[t.n_course];
			for (int i = 0; i < t.n_course; i++)
			{
				courses[i] = t.courses[i];
			}
		}
	}
};
class	academic_year
{
public:
	academic_year();
	~academic_year();

	int		start; //Năm bắt đầu năm học
	int		end;
	term*	terms; // i = 0: HK1, i=1: HK2, i =2: HK3
	int		n_term; // Số HK có trong năm học
	void	operator=(academic_year &y)
	{
		start = y.start;
		end = y.end;
		n_term = y.n_term;
		if (terms != NULL)
			delete[] terms;
		if (y.n_term == 0)
		{
			terms = NULL;
		}
		else
		{
			terms = new term[y.n_term];
			for (int i = 0; i < y.n_term; i++)
			{
				terms[i] = y.terms[i];
			}
		}
	}
	bool	operator > (const academic_year &yr)
	{
		return (start > yr.start);
	}
	bool	operator < (const academic_year &yr)
	{
		return (start < yr.start);
	}
	bool	operator == (const academic_year &yr)
	{
		return (start == yr.start);
	}
	bool	operator != (const academic_year &yr)
	{
		return (start != yr.start);
	}
};
class	lecturer
{
public:
	lecturer();
	~lecturer();
	string			name;
	string			account;
	int				n_year;
	academic_year*	years;
	string			password;
	void			operator=(lecturer &l)
	{
		name = l.name;
		account = l.account;
		n_year = l.n_year;
		if (years != NULL)
			delete[] years;
		if (l.n_year == 0)
			years = NULL;
		else
		{
			years = new academic_year[l.n_year];
			for (int i = 0; i < l.n_year; i++)
			{
				years[i] = l.years[i];
			}
		}
		password = l.password;
	}
};
class	course
{
	// struct lưu đầy đủ thông tin course
public:
	course();
	~course();
	string		id;
	string		name;
	string		class_name;
	string		lecturer;
	date		start_date;
	date		end_date;
	dayhour*	course_date;
	int			n_course_date;
	int			n_student;
	bool		dow[7];				// Date of week: lập mảng bool để xem ngày nào có tiết, (0 = CN, 1 = Thứ 2, 2 = Thứ 3...)
	hour		start_hour[7];		// Start, end hour có thể khác nhau tùy ngày
	hour		end_hour[7];
	string		room;
	void		operator=(course &c)
	{
		id = c.id;
		name = c.name;
		class_name = c.class_name;
		lecturer = c.lecturer;
		start_date = c.start_date;
		end_date = c.end_date;

		n_course_date = c.n_course_date;
		if (course_date != NULL)
			delete[]course_date;
		if (c.n_course_date == 0)
			course_date = NULL;
		else
		{
			course_date = new dayhour[c.n_course_date];
			for (int i = 0; i < c.n_course_date; i++)
			{
				course_date[i] = c.course_date[i];
			}
		}

		n_student = c.n_student;
		for (int i = 0; i < 7; i++)
		{
			dow[i] = c.dow[i];
			start_hour[i] = c.start_hour[i];
			end_hour[i] = c.end_hour[i];
		}
		room = c.room;
	}
	template <class COURSE> bool operator == (COURSE &c)
	{
		return (id == c.id && class_name == c.class_name);
	}
	template <class COURSE> bool operator !=(COURSE &c)
	{
		return (id != c.id || class_name != c.class_name);
	}
};

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void	textColor(int x);
template <class T> void		push_back(T* &arr, int &n, T &item);
template <class T> void		moreSize(T* &arr, int &n);
template <class T> void		moreNSize(T* &arr, int &n, int size_to_add_more);
template <class t>	void	pointColor(t point);
template <class t>	void	getNum(t &n);
template <class T>	void	sortAscending(T* &s, int n);
template <class T>	int		merge2Arrays(T &arr1, int n1, T &arr2, int n2, T & arr3);
template <class T>	int		removeDuplicates(T* &arr, int n);
template <class T>	void	showStudentList(T* &s, int n, bool is_showing_pass);

int currentlyRunningCourse(courseID *&all_course, int n_c, int &return_course_date_j, dayhour &return_course_date);
bool	yesNoAns();
bool	checkValidDate(date d);
bool	dateInputChecking(int dd, int mm, int yy);
void	studentAccountGenerator(student &s);
int		askCommand(int lastCommand);
int		askCommand(int firstCommand, int lastCommand);
int		askManyCommands(int first_command, int last_command, int* &selected_command);
string	intToMonth(int n);
int		monthToString(string s);
int		monthToSemesterInt(int mm);
string	monthToSemesterString(int mm);
int		monthToAcademicYear(int mm, int start_year);
int		semesterToAcademicYear(int sem, int start_year);
int		getCurrentSemester();
int		getCurrentAcademicYear();
string	dateToPass(date d);
int		changeStartYearOfACourseToMatchWithNewAcademicYear(int old_month, int new_start_year);
void	courseDateGenerator(course &c);		//Hàm tạo ngày tháng đi học cho course_date
size_t	timeSince1970(int dd, int mm, int yy);	//Tính số giây từ 0:00AM 1st, Jan, 1970
void	strLwr(string &s);
void	strUpr(string &s);
void	studentAccountGenerator(student &s);
bool	lecturerAcountGenerator(lecturer &l, const course &c, int start_yr, int end_yr, int term_no);
bool	loginStudentAccount(string &user_name, student &s);
template <class COURSE> bool askingCourseID(COURSE &c);
template <class COURSE> bool askingCourseIDOfALecturer(COURSE &c, string lecturer_acc);
int		checkDateStrDDMMYYYY(date &d, char delim);
string nameProcesser_StringOutput(string full_name);
bool viewLecturerGeneralSchedule(bool is_lecturer, term& this_term);

// folder\file path
void	classFolderPath(string class_name, string &path);
void	studentTXTPath(string class_name, int id, string &path);
void	classTXTPath(string class_name, string &path);
void	courseIDTXTPath(string class_name, string course_id, string &path);

		// CSV
int		weekToInt(char* token);
bool	readDOWInSemesterTXT(bool dow[7], const char* str);
hour	strToHour(char* token);
bool	readHourInSemesterCSV(bool dow[7], hour hours[7], const char* str);
bool	exportScoreboardCSV(student* s, int n, const course &c);
bool	exportAttendanceCSV(student* s, int n, course c);
bool	importSemesterCSV(course* &courses, int &n_course, string path, int start_yr, int end_yr, int term_no);
int		checkStudentCSV(student* &student_list, int &n, string path, string class_name, studentID *& existed_student, int &n_existed);

		// Class.txt
bool	readClassTXT(string* &class_name, int &n);
void	addClass(string class_name);
bool	removeClass(string class_name);

		// File [CLass_name].txt
void	exportStudentList(student* student_list, int n, string class_name);
bool	readStudentList(student* &student_list, int &n, string class_name);
void	addNewStudent(student s);
bool	isInStudentList(int id, string class_name);
void	removeStudentFromStudentList(int id, string class_name);

		// s[MSSV].txt
bool	saveStudent(student s);
template <class COURSE> void removeACourseInStudentIDTXT(const student &s, academic_year* &student_course, int n_course, const COURSE &c);
bool	saveStudent(const student &s, academic_year* &student_course, int n_course);
bool	loadStudentData(student &s, academic_year* &student_course, int &n_course, string class_name, int id);
void	exportStudentTXT(student* student_list, int n, string class_name);
student	readStudentData(int id, string class_name);
bool	readStudentData(int id, string class_name, student &s);
bool	isStudentExist(int id);
bool	isStudentExist(int id, string &existed_class);
bool	findStudentByID(int id, student &s);
bool	loginStudentAccount(string &user_name, student &s);
void	removeStudentTXT(int id, string class_name);
void	moveStudentTXT(student &s, string new_class);
void	saveOneNewCourseToStudentTXT(const course &c);

		// [Course].txt
bool	readCourseIDTXT(string course_id, course &course_read, student* &s, int &n, string class_name);
void	saveCourseIDTXT(course &course_save, student* &s, int n, string class_name);
void	removeStudentFromCourseIDTXT(course &course_save, student* &s, int n, string class_name, int id_delete);
void	removeStudentsFromCourseIDTXT(course &course_save, student* &s, int n, string class_name, int* id_delete, int n_delete);
void	saveAllStudentCourse(student* &s, int n, const course &c, int start_yr, int end_yr, int term_no);
void	removeAStudentNameInCourseTXT(const student &s, const string &course_id);
void	removeAStudentNameInAllCourseIDTXT(const student &s, academic_year* &c, int n_c);
template <class COURSE> void	saveAllCourseToAllStudent(student *&s, int n_student, COURSE *&c, int n_course, int start_yr, int end_yr, int term_no);
bool	courseInformationInput(course &c);
bool	importStudentToCourse(course &c, student* &s, int &n);
void	readCourseTXT_OnlyCourseInfo(string courseID, string class_name, course &c);
bool	isCourseExistInClass_Ver2(string class_name, string course_id);
void	removeCourseFromSemesterTXT(string class_name, string course_id);
void	removeCourseFromLecturerTXT(string class_name, string course_id);
void	removeCourseFromStudentTXT(string class_name, string course_id);

		// semester.txt
bool	readSemesterTXT(academic_year* &year, int &n);
void	saveSemesterTXT(academic_year* &year, int n);
template <class COURSE = courseID> int	isCourseInSemesterTXTExist(COURSE &c);
void	readSemesterCourses(ifstream &fin, academic_year* &year, int &n);
void	saveSemesterCourses(ofstream &fout, academic_year* &year, int n);
template <class COURSE> void	removeACourseInSemesterCourses(ofstream &fout, academic_year* year, int n, const COURSE &c_delete);
template <class COURSE> bool	addCourseToStructAcademicYear(const COURSE &c, academic_year* &years, int &n_year, int start_yr, int end_yr, int term_no);
bool	addCourseToSemesterTXT(const course &c, int start_yr, int end_yr, int term_no);
int		readCurrentSemesterOfAClass(courseID* &current, int &n_course, string class_name);
bool	isCourseExistInSemesterTXT(string course_id, string class_id);
void	saveOneNewCourseToSemesterTXT(const course &c);

		// lecturer.txt
bool	readLecturerTXT(lecturer* &lecturers, int &n);
void	saveLecturerTXT(lecturer* &lecturers, int n);
int		addCourseToLecturerTXT(lecturer &l, const course &c, int start_yr, int end_yr, int term_no);
int		isLecturerExist(lecturer &l);
bool	isCourseExistInLecturerTXT(string class_name, string course_id);
bool	isCourseExistInLecturerTXT_(string class_name, string course_id, string lecturer_acc);
void	printLecturerInfo(const lecturer &l);
void	viewLecturerList();
void	addOneNewLecturer();
void	updateOneLecturer();
void	removeOneLecturer();
void	saveOneNewCourseToLecturerTXT(const course &c);
		
		// Mooldle's function
int		function01(string &);
void	function06();
void	function07();
void	function08();
void	function09();
void	function10();
void	function11();
void	function12();
void	function13();
void	function14Old();
void	function14();
void	function15();
void	function16();
void	function17();//Xóa 1 course nào đó
void	function18();
void	function19();
void	function20();
void	function21();
void	function24();
void	function25();
void	function27();
void	function23();
void	function22_26();
void	function28(string);
void	function30(string);
void	function31(string lecturer_account);
void	function32(string user_name);
void	function33(string);
void	function34(string);
void	function35(string);
void	function36(string user_name);
void	function37(string user_name);
void	function38(string temp3);

void	changePassword(student &s);
void	changeName(student &s);
void	changeBirthday(student &s);
void	changeBirthday(student &s);
void	changeID(student &s);
void	changeGender(student &s);
void	viewProfileInfo(const string& account);

void	clrscr();
void	gotoXY(short column, short line);
void	gotoxy(short x, short y);
void	ToMau(short x, short y, char *a, int color);
void	ToMau(int x, int y, string a, int color);
void	XoaManHinh();
void	loginMenu();
void	adminScoreboardMenu(string user_name);
void	adminClassMenu(string user_name);
void	adminMenu(string user_name);
void	studentMenu(string user_name);
void	lecturerMenu(string user_name);
void	adminCourseMenu(string user_name);
void	adminAttendanceMenu(string user_name);
bool	importScoreBoard(student*& s_list, int& n_s, string path);

int		importDate(ifstream &fin, date &d, char delim);
string	readAdminPassword();
void	changeAdminPassword();

void	exitOurProgram();
/*
		   " 0000000000 0000   0000        000         000    0000 000  0000 0000    0000    000000    00000     0000   00    00
		<< "     00      00     00        00 00        0000    00   00  00     00    00    000    000   000       00    00    00
		<< "     00      00     00       00   00       00 00   00   00 00        00 00    000      000  000       00    00    00
		<< "     00      000000000      000000000      00  00  00   0000          000    000        000 000       00    00    00
		<< "     00      00     00     00       00     00   00 00   00 000        000     000      000  000       00    00    00
		<< "     00      00     00    00         00    00    0000   00   000      000      000    000    000     00
		<< "    0000    0000   0000 0000         0000 0000    000  000    000    00000       000000        000000       00    00

*/
#endif // !_MOODLE_H_
