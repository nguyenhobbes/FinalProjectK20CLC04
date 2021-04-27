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
		aTmp->password = "1";
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
	system("cls");
	cout << "Created a semester!\n";
	system("pause");
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

void addCourseToSemester(Semester*& semester) {
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
	cout << "Enter the class you want to view list of students: "; 
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
void exportListStudent(ofstream& fo, Course* course) {
	Course* cExp = course;
	while (cExp) {
		string FileListStudentCourse = cExp->name + "Result.csv";
		fo.open(FileListStudentCourse);
		if (fo.is_open()) {
			fo << cExp->name;
			fo << "No,Student ID,Fullname,Total Mark,Final Mark,Midterm Mark,Other Mark,GPA\n";
			Student* sTmp = cExp->stu;
			while (sTmp) {
				fo << endl << sTmp->no << "," << sTmp->studentID << "," << sTmp->lastname << ' ' << sTmp->firstname;
				sTmp = sTmp->sNext;
			}
		}
		cExp = cExp->cNext;
	}
}

void importScoreboard(ifstream& fi, Course* course, Score*& score) {
	Course* cImp = course;
	while (cImp) {
		string FileScoreboard = cImp->name + "Result.csv";
		fi.open(FileScoreboard);
		if (!fi.is_open()) {
			cout << "Cannot open file " << FileScoreboard << "!\n";
		}
		else {
			string s;
			char c;
			getline(fi, s);
			Score* scoTmp = score;
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
				if (!scoTmp) score = sco;
				else scoTmp->score_next = sco;
				scoTmp = sco;
			}
		}
	}
}

void viewCourseScoreboard(Course* course) {
	cout << "Scoreboard of " << course->name << endl;
	Score* scTmp = course->score;
	cout << "No  Student ID  Full Name                Other  Midterm  Final  Total" << endl;
	while (scTmp) {
		cout << left << setw(4) << scTmp->no << setw(12) << scTmp->studentID << setw(25) << scTmp->fullname << setw(7) << scTmp->other << setw(9) << scTmp->midterm << setw(7) << scTmp->final << setw(7) << scTmp->total;
		scTmp = scTmp->score_next;
	}
}

void updateStudentResult(Course* course) {
	int choose;
	string s;
	do {
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
			cout << "The course is not exist!" << endl;
			system("pause");
		}
		else {
			int choose1;
			do {
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
							cout << "Student's total mark is updated!\n";
							break;
						case 2:
							cout << "Input a new final mark: ";
							cin >> sc;
							sTmp->final = sc;
							cout << "Student's final mark is updated!\n";
							break;
						case 3:
							cout << "Input a new midterm mark: ";
							cin >> sc;
							sTmp->midterm = sc;
							cout << "Student's midterm mark is updated!\n";
							break;
						case 4:
							cout << "Input a new other mark: ";
							cin >> sc;
							sTmp->other = sc;
							cout << "Student's other mark is updated!\n";
							break;
						default:
							cout << "Invalid selection!\n";
							break;
						}
						system("pause");
					} while (choose2 != 0);
				}
			} while (choose != 0);
		}
		system("pause");
	} while (choose != 0);
	
}

void viewClassScoreboard(Class* cl, Data* data, Course* course) { //Chua test
	Class* cls = cl;
	string s;
	do {
		viewListClasses(cls);
		cout << "Enter name of class you want to see the scoreboard: ";
		cin >> s;
		while (cls && cls->name != s) {
			cls = cls->cNext;
		}
		if (!cls) {
			cout << "The class is not exist!\n";
		}
		else {
			cout << endl << "ScoreBoard " << cls->name << endl;
			cout << "No  Student ID  Full Name                Course Name     Final  GPA" << endl;
			Student* stu = cls->stu;
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
				cout << right << setw(64) << "Overall GPA: " << left << ogpa/d->count << endl;
				stu = stu->sNext;
			}
		}
		system("pause");
	} while (!cls);
	
}

// <--------- Staff --------->