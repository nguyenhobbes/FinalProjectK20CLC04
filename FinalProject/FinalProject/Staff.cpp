#include "CourseRegistrationSystem.h"

// <--------- Staff --------->

// Functions for Staff 

// At the beginning of a school year, 3 semesters.
void createSchoolYear(schYear*& sY) {
	schYear* sCur = sY;
	string schoolYear;
	cout << "Input a school year: ";
	cin >> schoolYear;
	while (sCur) {
		if (sCur->name == schoolYear) {
			changeColor(4);
			cout << "This school year had already created before!\n";
			system("pause");
			return;
		}
		sCur = sCur->sYNext;
	}
	sCur = sY;
	if (sCur)
		while (sCur->sYNext) sCur = sCur->sYNext;
	schYear* sTmp = new schYear;
	sTmp->c = 0;
	sTmp->name = schoolYear;
	sTmp->num = 0;
	sTmp->sYNext = 0;
	if (!sCur) sY = sTmp;
	else sCur->sYNext = sTmp;
	cout << "Created school year " << schoolYear << endl;
	system("pause");
}

void create1stClass(schYear* sY) {
	string schoolYear;
	cout << "Input the school year: ";
	cin >> schoolYear;
	while (sY) {
		if (sY->name == schoolYear) break;
		sY = sY->sYNext;
	}
	if (!sY) {
		changeColor(4);
		cout << "The school year is not exist!\n";
		system("pause");
		return;
	}
	string cl;
	do {
		system("cls");
		cout << "Input the name of class: \n";
		cout << "Enter 0 to exit.\n"; 
		cin >> cl;
		if (cl == "0") break;
		Class* cCur = sY->c;
		while (cCur) {
			if (cCur->name == cl) {
				changeColor(4);
				cout << "This class had already created before!\n";
				system("pause");
				break;
			}
			cCur = cCur->cNext;
		}
		changeColor(11);
		cCur = sY->c;
		if (cCur)
			while (cCur->cNext) cCur = cCur->cNext;
		Class* cTmp = new Class;
		cTmp->stu = 0;
		cTmp->cNext = 0;
		cTmp->name = cl;
		sY->num++;
		if (cCur) cCur->cNext = cTmp;
		else sY->c = cTmp;
		cout << "Added class " << cl << endl;
		system("pause");
	} while (1);
	system("pause");
}

void add1stStudentsTo1stClasses(ifstream& fi, schYear* sY, Account* account, Data*& data) {
	system("cls");
	if (!sY) {
		changeColor(4);
		cout << "There is no class to add!\n";
		system("pause");
		return;
	}
	viewListClasses(sY);
	int choose;
	cout << "Enter the no. of the class you want to view list of students: ";
	cin >> choose;
	Class* c = sY->c;
	while (sY && choose != 1) {
		c = sY->c;
		while (c && choose != 1) {
			c = c->cNext;
			choose--;
		}
		sY = sY->sYNext;
	}
	if (!c || choose != 1) {
		changeColor(4);
		cout << "The class is not exist!" << endl;
		system("pause");
		return;
	}
	string z;
	cout << "Please enter the csv file name of student data you want to add. Example: Students.csv\n";
	cin >> z;
	fi.open(z);
	if (!fi.is_open()) {
		changeColor(4);
		cout << "Can't open file!\n";
		system("pause");
		return;
	}
	Student* sCur = 0;
	Data* dCur = 0;
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
		int day, mon, year;
		splitDate(sTmp->dob, day, mon, year);
		stringstream dob;
		dob << year << mon << day;
		string dateTmp;
		dob >> dateTmp;
		aTmp->password = dateTmp;
		aTmp->type = "Student";
		account->aNext = aTmp;
		account = aTmp;
		Data* dTmp = new Data;
		dTmp->id = sTmp->studentID;
		dTmp->count = 0;
		dTmp->dNext = 0;
		dTmp->course = 0;
		if (!dCur) data = dTmp;
		else dCur->dNext = dTmp;
		dCur = dTmp;
		if (!sCur) c->stu = sTmp;
		else sCur->sNext = sTmp;
		sCur = sTmp;
	}
	changeColor(10);
	cout << "Successfully added.\n";
	system("pause");
}

// At the beginning of a semester.
void createSemester(Semester*& semester, Semester*& sSel) {
	Semester* sTmp = new Semester;
	sTmp->sNext = 0;
	sTmp->course = 0;
	cout << "Input semester:\n";
	cin >> sTmp->name;
	cout << "Input school year: (Format: yyyy-yyyy)\n";
	cin >> sTmp->schoolYear;
	cout << "Input start date: (Format: dd/mm/yyyy)\n";
	cin >> sTmp->start;
	cout << "Input end date: (Format: dd/mm/yyyy)\n";
	cin >> sTmp->end;
	sTmp->num = 0;
	Semester* sCur = semester;
	if (!sCur) semester = sTmp;
	else {
		while (sCur->sNext) sCur = sCur->sNext;
		sCur->sNext = sTmp;
	}
	sSel = sTmp;
	system("cls");
	changeColor(10);
	cout << "Created a semester!\n";
	system("pause");
}

void createRegSession(Semester* semester) {
	cout << "Input registration session start date: (Format: dd/mm/yyyy)\n";
	cin >> semester->regStart;
	cout << "Input registration session end date: (Format: dd/mm/yyyy)\n";
	cin >> semester->regEnd;
	system("cls");
	changeColor(10);
	cout << "Course registration session added!\n";
	system("pause");
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
		cTmp->score = 0;
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
		for (int i=0; i < cTmp->day; i++) {
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
	course->score = 0;
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

void addCourseToSemester(Semester* semester) {
	Course* cCur = semester->course, * cTmp = 0;
	if (cCur) {
		while (cCur->cNext) cCur = cCur->cNext;
	}
	int choose;
	do {
		cout << "1. Add from csv file.\n";
		cout << "2. Add from keyboard.\n";
		cout << "0. Back.\n";
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
			changeColor(4);
			cout << "Invalid selection.\n";
			choose = -1;
			break;
		}
		if (choose < 3 && choose > 0) {
			semester->num++;
			if (!cCur) semester->course = cTmp;
			else cCur->cNext = cTmp;
			cCur = cTmp;
			system("cls");
			changeColor(10);
			cout << "Course added!\n";
		}
		system("pause");
	} while (choose == -1);
}

void changeSemester(Semester* semester, Semester*& sSel) {
	Semester* sTmp = semester;
	int z = 1;
	system("cls");
	cout << "List Semester.\n";
	while (sTmp) {
		cout << z++ << ". " << sTmp->name << "/" << sTmp->schoolYear << endl;
		sTmp = sTmp->sNext;
	}
	int choose;
	cout << "Enter no. of the semester you want to select: ";
	cin >> choose;
	system("cls");
	for (int i = 1; i < choose && semester; i++) semester = semester->sNext;
	if (semester) {
		sSel = semester;
		cout << "The semester is selected.\n";
	}
	else cout << "The semester is not exist!\n";
	system("pause");
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
				cout << sTmp->s;
				sTmp = sTmp->sNext;
				if (sTmp) cout << ", ";
			}
			cout << endl;
			cCur = cCur->cNext;
		}
	}
}

void updateCourseInfo(Course*& course) {
	system("cls");
	int choose;
	if (!course) {
		cout << "There is no course to update!\n";
		return;
	}
	Course* cSelect = course;
	do {
		viewListCourses(course);
		cout << "0. Back.\n";
		cout << "Enter no. of the course you want to update.\n";
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
		cout << "0. Back.\n";
		cout << "Select the information you want to update: ";
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
			system("pause");
			break;
		}
		if (choose > 0 && choose < 7) {
			system("cls");
			cout << "Info updated!\n";
			system("pause");
		}
	} while (choose != 0);
}

void deleteCourse(Course*& course) {
	int choose;
	Course* cSelect = 0;
	do {
		cSelect = course;
		viewListCourses(course);
		cout << "0. Back.\n";
		cout << "Enter no. of the course you want to delete.\n";
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
void viewListClasses(schYear* sY) {
	int i = 1;
	if (!sY) {
		changeColor(4);
		cout << "There is no class!\n";
		return;
	}
	cout << "List of classes: " << endl;
	while (sY) {
		Class* cTmp = sY->c;
		while (cTmp) {
			cout << i++ << ". " << cTmp->name << endl;
			cTmp = cTmp->cNext;
		}
		sY = sY->sYNext;
	}
	
}
void viewListStudentInClass(schYear* sY) {
	system("cls");
	if (!sY) {
		changeColor(4);
		cout << "There is no class!\n";
		system("pause");
		return;
	}
	viewListClasses(sY);
	int choose;
	cout << "Enter the no. of the class you want to view list of students: ";
	cin >> choose;
	Class* c = sY->c;
	while (sY && choose != 1) {
		c = sY->c;
		while (c && choose != 1) {
			c = c->cNext;
			choose--;
		}
		sY = sY->sYNext;
	}
	if (!c || choose != 1) {
		changeColor(4);
		cout << "The class is not exist!" << endl;
	}
	else {
		Student* sTmp = c->stu;
		cout << "No Student ID  First Name  Last Name       Gender  Date of birth  Social ID" << endl;
		while (sTmp) {
			cout << left << setw(3) << sTmp->no << setw(12) << sTmp->studentID << setw(12) << sTmp->firstname << setw(16) << sTmp->lastname << setw(8) << sTmp->gender << setw(15) << sTmp->dob << setw(12) << sTmp->socialID << endl;
			sTmp = sTmp->sNext;
		}
	}
	system("pause");
}

// view list course.
void viewListStudentInCourse(Course* course) {
	int choose;
	do {
		Course* cSelect = course;
		viewListCourses(course);
		cout << "0. Back.\n";
		cout << "Enter no. of the course you want to view the list of students.\n";
		cin >> choose;
		if (choose != 0) {
			for (int i = 0; i < choose - 1; i++) {
				if (cSelect) cSelect = cSelect->cNext;
			}
		}
		else return;
		system("cls"); 
		if (!cSelect) {
			changeColor(4);
			cout << "The course is not exist!" << endl;
		}
		else {
			Student* sTmp = cSelect->stu;
			cout << "No Student ID  First Name  Last Name       Gender  Date of birth  Social ID" << endl;
			while (sTmp) {
				cout << left << setw(3) << sTmp->no << setw(12) << sTmp->studentID << setw(12) << sTmp->firstname << setw(16) << sTmp->lastname << setw(8) << sTmp->gender << setw(15) << sTmp->dob << setw(12) << sTmp->socialID << endl;
				sTmp = sTmp->sNext;
			}
		}
		system("pause");
	} while (choose != 0);
}

//At the end of a semester
void exportListStudent(ofstream& fo, Course* course) {
	Course* cExp = course;
	while (cExp) {
		string FileListStudentCourse = cExp->name + "_Result.csv";
		fo.open(FileListStudentCourse);
		if (fo.is_open()) {
			fo << "No,Student ID,Fullname,Total Mark,Final Mark,Midterm Mark,Other Mark";
			Student* sTmp = cExp->stu;
			while (sTmp) {
				fo << endl << sTmp->no << "," << sTmp->studentID << "," << sTmp->lastname << ' ' << sTmp->firstname;
				sTmp = sTmp->sNext;
			}
			fo.close();
		}
		cExp = cExp->cNext;
	}
	changeColor(10);
	cout << "Exported file successfully.\n";
	system("pause");
}

void importScoreboard(ifstream& fi, Course* course) {
	Course* cImp = course;
	while (cImp) {
		string FileScoreboard = cImp->name + "_Result.csv";
		fi.open(FileScoreboard);
		if (!fi.is_open()) {
			cout << "Cannot open file " << FileScoreboard << "!\n";
		}
		else {
			string s;
			char c;
			getline(fi, s);
			Score* scoTmp = course->score;
			while (fi.good()) {
				getline(fi, s);
				if (s == "") break;
				Score* sco = new Score;
				sco->score_next = 0;
				stringstream ss(s);
				sco->total = sco->final = sco->midterm = sco->other = 0;
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
				if (!scoTmp) course->score = sco;
				else scoTmp->score_next = sco;
				scoTmp = sco;
			}
			fi.close();
		}
		cImp = cImp->cNext;
	}
}

void viewCourseScoreboard(Course* course) {
	cout << "Scoreboard of " << course->name << endl;
	Score* scTmp = course->score;
	cout << "No  Student ID  Full Name                Other  Midterm  Final  Total" << endl;
	while (scTmp) {
		cout << left << setw(4) << scTmp->no << setw(12) << scTmp->studentID << setw(25) << scTmp->fullname << setw(7) << scTmp->other << setw(9) << scTmp->midterm << setw(7) << scTmp->final << setw(7) << scTmp->total << endl;
		scTmp = scTmp->score_next;
	}
}

void saveStudentResult(ofstream& fo, Course* course) {
	Course* cExp = course;
	while (cExp) {
		string FileListStudentCourse = cExp->name + "_Result.csv";
		fo.open(FileListStudentCourse);
		if (fo.is_open()) {
			fo << "No,Student ID,Fullname,Total Mark,Final Mark,Midterm Mark,Other Mark";
			Student* sTmp = cExp->stu;
			while (sTmp) {
				Score* score = cExp->score;
				while (score && score->studentID != sTmp->studentID) score = score->score_next;
				if (score) fo << endl << score->no << "," << score->studentID << "," << score->fullname << ',' << score->total << ',' << score->final << ',' << score->midterm << ',' << score->other;
				sTmp = sTmp->sNext;
			}
			fo.close();
		}
		cExp = cExp->cNext;
	}
}

void updateStudentResult(Course* course) {
	int choose;
	string s;
	Course* cTmp = course;
	viewListCourses(course);
	cout << "0. Back.\n";
	cout << "Select the course enrolled by the student whose results you want to change.\n";
	cin >> choose;
	Score* sTmp = 0;
	if (choose != 0) {
		for (int i = 0; i < choose - 1; i++) {
			if (cTmp) cTmp = cTmp->cNext;
		}
	}
	else return;
	if (!cTmp) {
		changeColor(4);
		cout << "The course is not exist!" << endl;
		system("pause");
	}
	else {
		int choose1;
		do {
			system("cls");
			viewCourseScoreboard(cTmp);
			cout << "0. Back.\n";
			cout << "Enter no. of student you want to update result.\n";
			cin >> choose1;
			Score* sTmp = cTmp->score;
			if (choose1 != 0) {
				for (int i = 0; i < choose1 - 1; i++) {
					if (sTmp) sTmp = sTmp->score_next;
				}
			}
			else break;
			if (!sTmp) {
				changeColor(4);
				cout << "Student is not exist!" << endl;
				system("pause");
			}
			else {
				int choose2;
				do {
					system("cls");
					cout << "1. Total Mark.\n";
					cout << "2. Final Mark.\n";
					cout << "3. Midterm Mark.\n";
					cout << "4. Other Mark.\n";
					cout << "0. Back.\n";
					cout << "Select the information you want to update: ";
					cin >> choose2;
					if (choose2 == 0) break;
					float sc;
					switch (choose2) {
					case 1:
						cout << "Input a new total mark: ";
						cin >> sc;
						sTmp->total = sc;
						changeColor(10);
						cout << "Student's total mark is updated!\n";
						break;
					case 2:
						cout << "Input a new final mark: ";
						cin >> sc;
						sTmp->final = sc;
						changeColor(10);
						cout << "Student's final mark is updated!\n";
						break;
					case 3:
						cout << "Input a new midterm mark: ";
						cin >> sc;
						sTmp->midterm = sc;
						changeColor(10);
						cout << "Student's midterm mark is updated!\n";
						break;
					case 4:
						cout << "Input a new other mark: ";
						cin >> sc;
						sTmp->other = sc;
						changeColor(10);
						cout << "Student's other mark is updated!\n";
						break;
					default:
						changeColor(4);
						cout << "Invalid selection!\n";
						break;
					}
					system("pause");
					changeColor(11);
				} while (choose2 != 0);
			}
		} while (choose != 0);
	}
	
}

void viewClassScoreboard(schYear* sY, Data* data, Course* course) {
	system("cls");
	string s;
	if (!sY) {
		changeColor(4);
		cout << "There is no class!\n";
		system("pause");
	}
	viewListClasses(sY);
	cout << "Enter name of class you want to see the scoreboard: ";
	cin >> s;
	Class* c = 0;
	bool check = 1;
	while (sY && check) {
		c = sY->c;
		while (c) {
			if (c->name == s) {
				check = 0;
				break;
			}
			c = c->cNext;
		}
		sY = sY->sYNext;
	}
	if (!sY) {
		changeColor(4);
		cout << "The class is not exist!\n";
	}
	else {
		cout << endl << "ScoreBoard " << s << endl;
		cout << "No  Student ID  Full Name                Course Name     Final  GPA" << endl;
		Student* stu = c->stu;
		while (stu) {
			Data* d = data;
			while (d && d->id != stu->studentID) d = d->dNext;
			if (!d) {
				cout << "Error!\n";
				return;
			}
			float ogpa = 0;
			Course* cCur = d->course;
			while (cCur) {
				Course* cTmp = course;
				while (cTmp && cTmp->name != cCur->name) cTmp = cTmp->cNext;
				if (!cTmp) {
					cout << "Error!\n";
					return;
				}
				Score* sco = cTmp->score;
				while (sco && sco->studentID != stu->studentID) sco = sco->score_next;
				if (!sco) {
					cout << "Error!\n";
					return;
				}
				cout << left << setw(4) << sco->no << setw(12) << sco->studentID << setw(25) << sco->fullname << setw(16) << cTmp->name << setw(7) << sco->final << setw(3) << sco->total << endl;
				ogpa += sco->total;
				cCur = cCur->cNext;
			}
			if (d->count != 0) cout << right << setw(64) << "Overall GPA: " << left << ogpa / d->count << endl;
			stu = stu->sNext;
		}
	}
	system("pause");
	changeColor(11);
}

// <--------- Staff --------->