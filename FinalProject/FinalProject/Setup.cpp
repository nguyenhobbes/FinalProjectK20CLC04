#include "CourseRegistrationSystem.h"

// <--------- Setup --------->


// Functions that's run at the beginning of the system

void saveClassData(ofstream& fo, Class* c) {
	while (c) {
		fo << c->schoolYear << ',' << c->name;
		Student* sTmp = c->stu;
		while (sTmp) {
			fo << "\n" << sTmp->no << ',' << sTmp->studentID << ',' << sTmp->firstname << ',' << sTmp->lastname << ',' << sTmp->gender << ',' << sTmp->dob << ',' << sTmp->socialID;
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

void saveSemesterData(ofstream& fo, Semester* semester, Semester* sSel) {
	if (!semester) return;
	fo << sSel->name << ',' << sSel->schoolYear << endl;
	while (semester) {
		fo << semester->name << ',' << semester->schoolYear << ',' << semester->start << ',' << semester->end << ',' << semester->regStart << ',' << semester->regEnd << ',' << semester->num;
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
		semester = semester->sNext;
	}
}

void loadSemesterData(ifstream& fi, Semester*& semester, Semester*& sSel) {
	string s, name, year;
	getline(fi, name, ',');
	getline(fi, year, ',');
	Semester* sCur = 0;
	while (fi.good()) {
		getline(fi, s);
		stringstream ss(s);
		Semester* sTmp = new Semester;
		sTmp->course = 0;
		getline(ss, sTmp->name, ',');
		getline(ss, sTmp->schoolYear, ',');
		getline(ss, sTmp->start, ',');
		getline(ss, sTmp->end, ',');
		getline(ss, sTmp->regStart, ',');
		getline(ss, sTmp->regEnd);
		ss >> sTmp->num;
		Course* cCur = sTmp->course;
		for (int i = 0; i < sTmp->num; i++) {
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
			cTmp->cNext = 0;
			Session* seCur = cTmp->session;
			for (int j = 0; j < cTmp->day; j++) {
				Session* seTmp = new Session;
				sTmp->sNext = 0;
				getline(sss, seTmp->s, ',');
				if (seCur) seCur->sNext = seTmp;
				else cTmp->session = seTmp;
				seCur = seTmp;
			}
			sss >> cTmp->enrolled;
			cTmp->stu = 0;
			Student* stu = 0;
			for (int j = 0; j < cTmp->enrolled; j++) {
				Student* stuTmp = new Student;
				stuTmp->sNext = 0;
				getline(sss, stuTmp->no, ',');
				getline(sss, stuTmp->studentID, ',');
				getline(sss, stuTmp->firstname, ',');
				getline(sss, stuTmp->lastname, ',');
				getline(sss, stuTmp->gender, ',');
				getline(sss, stuTmp->dob, ',');
				getline(sss, stuTmp->socialID, ',');
				if (!stu) cTmp->stu = stuTmp;
				else stu->sNext = stuTmp;
				stu = stuTmp;
			}
			if (cCur) cCur->cNext = cTmp;
			else semester->course = cTmp;
			cCur = cTmp;
			if (sCur) sCur->sNext = sTmp;
			else semester = sTmp;
			sCur = sTmp;
			if (sTmp->name == name && sTmp->schoolYear == year) sSel = sTmp;
		}
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

void deleteSemesterData(Semester*& semester, Semester*& sSel) {
	if (!semester) return;
	sSel = 0;
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

bool checkRegTime(string s1, string s2, tm* rt) {
	stringstream ss1(s1), ss2(s2);
	int d1, d2, m1, m2, y1, y2;
	char c1, c2;
	ss1 >> d1 >> c1 >> m1 >> c2 >> y1;
	ss2 >> d2 >> c1 >> m2 >> c2 >> y2;
	if (rt->tm_year < y1 || rt->tm_year > y2) return 0;
	if (y1 < y2) {
		if (rt->tm_year == y1) {
			if (rt->tm_mon < m1 || (rt->tm_mon == m1 && rt->tm_mday + 1 < d1)) return 0;
		}
		else if (rt->tm_mon > m2 || (rt->tm_mon == m2 && rt->tm_mday + 1 > d2)) return 0;
	}
	else {
		if (rt->tm_mon < m1 || rt->tm_mon > m2 || (rt->tm_mon == m1 && rt->tm_mday + 1 < d1) || (rt->tm_mon == m2 && rt->tm_mday + 1 > d2)) return 0;
	}
	return 1;
}
// <--------- Setup --------->