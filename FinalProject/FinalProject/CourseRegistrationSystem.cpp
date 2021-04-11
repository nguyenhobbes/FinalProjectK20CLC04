#include "CourseRegistrationSystem.h"

// <--------- Setup --------->

void loadAccountData(ifstream& fi, Account*& account) {
	Account* aCur = 0;
	while (fi.good()) {
		Account* tmp = new Account;
		tmp->aNext = 0;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, tmp->username, ',');
		getline(s, tmp->password, ',');
		getline(s, tmp->type);
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
		if (c->cNext) fo << endl;
		c = c->cNext;
	}
}

void loadClassData(ifstream& fi, Class*& c) {
	Class* cCur = 0;
	while (fi.good()) {
		Class* tmp = new Class;
		tmp->cNext = 0;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, tmp->schoolYear, ',');
		getline(s, tmp->name, ',');
		Student* stu = 0;
		while (s.good()) {
			Student* sTmp = new Student;
			sTmp->sNext = 0;
			getline(s, sTmp->no, ',');
			getline(s, sTmp->studentID, ',');
			getline(s, sTmp->firstname, ',');
			getline(s, sTmp->lastname, ',');
			getline(s, sTmp->gender, ',');
			getline(s, sTmp->dob, ',');
			getline(s, sTmp->socialID, ',');
			if (!stu) tmp->stu = sTmp;
			else stu->sNext = sTmp;
			stu = sTmp;
		}
		if (!cCur) c = tmp;
		else cCur->cNext = tmp;
		cCur = tmp;
	}
}

void saveSemesterData(ofstream& fo, Semester* semester) {
	if (!semester) return;
	fo << semester->name << ',' << semester->schoolYear << ',' << semester->start << ',' << semester->end << ',' << semester->regStart << ',' << semester->regEnd;
	Course* cCur = semester->course;
	while (cCur) {
		fo << endl << cCur->id << ',' << cCur->name << ',' << cCur->teacher << ',' << cCur->credits << ',' << cCur->max << ',' << cCur->day;
		Session* sCur = cCur->session;
		while (sCur) {
			fo << ',' << sCur->s;
			sCur = sCur->sNext;
		}
		fo << ',' << cCur->enrolled;
		cCur = cCur->cNext;
	}
}

void loadSemesterData(ifstream& fi, Semester*& semester) {
	string s;
	getline(fi, s);
	stringstream ss(s);
	semester = new Semester;
	semester->course = 0;
	getline(ss, semester->name, ',');
	getline(ss, semester->schoolYear, ',');
	getline(ss, semester->start, ',');
	getline(ss, semester->end, ',');
	getline(ss, semester->regStart, ',');
	getline(ss, semester->regEnd);
	Course* cCur = semester->course;
	while (fi.good()) {
		string tmp;
		char c;
		getline(fi, tmp);
		stringstream sss(tmp);
		Course* cTmp = new Course;
		getline(sss, cTmp->id, ',');
		getline(sss, cTmp->name, ',');
		getline(sss, cTmp->teacher, ',');
		getline(sss, cTmp->credits, ',');
		sss >> cTmp->max;
		sss >> c;
		sss >> cTmp->day;
		sss >> c;
		cTmp->session = 0;
		Session* sCur = cTmp->session;
		for (int i=0; i<cTmp->day; i++) {
			Session* sTmp = new Session;
			sTmp->sNext = 0;
			getline(sss, sTmp->s, ',');
			if (sCur) sCur->sNext = sTmp;
			else cTmp->session = sTmp;
			sCur = sTmp;
		}
		sss >> cTmp->enrolled;
		if (cCur) cCur->cNext = cTmp;
		else semester->course = cTmp;
		cCur = cTmp;
		cTmp->cNext = 0;
	}
}

void deleteSemesterData(Semester*& semester) {
	if (!semester) return;
	while (semester->course) {
		Course* cTmp = semester->course;
		semester->course = cTmp->cNext;
		while (cTmp->session) {
			Session* sTmp = cTmp->session;
			cTmp->session = sTmp->sNext;
			delete sTmp;
		}
		delete cTmp;
	}
	delete semester;
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
		aTmp->aNext = 0;
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
void createSemester(Semester*& semester) {
	if (semester) deleteSemesterData(semester);
	semester = new Semester;
	semester->course = 0;
	cout << "Input semester:\n";
	cin >> semester->name;
	cout << "Input school year: (Format: yyyy-yyyy)\n";
	cin >> semester->schoolYear;
	cout << "Input start date: (Format: dd/mm/yyyy)\n";
	cin >> semester->start;
	cout << "Input end date: (Format: dd/mm/yyyy)\n";
	cin >> semester->end;
}

void createRegSession(Semester*& semester) {
	cout << "Input registration session start date: (Format: dd/mm/yyyy)\n";
	cin >> semester->regStart;
	cout << "Input registration session end date: (Format: dd/mm/yyyy)\n";
	cin >> semester->regEnd;
	system("cls");
	cout << "Course registration session added!\n";
}

void addCourseFromFile(Course*& course) {
	ifstream fi;
	string filename;
	cout << "Input file name. Ex: courses.csv\n";
	cin >> filename;
	fi.open(filename);
	if (fi.is_open()) {
		Course* cTmp = new Course;
		cTmp->cNext = 0;
		string s;
		char c;
		getline(fi, s);
		stringstream ss(s);
		getline(ss, cTmp->id, ',');
		getline(ss, cTmp->name, ',');
		getline(ss, cTmp->teacher, ',');
		getline(ss, cTmp->credits, ',');
		ss >> cTmp->max;
		ss >> c;
		ss >> cTmp->day;
		ss >> c;
		cTmp->enrolled = 0;
		cTmp->session = 0;
		Session* sCur = cTmp->session;
		while (ss) {
			Session* sTmp = new Session;
			sTmp->sNext = 0;
			getline(ss, sTmp->s, ',');
			if (sCur) sCur->sNext = sTmp;
			else cTmp->session = sTmp;
			sCur = sTmp;
		}
		fi.close();
	}
	else cout << "Can't open file " << filename << ".\n";
}

void addCourseFromKeyboard(Course*& course) {
	course = new Course;
	course->cNext = 0;
	cout << "Input a course id:\n";
	cin >> course->id;
	cout << "Input a course name:\n";
	cin.ignore();
	getline(cin, course->name);
	cout << "Input a teachter name:\n";
	cin.ignore();
	getline(cin, course->teacher);
	cout << "Input the number of credits:\n";
	cin >> course->credits;
	cout << "Input the maximum number of students in the course:\n";
	cin >> course->max;
	cout << "Input days of the week:\n";
	cin >> course->day;
	course->enrolled = 0;
	cin.ignore();
	Session* sCur = 0;
	for (int i = 0; i < course->day; i++) {
		Session* sTmp = new Session;
		sTmp->sNext = 0;
		cout << "Input session " << i+1 << " of the week. Ex: MON S1\n";
		getline(cin, sTmp->s);
		if (sCur) sCur->sNext = sTmp;
		else course->session = sTmp;
		sCur = sTmp;
	}
}

void addCourseToSemester(Semester*& semester) {
	Course* cCur = semester->course, * cTmp = 0;
	if (cCur) {
		while (cCur->cNext) cCur = cCur->cNext;
	}
	int choose;
	do {
		cout << "1. Add from csv file.\n";
		cout << "2. Add from keyboard.\n";
		cout << "0. Exit.\n";
		cout << "Input selection:\n";
		cin >> choose;
		system("cls");
		switch (choose) {
		case 1:
			addCourseFromFile(cTmp);
			break;
		case 2:
			addCourseFromKeyboard(cTmp);
			break;
		case 0:
			return;
		default:
			cout << "Invalid selection.\n";
			choose = -1;
			break;
		}
		if (!cCur) semester->course = cTmp;
		else cCur->cNext = cTmp;
		cCur = cTmp;
		system("cls");
		cout << "Course added!\n";
	} while (choose == -1);
}

void viewListCourses(Course* course) {
}

void updateCourseInfo(Course*& course) {
	int choose;
	if (!course) {
		cout << "There is no course to update!\n";
		return;
	}
	Course* cSelect = 0;
	do {
		viewListCourses(course);
		cout << "0. Exit.\n";
		cout << "Select no. of the course you want to update.\n";
		cin >> choose;
		if (choose != 0) {
			Course* cTmp = course;
			for (int i = 0; i < choose - 1; i++)
				cTmp = cTmp->cNext;
			cSelect = cTmp;
		}
	} while (choose == 0);
	do {
		cout << "1. Course id.\n";
		cout << "2. Course name.\n";
		cout << "3. Teacher name.\n";
		cout << "4. The number of credits.\n";
		cout << "5. The maximum number of students.\n";
		cout << "6. Days and Sessions of the week.\n";
		cout << "0. Exit.\n";
		cout << "Select the information you want to update:\n";
		cin >> choose;
		switch (choose) {
		case 1:
			cout << "Input a course id:\n";
			cin >> cSelect->id;
			break;
		case 2:
			cout << "Input a course name:\n";
			cin.ignore();
			getline(cin, cSelect->name);
			break;
		case 3:
			cout << "Input a teacher name:\n";
			cin.ignore();
			getline(cin, cSelect->teacher);
			break;
		case 4:
			cout << "Input a the number of credits:\n";
			cin >> cSelect->credits;
			break;
		case 5:
			cout << "Input the maximum number of students:\n";
			cin >> cSelect->max;
			break;
		case 6:
		{
			while (cSelect->session) {
				Session* sTmp = cSelect->session;
				cSelect->session = sTmp->sNext;
				delete sTmp;
			}
			cout << "Input days of the week:\n";
			cin >> cSelect->day;
			cSelect->session = 0;
			Session* sCur = cSelect->session;
			for (int i = 0; i < int(cSelect->day) - 48; i++) {
				Session* sTmp = new Session;
				sTmp->sNext = 0;
				cout << "Input session " << i + 1 << " of the week. Ex: MON S1\n";
				cin >> sTmp->s;
				if (sCur) sCur->sNext = sTmp;
				else cSelect->session = sTmp;
				sCur = sTmp;
			}
		}
			break;
		case 0:
			return;
		default:
			cout << "Invalid selection!\n";
			break;
		}
		if (choose > 0 && choose < 7) {
			system("cls");
			cout << "Info updated!\n";
		}
	} while (choose != 0);
}

void deleteCourse(Course*& course) {

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
void enrollCourse(Data*& data, Course* course, string accountCur) {

	/*
	do{
		cout << "1. Enroll a course.\n";
		cout << "2. View list of enrolled course.\n";
		cout << "3. Remove a course from enrolled list.\n";
		cout << "0. Exit.\n";
		cout << "Select the information you want to update:\n";
		cin >> choose;
		switch (choose) {
		case 1:
			viewListCourses(course);
			cout << "Select no. of the course you want to enroll:\n";
			cin >> cSelect->id;
			break;
		case 2:
			cout << "Input a course name:\n";
			cin.ignore();
			getline(cin, cSelect->name);
			break;
		case 3:
			cout << "Input a teacher name:\n";
			cin.ignore();
			getline(cin, cSelect->teacher);
			break;
		case 4:
			cout << "Input a the number of credits:\n";
			cin >> cSelect->credits;
			break;
		case 5:
			cout << "Input the maximum number of students:\n";
			cin >> cSelect->max;
			break;
	}*/
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