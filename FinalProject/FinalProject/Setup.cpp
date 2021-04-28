#include "CourseRegistrationSystem.h"

// <--------- Setup --------->


// Functions that's run at the beginning of the system

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
		tmp->stu = 0;
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
		Student* sTmp = cCur->stu;
		while (sTmp) {
			fo << ',' << sTmp->no << ',' << sTmp->studentID << ',' << sTmp->firstname << ',' << sTmp->lastname << ',' << sTmp->gender << ',' << sTmp->dob << ',' << sTmp->socialID;
			sTmp = sTmp->sNext;
		}
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
		cTmp->score = 0;
		Session* sCur = cTmp->session;
		for (int i = 0; i < cTmp->day; i++) {
			Session* sTmp = new Session;
			sTmp->sNext = 0;
			getline(sss, sTmp->s, ',');
			if (sCur) sCur->sNext = sTmp;
			else cTmp->session = sTmp;
			sCur = sTmp;
		}
		sss >> cTmp->enrolled;
		cTmp->stu = 0;
		Student* stu = 0;
		for (int i = 0; i < cTmp->enrolled; i++) {
			Student* sTmp = new Student;
			sTmp->sNext = 0;
			getline(sss, sTmp->no, ',');
			getline(sss, sTmp->studentID, ',');
			getline(sss, sTmp->firstname, ',');
			getline(sss, sTmp->lastname, ',');
			getline(sss, sTmp->gender, ',');
			getline(sss, sTmp->dob, ',');
			getline(sss, sTmp->socialID, ',');
			if (!stu) cTmp->stu = sTmp;
			else stu->sNext = sTmp;
			stu = sTmp;
		}
		if (cCur) cCur->cNext = cTmp;
		else semester->course = cTmp;
		cCur = cTmp;
		cTmp->cNext = 0;
	}
}

void saveStudentCourseData(ofstream& fo, Data* data) {
	while (data) {
		fo << data->id << ',' << data->count;
		Course* cTmp = data->course;
		while (cTmp) {
			fo << ',' << cTmp->id << ',' << cTmp->name << ',' << cTmp->teacher << ',' << cTmp->credits << ',' << cTmp->max << ',' << cTmp->day;
			Session* sTmp = cTmp->session;
			while (sTmp) {
				fo << ',' << sTmp->s;
				sTmp = sTmp->sNext;
			}
			cTmp = cTmp->cNext;
		}
		if (data->dNext) fo << endl;
		data = data->dNext;
	}
}

void loadStudentCourseData(ifstream& fi, Data*& data) {
	Data* dCur = 0;
	while (fi.good()) {
		Data* tmp = new Data;
		tmp->dNext = 0;
		tmp->course = 0;
		tmp->count = 0;
		string line;
		getline(fi, line);
		stringstream s(line);
		getline(s, tmp->id, ',');
		char c;
		s >> tmp->count;
		s >> c;
		Course* cCur = 0;
		while (s.good()) {
			Course* cTmp = new Course;
			cTmp->cNext = 0;
			getline(s, cTmp->id, ',');
			getline(s, cTmp->name, ',');
			getline(s, cTmp->teacher, ',');
			getline(s, cTmp->credits, ',');
			s >> cTmp->max;
			s >> c;
			s >> cTmp->day;
			s >> c;
			cTmp->session = 0;
			Session* sCur = cTmp->session;
			for (int i = 0; i < cTmp->day; i++) {
				Session* sTmp = new Session;
				sTmp->sNext = 0;
				getline(s, sTmp->s, ',');
				if (sCur) sCur->sNext = sTmp;
				else cTmp->session = sTmp;
				sCur = sTmp;
			}
			if (!cCur) tmp->course = cTmp;
			else cCur->cNext = cTmp;
			cCur = cTmp;
		}
		if (!dCur) data = tmp;
		else dCur->dNext = tmp;
		dCur = tmp;
	}
}

void deleteStudentCourseData(Data*& data) {
	while (data) {
		Data* dTmp = data;
		while (dTmp->course) {
			Course* cTmp = dTmp->course;
			while (cTmp->session) {
				Session* sTmp = cTmp->session;
				cTmp->session = sTmp->sNext;
			}
			dTmp->course = cTmp->cNext;
			delete cTmp;
		}
		data = data->dNext;
		delete dTmp;
	}
}

void deleteSemesterData(Semester*& semester) {
	if (!semester) return;
	while (semester->course) {
		Course* cTmp = semester->course;
		while (cTmp->stu) {
			Student* stuTmp = cTmp->stu;
			cTmp->stu = stuTmp->sNext;
			delete stuTmp;
		}
		semester->course = cTmp->cNext;
		while (cTmp->session) {
			Session* sTmp = cTmp->session;
			cTmp->session = sTmp->sNext;
			delete sTmp;
		}
		while (cTmp->score) {
			Score* score = cTmp->score;
			cTmp->score = score->score_next; // error
			delete score;
		}
		deleteStudentData(cTmp->stu);
		delete cTmp;
	}
	delete semester;
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

void getStudentData(Class* c, Student*& studentCur, string accountCur) {
	while (c) {
		Student* sTmp = c->stu;
		while (sTmp) {
			if (sTmp->studentID == accountCur) {
				studentCur = sTmp;
				return;
			}
			sTmp = sTmp->sNext;
		}
		c = c->cNext;
	}
}

//menu

void menuLogin(ofstream& fo, Class* c, Account* account, string& accountCur, string& type) {
	int choose;
	do {
		system("cls");
		cout << "################################\n";
		cout << "#                              #\n";
		cout << "#          1. Log in.          #\n";
		cout << "#          0. Exit.            #\n";
		cout << "#                              #\n";
		cout << "################################\n\n";
		cout << "Input selection: ";
		cin >> choose;
		if (choose == 1) {
			accountCur = "";
			logIn(account, accountCur, type);
			if (accountCur != "") {
				int choose1;
				do {
					system("cls");
					cout << "1. View profile.\n";
					cout << "2. Change password.\n";
					cout << "3. Log out.\n";
					cin >> choose1;
					switch (choose1) {
					case 1:
						viewProfile(c, accountCur, type);

						break;
					case 2:
						changePassword(fo, account, accountCur);
						break;
					case 3:
						logOut(accountCur);
						break;
					case 0:
						break;
					}
				} while (choose1 != 0 && choose1 != 3);
			}
		}
		else if (choose == 0) break;
		else {
			cout << "Invalid selection!\n";
			system("pause");
		}
	} while (choose != 0);
}


// <--------- Setup --------->