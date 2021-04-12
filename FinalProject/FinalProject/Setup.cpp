#include "CourseRegistrationSystem.h"

// <--------- Setup --------->


// Functions that's run at the beginning of the system

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
		for (int i = 0; i < cTmp->day; i++) {
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