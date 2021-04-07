#include "CourseRegistrationSystem.h"

// <--------- Setup --------->

void loadAccountData(ifstream& fi, Account*& account) {
	Account* aCur = 0;
	while (fi.good()) {
		Account* tmp = new Account;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, tmp->username, ',');
		getline(s, tmp->password, ',');
		getline(s, tmp->type);
		tmp->aNext = 0;
		if (aCur == 0) {
			account = tmp;
			aCur = account;
		}
		else {
			aCur->aNext = tmp;
			aCur = tmp;
		}
	}
}

void logIn(Account* account, string& accountCur, string& type) {
	Account* tmp;
	string username, password;
	do {
		tmp = account;
		cout << "Input Username:\n";
		getline(cin, username);
		cout << "Input password:\n";
		getline(cin, password);
		while (tmp) {
			if (tmp->username == username) {
				if (tmp->password == password) {
					accountCur = username;
					type = tmp->type;
					system("cls");
					cout << "Logged in!\n";
					return;
				}
				break;
			}
			tmp = tmp->aNext;
		}
		system("cls");
		cout << "Invalid login, please try again.\n";
	} while (tmp == 0 || tmp->password != password);
}

void viewProfile(Student* student) {

}

void changePassword(ofstream& fo, Account* account, string accountCur) {
	Account* tmp = account;
	if (account->username != accountCur)
		account = account->aNext;
	do {
		string password;
		cout << "Input current password:\n";
		cin >> password;
		if (account->password == password)
		{
			cout << "Input new password:\n";
			cin >> password;
			string newpassword;
			cout << "Reinput new password:\n";
			cin >> newpassword;
			if (password == newpassword) {
				account->password = newpassword;
				system("cls");
				cout << "Password's changed!\n";
				break;
			}
			else {
				system("cls");
				cout << "2 passwords are not match.\n";
			}
		}
		else {
			system("cls");
			cout << "Wrong password!\n";
		}
	} while (1);
	while (tmp) {
		fo << tmp->username << ',' << tmp->password;
		if (tmp->aNext) fo << endl;
		tmp = tmp->aNext;
	}

}

void logOut(string& accountCur) {
	accountCur = "";
}

void saveAccountData(ofstream& fo, Account* account) {
	while (account) {
		fo << account->username << ',' << account->password << ',' << account->type << endl;
		account = account->aNext;
	}
}

void saveClassData(ofstream& fo, Class* c) {
	while (c) {
		fo << c->schoolYear << ',' << c->name;
		Student* sTmp = c->stu;
		while (sTmp) {
			fo << ',' << sTmp->no << ',' << sTmp->studentID << ',' << sTmp->firstname << ',' << sTmp->lastname << ',' << sTmp->gender << ',' << sTmp->dob << ',' << sTmp->socialID;
			sTmp = sTmp->sNext;
		}
		fo << endl;
		c = c->cNext;
	}
}

void loadClassData(ifstream& fi, Class*& c) {
	Class* cCur = 0;
	while (fi.good()) {
		Class* tmp = new Class;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, tmp->schoolYear, ',');
		getline(s, tmp->name, ',');
		Student* stu = 0;
		while (s.good()) {
			Student* sTmp = new Student;
			getline(s, sTmp->no, ',');
			getline(s, sTmp->studentID, ',');
			getline(s, sTmp->firstname, ',');
			getline(s, sTmp->lastname, ',');
			getline(s, sTmp->gender, ',');
			getline(s, sTmp->dob, ',');
			getline(s, sTmp->socialID, ',');
			sTmp->sNext = 0;
			if (!stu) tmp->stu = sTmp;
			else stu->sNext = sTmp;
			stu = sTmp;
		}
		tmp->cNext = 0;
		if (!cCur) c = tmp;
		else cCur->cNext = tmp;
		cCur = tmp;
	}
}

void deleteAccountData(Account*& account) {
	while (account)
	{
		Account* tmp = account;
		account = account->aNext;
		delete tmp;
	}
}

void deleteStudentData(Student*& student) {
	while (student)
	{
		Student* tmp = student;
		student = student->sNext;
		delete tmp;
	}
}

void deleteClassData(Class*& c) {
	while (c)
	{
		Class* tmp = c;
		c = c->cNext;
		deleteStudentData(tmp->stu);
		delete tmp;
	}
}


// <--------- Setup --------->

// <--------- Staff --------->

// At the beginning of a school year, 3 semesters.
void createSchoolYear(string& schoolYear) {
	cout << "Input a school year:\n";
	cin >> schoolYear;
}

void create1stClass(string& cl) {
	cout << "Input name of class:\n";
	cin >> cl;
}

void add1stStudentsTo1stClasses(ifstream& fi, string schoolYear, string cl, Class*& c, Account* account) {
	Class* cCur = c;
	Class* cTmp = new Class;
	cTmp->cNext = 0;
	cTmp->schoolYear = schoolYear;
	cTmp->name = cl;
	Student* sCur = 0;
	while (account->aNext) account = account->aNext;
	while (fi.good()) {
		Student* sTmp = new Student;
		sTmp->sNext = 0;
		string s;
		getline(fi, s);
		stringstream ss(s);
		getline(ss, sTmp->no, ',');
		getline(ss, sTmp->studentID, ',');
		getline(ss, sTmp->firstname, ',');
		getline(ss, sTmp->lastname, ',');
		getline(ss, sTmp->gender, ',');
		getline(ss, sTmp->dob, ',');
		getline(ss, sTmp->socialID, ',');
		Account* aTmp = new Account;
		aTmp->username = sTmp->studentID;
		aTmp->password = "1";
		aTmp->type = "Student";
		account->aNext = aTmp;
		account = aTmp;
		if (!sCur) cTmp->stu = sTmp;
		else sCur->sNext = sTmp;
		sCur = sTmp;
	}
	while (cCur->cNext) cCur = cCur->cNext;
	if (cCur == c) c = cTmp;
	else cCur->cNext = cTmp;
}

// At the beginning of a semester.
void createSemester(string& semester) {

}

void createRegSession() {

}

void addCourseToSemester(string semester) {

}

void viewListCourses() {

}

void updateCourseInfo() {

}

void deleteCourse() {

}

// At any time:
void viewListClasses() {

}
void viewListStudentInClass() {

}

// view list course.
void viewListStudentInCourse() {

}

//At the end of a semester
void exportListStudent() {

}

void importScoreboard() {

}

void viewCourseScoreboard() {

}

void updateStudentResult() {

}

void viewClassScoreboard() {

}

// <--------- Staff --------->

// <--------- Student --------->

// When a course registration session is active.
void enrollCourse() {

}

void viewListEnrolledCourses() {

}

void removeEnrolledCourse() {

}

// When a course registration session is close.
void viewListCoursesInSemester() {

}

// When the scoreboard has been published
void viewScoreboard() {

}

// <--------- Student --------->