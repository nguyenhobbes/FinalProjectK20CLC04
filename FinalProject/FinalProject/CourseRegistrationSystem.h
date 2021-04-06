#ifndef _CourseRegistrationSystem_
#define _CourseRegistrationSystem_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

// <--------- Setup --------->

void loadAccountData(ifstream& fi, Account*& account); // Load data of user's account from csv file
void logIn(Account* account, string& accountCur, string& type); // Log in to the system.
void viewProfile(Student* studentCur); // View profile info of account.
void changePassword(ofstream& fo, Account* account, string accountCur); // Change password of account.
void logOut(string& accountCur); // Log out of the system.
void deleteAccountData(Account*& account); // Release memory
void deleteStudentData(Student*& student); // Release memory
void deleteClassData(Class*& c);

// <--------- Setup --------->

// <--------- Staff --------->

// At the beginning of a school year, 3 semesters.
void createSchoolYear(string& schoolYear); // Create a school year. Ex: 2020-2021.
void create1stClass(string& cl); // Create class for 1st year students. Ex: 20APCS1, 20CLC1, 20VP1.
void add1stStudentsTo1stClasses(ifstream& fi, string schoolYear, string cl, Class*& c); // Add all 1st year students to 1st classes.
void saveClassData(ofstream& fo, Class* c);
void loadClassData(ifstream& fi, Class*& c); // Load data of classes from csv file.

// At the beginning of a semester.
void createSemester(string& semester); // Create semester 1, 2, or 3, school year, start date, end date. The created semester will be the default for below action.
void createRegSession(); // Create session for course registration.
void addCourseToSemester(string semester); // Add course to semester with: id, name, teacher name, credits, max students (default 50), day of the week, and the session  (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)). A course in 2 session.
void viewListCourses(); // View list of courses.
void updateCourseInfo(); // Update course infomation.
void deleteCourse(); // Delete a course.

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
void enrollCourse(); // Enroll a course. If 2 sessions are conflicted with existing enrolled course session, can't enroll. Max course: 5.
void viewListEnrolledCourses(); // View list of enrolled courses.
void removeEnrolledCourse(); // Remove a course from the enrolled list

// When a course registration session is close.
void viewListCoursesInSemester(); // View list of courses that student will study in this semester.

// When the scoreboard has been published
void viewScoreboard(); // View his/her scoreboard.

// <--------- Student --------->

#endif