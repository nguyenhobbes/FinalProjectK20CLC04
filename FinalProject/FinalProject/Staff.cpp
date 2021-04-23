#include "CourseRegistrationSystem.h"

// <--------- Staff --------->

// Functions for Staff 

// At the beginning of a school year, 3 semesters.
void createSchoolYear(string& schoolYear) {
	cout << "Input a school year:\n";
	cin >> schoolYear;
}

void create1stClass(string& cl) {
	cout << "Input name of class:\n";
	cin >> cl;
}

void add1stStudentsTo1stClasses(ifstream& fi, string schoolYear, string cl, Class*& c, Account* account, Data*& data) {
	Class* cCur = c;
	Class* cTmp = new Class;
	cTmp->cNext = 0;
	cTmp->schoolYear = schoolYear;
	cTmp->name = cl;
	Student* sCur = 0;
	Data* dCur = data;
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
		Data* dTmp = new Data;
		dTmp->id = sTmp->studentID;
		dTmp->dNext = 0;
		dTmp->course = 0;
		if (!dCur) data = dTmp;
		else dCur->dNext = dTmp;
		dCur = dTmp;
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
	Course* cCur = 0;
	cout << "Input file name. Ex: courses.csv\n";
	cin >> filename;
	fi.open(filename);
	if (fi.is_open()) {
		Course* cTmp = new Course;
		cTmp->stu = 0;
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
		if (!cCur) course = cTmp;
		else cCur->cNext = cTmp;
		cCur = cTmp;
		fi.close();
	}
	else cout << "Can't open file " << filename << ".\n";
}

void addCourseFromKeyboard(Course*& course) {
	course = new Course;
	course->stu = 0;
	course->cNext = 0;
	cout << "Input a course id:\n";
	cin >> course->id;
	cin.ignore();
	cout << "Input a course name:\n";
	getline(cin, course->name);
	cout << "Input a teachter name:\n";
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
		cout << "Input session " << i + 1 << " of the week. Ex: MON S1\n";
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
		cTmp = 0;
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
	Course* cCur = course;
	system("cls");
	cout << " ---- COURSES IN THE SEMESTER ----" << endl;
	if (!course) cout << "There is no course!" << endl;
	else {
		cout << "No ID         Name             Teacher              Credits    Students    Sessions\n";
		int z = 1;
		while (cCur) {
			stringstream ss;
			ss << cCur->enrolled << '/' << cCur->max;
			string s;
			ss >> s;
			cout << left << setw(3) << z << setw(11) << cCur->id << setw(17) << cCur->name << setw(21) << cCur->teacher << setw(11) << cCur->credits << setw(12) << s;
			Session* sTmp = cCur->session;
			while (sTmp) {
				cout << sTmp->s << ", ";
				sTmp = sTmp->sNext;
			}
			cout << endl;
			cCur = cCur->cNext;
		}
	}
}

void updateCourseInfo(Course*& course) {
	int choose;
	if (!course) {
		cout << "There is no course to update!\n";
		return;
	}
	Course* cSelect = course;
	do {
		viewListCourses(course);
		cout << "0. Exit.\n";
		cout << "Select no. of the course you want to update.\n";
		cin >> choose;
		if (choose != 0) {
			for (int i = 0; i < choose - 1; i++)
				if (cSelect) cSelect = cSelect->cNext;
		}
		system("cls");
		if (!cSelect) cout << "The course is not exist!\n";
	} while (choose == 0 && !cSelect);
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
	int choose;
	Course* cSelect = 0;
	do {
		cSelect = course;
		viewListCourses(course);
		cout << "0. Exit.\n";
		cout << "Select no. of the course you want to delete.\n";
		cin >> choose;
		if (choose == 0) return;
		else 
		{
			for (int i = 0; i < choose - 1; i++)
				cSelect = cSelect->cNext;
		}
		system("cls");
		if (!cSelect) {
			cout << "The course is not exist!\n";
			choose = -1;
		}
	} while (choose == -1);
	if (cSelect == course) {
		course = cSelect->cNext;
	}
	else {
		Course* cTmp = course;
		while (cTmp->cNext != cSelect) {
			cTmp = cTmp->cNext;
		}
		cTmp->cNext = cSelect->cNext;
	}
	while (cSelect->session) {
		Session* sTmp = cSelect->session;
		cSelect->session = sTmp->sNext;
		delete sTmp;
	}
	while (cSelect->stu) {
		Student* sTmp = cSelect->stu;
		cSelect->stu = sTmp->sNext;
		delete sTmp;
	}
	delete cSelect;
	cout << "The course has been deleted.\n";
	system("pause");
}

// At any time:
void viewListClasses(Class* c) {
	Class* cTmp = c;
	int i = 1;
	cout << "List of classes: " << endl;
	while (cTmp) {
		cout << i << ". " << cTmp->name << endl;
		cTmp = cTmp->cNext;
		i++;
	}
}
void viewListStudentInClass(Class* c) {
	Class* cCur = c;
	viewListClasses(c);
	string cl;
	cout << "Select which class to view students list: "; 
	cin >> cl;
	while (cCur && cCur->name != cl) {
		cCur = cCur->cNext;
	}

	if (!cCur) cout << "The class is not exist!" << endl;
	else {
		Student* sTmp = cCur->stu;
		cout << "No Student ID  First Name  Last Name       Gender  Date of birth  Social ID" << endl;
		while (sTmp) {
			cout << left << setw(3) << sTmp->no << setw(12) << sTmp->studentID << setw(12) << sTmp->firstname << setw(16) << sTmp->lastname << setw(8) << sTmp->gender << setw(15) << sTmp->dob << setw(12) << sTmp->socialID << endl;
			sTmp = sTmp->sNext;
		}
	}
}

// view list course.
void viewListStudentInCourse(Course* course) {
	int choose;
	do {
		Course* cSelect = course;
		viewListCourses(course);
		cout << "0. Exit.\n";
		cout << "Select no. of the course you want to view the List of Student.\n";
		cin >> choose;
		if (choose != 0) {
			for (int i = 0; i < choose - 1; i++) {
				if (cSelect) cSelect = cSelect->cNext;
			}
		}
		else return;
		system("cls"); 
		if (!cSelect) cout << "The course is not exist!" << endl;
		else {
			Student* sTmp = cSelect->stu;
			cout << "No Student ID  First Name  Last Name       Gender  Date of birth  Social ID" << endl;
			while (sTmp) {
				cout << left << setw(3) << sTmp->no << setw(12) << sTmp->studentID << setw(12) << sTmp->firstname << setw(16) << sTmp->lastname << setw(8) << sTmp->gender << setw(15) << sTmp->dob << setw(12) << sTmp->socialID << endl;
				sTmp = sTmp->sNext;
			}
		}
	} while (choose != 0);
}

//At the end of a semester
void exportListStudent(Course* course, ofstream& fo) {
	Course* cExp = course;
	while (cExp) {
		string FileListStudentCourse = cExp->name + ".csv";
		fo.open(FileListStudentCourse);
		fo << "No,Student ID,Fullname,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
		if (fo.is_open()) {
			fo << cExp->name;
			Student* sTmp = cExp->stu;
			while (sTmp) {
				fo << endl << sTmp->no << "," << sTmp->studentID << "," << sTmp->lastname << ' ' << sTmp->firstname;
				sTmp = sTmp->sNext;
			}
		}
		cExp = cExp->cNext;
	}
}

void importScoreboard(Course* course, ifstream& fi, Score*& score) {
	Course* cImp = course;
	while (cImp) {
		string FileScoreboard = cImp->name + ".csv"; // Minh se dat ten theo cu phap nay nha
		fi.open(FileScoreboard);
		if (!fi.is_open()) {
			cout << "Cannot open file " << FileScoreboard << "!\n";
		}
		else {
			string s;
			char c;
			getline(fi, s);
			Score* sco = new Score;
			sco->score_next = 0;
			while (fi.good()) {
				getline(fi, s);
				stringstream ss(s);
				getline(ss, sco->no, ',');
				getline(ss, sco->studentID, ',');
				getline(ss, sco->fullname, ',');
				ss >> sco->total;
				ss >> c;
				ss >> sco->final;
				ss >> c;
				ss >> sco->midterm;
				ss >> c;
				ss >> sco->other;
			}
		}
	}
}

void viewCourseScoreboard() {

}

void updateStudentResult(Score* score) {

}

void viewClassScoreboard() {

}

// <--------- Staff --------->