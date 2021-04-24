#include "CourseRegistrationSystem.h"

int main() {
	Account* account = 0;
	Class* c = 0;
	Semester* semester = 0;
	Data* data = 0;
	string accountCur = "20127406", type = "Student";
	Student* studentCur = 0;
	Score* score = 0;
	ifstream fi;
	ofstream fo;
	fi.open("Accounts.csv");
	if (fi.is_open()) {
		loadAccountData(fi, account);
		fi.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	fi.open("Classes.csv");
	if (fi.is_open()) {
		loadClassData(fi, c);
		fi.close();
	}
	fi.open("Semester.csv");
	if (fi.is_open()) {
		loadSemesterData(fi, semester);
		fi.close();
	}
	fi.open("StudentData.csv");
	if (fi.is_open()) {
		loadStudentCourseData(fi, data);
		fi.close();
	}
	menuLogin(account, accountCur, type);
	/* ------------ Menu
	int choose = 0;
	do {
		menuLogin;
		cin >> choose;
		switch (choose) {
		case 1:
			logIn(account, accountCur, type);
			if (type == "Student") getStudentData(c, studentCur, accountCur);
			break;
		case 0:
			break;
		}
	} while (choose != 0);
	*/
	/*  ----------- Change Password
	fo.open("Accounts.csv");
	if (fo.is_open()) {
		changePassword(fo, account, accountCur);
		fo.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	*/
	/* --------------- Create class and add student data to class
	string schoolYear = "", cl = "";
	createSchoolYear(schoolYear);
	create1stClass(cl);
	cout << "Input csv file name. Ex: student.csv\n";
	string fname = "";
	cin >> fname;
	fi.open(fname);
	if (fi.is_open()) {
		add1stStudentsTo1stClasses(fi, schoolYear, cl, c, data);
		fi.close();
	}
	else cout << "Can't open file Classes.csv.\n";
	fo.open("Accounts.csv");
	if (fo.is_open()) {
		saveAccountData(fo, c);
		fo.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
		fo.close();
	}
	else cout << "Can't open file Classes.csv.\n";
	*/
	/* ----------- Create semester
	createSemester(semester);
	int choose = 0;
	do {
		cout << "1. Create a course registration session.\n";
		cout << "2. Add a course to the semester.\n";
		cout << "3. View list of courses.\n";
		cout << "4. Update course information.\n";
		cout << "5. Delete a course.\n";
		cout << "0. Exit.\n";
		cout << "Enter selection:\n";
		cin >> choose;
		system("cls");
		switch (choose) {
		case 1:
			createRegSession(semester);
			break;
		case 2:
			addCourseToSemester(semester);
			break;
		case 3:
			viewListCourses(semester->course);
			break;
		case 4:
			updateCourseInfo(semester->course);
			break;
		case 5:
			deleteCourse(semester->course);
			break;
		case 0:
			break;
		default:
			cout << "Invalid selection.\n";
			choose = -1;
			break;
		}
	} while (choose != 0);
	fo.open("Semester.csv");
	if (fo.is_open()) {
		saveSemesterData(fo, semester);
		fo.close();
	}
	else cout << "Can't open file Semester.csv.\n";
	*/
	/* ------------- Enroll course
	Data* dSelect = data;
	while (dSelect && dSelect->id != accountCur) dSelect = dSelect->dNext;
	int choose;
	do {
		cout << "1. Enroll a course.\n";
		cout << "2. View list of enrolled course.\n";
		cout << "3. Remove a course from enrolled list.\n";
		cout << "0. Exit.\n";
		cout << "Select the information you want to update:\n";
		cin >> choose;
		system("cls");
		switch (choose) {
		case 1:
			if (!semester) {
				cout << "There is an error!\n";
				break;
			}
			enrollCourse(dSelect, semester->course, studentCur);
			fo.open("Classes.csv");
			if (fo.is_open()) {
				saveClassData(fo, c);
				fo.close();
			}
			else cout << "Can't save the course data of student";
			break;
		case 2:
			viewListEnrolledCourses(dSelect);
			break;
		case 3:
			if (!semester) {
					cout << "There is an error!\n";
					break;
			}
			removeEnrolledCourse(dSelect, semester->course);
			break;
		case 0:
			break;
		default:
			cout << "Invalid selection!\n";
			break;
		}
	} while (choose != 0);
	*/
	/*
	getStudentData(c, studentCur, accountCur);
	Data* dSelect = data;
	while (dSelect && dSelect->id != accountCur) dSelect = dSelect->dNext;
	enrollCourse(dSelect, semester->course, studentCur);
	fo.open("Semester.csv");
	if (fo.is_open()) {
		saveSemesterData(fo, semester);
		fo.close();
	}
	else cout << "Can't save the semester data\n";
	fo.open("StudentData.csv");
	if (fo.is_open()) {
		saveStudentCourseData(fo, data);
		fo.close();
	}
	else cout << "Can't save the student data\n";

	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
		fo.close();
	}
	else cout << "Can't save the course data of student";
	studentCur = 0;
	*/
	/*
	int choose;
	do {
	cout << "1. Export list of students in a course to a CSV file.\n";
	cout << "2. Import the scoreboard of a course.\n";
	cout << "3. View the scoreboard of a course.\n";
	cout << "4. Update a student result.\n";
	cout << "5. View the scoreboard of a class.\n";
	cout << "0. Exit.\n";
	cout << "Enter selection:\n";
	cin >> choose;
	system("cls");
	switch (choose) {
	case 1:
		exportListStudent(fo, semester->course);
		break;
	case 2:
		importScoreboard(fi, semester->course, score);
		break;
	case 3:
		viewCourseScoreboard(semester->course);
		break;
	case 4:
		updateStudentResult(semester->course);
		break;
	case 5:
		viewClassScoreboard();
		break;
	case 0:
		break;
	default:
		cout << "Invalid selection.\n";
		choose = -1;
		break;
	}
	} while (choose != 0);
	*/
	deleteSemesterData(semester);
	deleteAccountData(account);
	deleteStudentCourseData(data);
	deleteClassData(c);

	return 0;
}