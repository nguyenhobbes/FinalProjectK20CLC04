#include "CourseRegistrationSystem.h"

// <--------- Setup --------->


// Functions that's run at the beginning of the system

void loadSettings(ifstream& fi, Setting*& sett) {
	string s;
	if (sett) delete sett;
	sett = new Setting;
	getline(fi, s);
	getline(fi, s, ',');
	getline(fi, sett->ys, ',');
	getline(fi, sett->ye);
	getline(fi, s, ',');
	getline(fi, sett->s1, ',');
	getline(fi, sett->e1);
	getline(fi, s, ',');
	getline(fi, sett->s2, ',');
	getline(fi, sett->e2);
	getline(fi, s, ',');
	getline(fi, sett->s3, ',');
	getline(fi, sett->e3);
}

void saveClassData(ofstream& fo, schYear* sY) {
	while (sY) {
		fo << sY->name << ',' << sY->num;
		Class* c = sY->c;
		while (c) {
			fo << endl << c->name;
			Student* sTmp = c->stu;
			while (sTmp) {
				fo << ',' << sTmp->no << ',' << sTmp->studentID << ',' << sTmp->firstname << ',' << sTmp->lastname << ',' << sTmp->gender << ',' << sTmp->dob << ',' << sTmp->socialID;
				sTmp = sTmp->sNext;
			}
			c = c->cNext;
		}
		if (sY->sYNext) fo << endl;
		sY = sY->sYNext;
	}
}

void loadClassData(ifstream& fi, schYear*& sY) {
	schYear* schCur = 0;
	while (fi.good()) {
		string s;
		getline(fi, s);
		if (s == "") return;
		stringstream ss(s);
		if (ss.good()) {
			schYear* schTmp = new schYear;
			schTmp->sYNext = 0;
			schTmp->c = 0;
			schTmp->num = 0;
			getline(ss, schTmp->name, ',');
			ss >> schTmp->num;
			Class* cCur = 0;
			for (int i = 0; i < schTmp->num; i++) {
				Class* c = new Class;
				c->cNext = 0;
				c->stu = 0;
				string line;
				getline(fi, line);
				stringstream ss2(line);
				if (ss2.good()) getline(ss2, c->name, ',');
				Student* stu = 0;
				while (ss2.good()) {
					Student* sTmp = new Student;
					sTmp->sNext = 0;
					getline(ss2, sTmp->no, ',');
					getline(ss2, sTmp->studentID, ',');
					getline(ss2, sTmp->firstname, ',');
					getline(ss2, sTmp->lastname, ',');
					getline(ss2, sTmp->gender, ',');
					getline(ss2, sTmp->dob, ',');
					getline(ss2, sTmp->socialID, ',');
					if (!stu) c->stu = sTmp;
					else stu->sNext = sTmp;
					stu = sTmp;
				}
				if (!cCur) schTmp->c = c;
				else cCur->cNext = c;
				cCur = c;
			}
			if (!schCur) sY = schTmp;
			else schCur->sYNext = schTmp;
			schCur = schTmp;
		}
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
	if (!fi) return;
	getline(fi, s);
	stringstream st(s);
	getline(st, name, ',');
	getline(st, year);
	Semester* sCur = 0;
	while (fi.good()) {
		getline(fi, s);
		if (s == "") return;
		stringstream ss(s);
		Semester* sTmp = new Semester;
		sTmp->course = 0;
		sTmp->sNext = 0;
		getline(ss, sTmp->name, ',');
		getline(ss, sTmp->schoolYear, ',');
		getline(ss, sTmp->start, ',');
		getline(ss, sTmp->end, ',');
		getline(ss, sTmp->regStart, ',');
		getline(ss, sTmp->regEnd,',');
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
				seTmp->sNext = 0;
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
			else sTmp->course = cTmp;
			cCur = cTmp;
		}
		if (sCur) sCur->sNext = sTmp;
		else semester = sTmp;
		sCur = sTmp;
		if (sTmp->name == name && sTmp->schoolYear == year) sSel = sTmp;
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
		string line;
		getline(fi, line);
		if (line == "") {
			delete data;
			return;
		}
		Data* tmp = new Data;
		tmp->dNext = 0;
		tmp->course = 0;
		tmp->count = 0;
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
			cTmp->score = score->score_next;
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

void deleteClassData(schYear*& sY) {
	while (sY) {
		schYear* sTmp = sY;
		Class* c = sY->c;
		while (c)
		{
			Class* tmp = c;
			c = c->cNext;
			deleteStudentData(tmp->stu);
			delete tmp;
		}
		sY = sY->sYNext;
		delete sTmp;
	}
}

// Additional function

void getStudentData(schYear* sY, Student*& studentCur, Data* data, Data*& dSel, string accountCur) {
	while (data) {
		if (data->id == accountCur) {
			dSel = data;
			break;
		}
		data = data->dNext;
	}
	while (sY) {
		Class* c = sY->c;
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
		sY = sY->sYNext;
	}
}

void splitDate(string s, int &d, int &m, int &y) {
	stringstream ss(s);
	char c1, c2;
	ss >> d >> c1 >> m >> c2 >> y;
}

bool checkRegTime(string s1, string s2, tm* rt) {
	int d1, d2, m1, m2, y1, y2;
	splitDate(s1, d1, m1, y1);
	splitDate(s2, d2, m2, y2);
	d1--; m1--; y1--; d2--; m2--; y2--;
	if (rt->tm_year < y1 || rt->tm_year > y2) return 0;
	if (y1 < y2) {
		if (rt->tm_year == y1) {
			if (rt->tm_mon < m1 || (rt->tm_mon + 1 == m1 && rt->tm_mday < d1)) return 0;
		}
		else if (rt->tm_mon > m2 || (rt->tm_mon + 1 == m2 && rt->tm_mday > d2)) return 0;
	}
	else {
		if (rt->tm_mon < m1 || rt->tm_mon > m2 || (rt->tm_mon == m1 && rt->tm_mday < d1) || (rt->tm_mon == m2 && rt->tm_mday > d2)) return 0;
	}
	return 1;
}

bool checkBeginTime(string s1, string s2, tm* rt) {
	int d1, d2, m1, m2, y1, y2;
	splitDate(s1, d1, m1, y1);
	splitDate(s2, d2, m2, y2);
	d1--; m1--; d2--; m2--;
	if (rt->tm_mon < m1 || rt->tm_mon > m2 || (rt->tm_mon == m1 && rt->tm_mday + 1 < d1) || (rt->tm_mon == m2 && rt->tm_mday + 1 > d2)) return 0;
	return 1;
}

bool checkEndTime(string s, tm* rt) {
	int d, m, y;
	splitDate(s, d, m, y);
	if (rt->tm_year < y || rt->tm_mon < m || (rt->tm_mon == m && rt->tm_mday + 1 <= d)) return 0;
	return 1;
}



// <--------- Setup --------->