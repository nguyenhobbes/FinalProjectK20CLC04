#ifndef _CourseRegistrationSystem_
#define _CourseRegistrationSystem_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Account {
	string username, password, type;
	Account* aNext;
};

struct Student {
	string no, studentID, firstname, lastname, gender, dob, socialID;
	Student* sNext;
};

struct Class {
	string schoolYear, name;
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
	Course* cNext;
};

struct Semester {
	string name, schoolYear, start, end, regStart, regEnd;
	Course* course;
};

struct Data {
	string id;
	Course* course;
	Data* dNext;
};

// <--------- Setup --------->

void loadAccountData(ifstream& fi, Account*& account); // Load data of user's account from csv file
void logIn(Account* account, string& accountCur, string& type); // Log in to the system.
void viewProfile(Class* c, string accountCur, string type); // View profile info of account.
void changePassword(ofstream& fo, Account* account, string accountCur); // Change password of account.
void logOut(string& accountCur); // Log out of the system.
void saveClassData(ofstream& fo, Class* c); // Save data of classes
void loadClassData(ifstream& fi, Class*& c); // Load data of classes from csv file.
void saveSemesterData(ofstream& fo, Semester* semester); // Save data of semester
void loadSemesterData(ifstream& fi, Semester*& semester); // Load data of semester from csv file
void saveStudentCourseData(ofstream& fo, Data* data);
void loadStudentCourseData(ifstream& fi, Data*& data);
void deleteStudentCourseData(Data*& data);
void deleteSemesterData(Semester*& semester); // Release memory
void deleteAccountData(Account*& account); // Release memory
void deleteStudentData(Student*& student); // Release memory
void deleteClassData(Class*& c); // Release memory

void menuLogin(); //Menu Login

// <--------- Setup --------->

// <--------- Staff --------->

// At the beginning of a school year, 3 semesters.
void createSchoolYear(string& schoolYear); // Create a school year. Ex: 2020-2021.
void create1stClass(string& cl); // Create class for 1st year students. Ex: 20APCS1, 20CLC1, 20VP1.
void add1stStudentsTo1stClasses(ifstream& fi, string schoolYear, string cl, Class*& c, Account* account, Data*& data); // Add all 1st year students to 1st classes.

// At the beginning of a semester.
void createSemester(Semester*& semester); // Create semester 1, 2, or 3, school year, start date, end date. The created semester will be the default for below action.
void createRegSession(Semester*& semester); // Create session for course registration.
void addCourseFromFile(Course*& course);
void addCourseFromKeyboard(Course*& course);
void addCourseToSemester(Semester*& semester); // Add course to semester with: id, name, teacher name, credits, max students (default 50), day of the week, and the session  (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)). A course in 2 session.
void viewListCourses(Course* course); // View list of courses.
void updateCourseInfo(Course*& course); // Update course infomation.
void deleteCourse(Course*& course); // Delete a course.

// At any time:
void viewListClasses(); // View list of classes.
void viewListStudentInClass(); // View list of students in class. Ex: 20CLC4.

// view list course.
void viewListStudentInCourse(); // View list of students in course.

//At the end of a semester
void exportListStudent(); // Export list of students in a course to a CSV file.
void importScoreboard(); // Import the scoreboard of a course. Including: No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark
void viewCourseScoreboard(); // View the scoreboard of a course
void updateStudentResult(); // Update a student result.
void viewClassScoreboard(); // View the scoreboard of a class. Including final marks of all courses, GPA , and the overall GPA.

// <--------- Staff --------->

// <--------- Student --------->

// When a course registration session is active.
// Log in.
void enrollCourse(Data* data, Course* course); // Enroll a course. If 2 sessions are conflicted with existing enrolled course session, can't enroll. Max course: 5.
void viewListEnrolledCourses(Data* data); // View list of enrolled courses.
void removeEnrolledCourse(Data* data); // Remove a course from the enrolled list

// When a course registration session is close.
void viewListCoursesInSemester(Data* data); // View list of courses that student will study in this semester.

// When the scoreboard has been published
void viewScoreboard(); // View his/her scoreboard.

// <--------- Student --------->

#endif