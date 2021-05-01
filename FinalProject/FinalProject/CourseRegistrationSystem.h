#ifndef _CourseRegistrationSystem_
#define _CourseRegistrationSystem_

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <ctime>
using namespace std;

struct Account {
	string username, password, type;
	Account* aNext;
};

struct Score {
	string no, studentID, fullname;
	float total, final, midterm, other;
	Score* score_next;
};

struct Student {
	string no, studentID, firstname, lastname, gender, dob, socialID;
	Student* sNext;
};

struct Class {
	string name;
	Student* stu;
	Class* cNext;
};

struct Session {
	string s;
	Session* sNext;
};

struct Course {
	string id, name, teacher, credits;
	int max, day, enrolled;
	Session* session;
	Student* stu;
	Course* cNext;
	Score* score;
};

struct schYear {
	Class* c;
	string name;
	int num;
	schYear* sYNext;
};

struct Semester {
	string name, schoolYear, start, end, regStart, regEnd;
	int num;
	Course* course;
	Semester* sNext;
};

struct Data {
	string id;
	int count;
	Course* course;
	Data* dNext;
};

struct Setting {
	string ys, ye, s1, e1, s2, e2, s3, e3;
};

// <--------- Setup --------->

void loadSettings(ifstream& fi, Setting*& sett);
void loadAccountData(ifstream& fi, Account*& account); // Load data of user's account from csv file
void saveAccountData(ofstream& fo, Account* account);
void logIn(Account* account, string& accountCur, string& type); // Log in to the system.
void viewProfile(schYear* sY, string accountCur, string type); // View profile info of account.
void changePassword(ofstream& fo, Account* account, string accountCur); // Change password of account.
void logOut(string& accountCur); // Log out of the system.
void saveClassData(ofstream& fo, schYear* sY); // Save data of classes
void loadClassData(ifstream& fi, schYear*& sY); // Load data of classes from csv file.
void saveSemesterData(ofstream& fo, Semester* semester, Semester* sSel); // Save data of semester
void loadSemesterData(ifstream& fi, Semester*& semester, Semester*& sSel); // Load data of semester from csv file
void saveStudentCourseData(ofstream& fo, Data* data);
void loadStudentCourseData(ifstream& fi, Data*& data);
void deleteStudentCourseData(Data*& data);
void deleteSemesterData(Semester*& semester, Semester*& sSel); // Release memory
void deleteAccountData(Account*& account); // Release memory
void deleteStudentData(Student*& student); // Release memory
void deleteClassData(schYear*& sY); // Release memory
void getStudentData(schYear* sY, Student*& studentCur, Data* data, Data*& dSel, string accountCur);

// <--------- Setup --------->

// <--------- Staff --------->

// At the beginning of a school year, 3 semesters.
void createSchoolYear(schYear*& sY); // Create a school year. Ex: 2020-2021.
void create1stClass(schYear* sY); // Create class for 1st year students. Ex: 20APCS1, 20CLC1, 20VP1.
void add1stStudentsTo1stClasses(ifstream& fi, schYear* sY, Account* account, Data*& data); // Add all 1st year students to 1st classes.

// At the beginning of a semester.
void createSemester(Semester*& semester, Semester*& sSel); // Create semester 1, 2, or 3, school year, start date, end date. The created semester will be the default for below action.
void createRegSession(Semester* semester); // Create session for course registration.
void addCourseFromFile(Course*& course);
void addCourseFromKeyboard(Course*& course);
void addCourseToSemester(Semester*& semester); // Add course to semester with: id, name, teacher name, credits, max students (default 50), day of the week, and the session  (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)). A course in 2 session.
void viewListCourses(Course* course); // View list of courses.
void updateCourseInfo(Course*& course); // Update course infomation.
void deleteCourse(Course*& course); // Delete a course.
void changeSemester(Semester* semester, Semester*& sSel);

// At any time:
void viewListClasses(schYear* sY); // View list of classes.
void viewListStudentInClass(schYear* sY); // View list of students in class. Ex: 20CLC4.

// view list course.
void viewListStudentInCourse(Course* course); // View list of students in course.

//At the end of a semester
void exportListStudent(ofstream& fo, Course* course); // Export list of students in a course to a CSV file.
void importScoreboard(ifstream& fi, Course* course, Score*& score); // Import the scoreboard of a course. Including: No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark
void viewCourseScoreboard(Course* course); // View the scoreboard of a course
void updateStudentResult(Course* course); // Update a student result.
void viewClassScoreboard(schYear* sY, Data* data, Course* course); // View the scoreboard of a class. Including final marks of all courses, GPA , and the overall GPA.

// <--------- Staff --------->

// <--------- Student --------->

// When a course registration session is active.
// Log in.
void enrollCourse(Data* data, Course* course, Student* studentCur); // Enroll a course. If 2 sessions are conflicted with existing enrolled course session, can't enroll. Max course: 5.
void viewListEnrolledCourses(Data* data); // View list of enrolled courses.
void viewListStudentCourses(Course* course);
void removeEnrolledCourse(Data* data, Course* course); // Remove a course from the enrolled list

// When a course registration session is close.
void viewListCoursesInSemester(Data* data); // View list of courses that student will study in this semester.

// When the scoreboard has been published
void viewScoreboard(Course* course); // View his/her scoreboard.

// <--------- Student --------->

// <--------- Function --------->

void splitDate(string s, int& d, int& m, int& y);
bool checkRegTime(string s1, string s2, tm* rt);
bool checkBeginTime(string s1, string s2, tm* rt);
bool checkEndTime(string s, tm* rt);

// <--------- Function --------->

// <--------- Screen ----------->
void gotoxy(int x, int y);
void loadingScreen();
void changeColor(int i);

// <--------- Screen ----------->

#endif