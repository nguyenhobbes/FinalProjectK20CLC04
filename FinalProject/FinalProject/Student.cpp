#include "CourseRegistrationSystem.h"

// <--------- Student --------->

// When a course registration session is active.
void enrollCourse(Data* data, Course* course, Student* studentCur) {
	int choose;
	do {
		Course* cSelect = course;
		viewListCourses(course);
		cout << "0. Back.\n";
		cout << "Enter no. of the course you want to enroll.\n";
		cin >> choose;
		if (choose != 0) {
			for (int i = 0; i < choose - 1; i++)
				if (cSelect) cSelect = cSelect->cNext;
		}
		if (choose == 0) return;
		system("cls");
		if (!cSelect) cout << "The course is not exist!\n";
		else {
			if (cSelect->enrolled == cSelect->max) {
				cout << "This course is full now!\n";
			}
			else if (data->count == 5){
				cout << "You had been enrolled .....\n";
			}
			else {
				Course* cCheck = data->course;
				while (cCheck && cCheck->name != cSelect->name) cCheck = cCheck->cNext;
				if (cCheck) {
					cout << "You had already enrolled this course!\n";
					return;
				}
				Course* cCheckSession = data->course;
				while (cCheckSession && cCheckSession->cNext) {
					Session* sTmp1 = cCheckSession->session;
					while (sTmp1) {
						Session* sTmp2 = cSelect->session;
						while (sTmp2) {
							if (sTmp1->s == sTmp2->s) {
								cout << "Trung`tiet hoc.....\n";
								return;
							}
							sTmp2 = sTmp2->sNext;
						}
						sTmp1 = sTmp2->sNext;
					}
				}
				Course* cTmp = new Course;
				cSelect->enrolled++;
				cTmp->cNext = 0;
				cTmp->id = cSelect->id;
				cTmp->name = cSelect->name;
				cTmp->teacher = cSelect->teacher;
				cTmp->credits = cSelect->credits;
				cTmp->max = cSelect->max;
				cTmp->day = cSelect->day;
				Student* stuTmp = new Student;
				stuTmp->sNext = 0;
				stuTmp->dob = studentCur->dob;
				stuTmp->firstname = studentCur->firstname;
				stuTmp->gender = studentCur->gender;
				stuTmp->lastname = studentCur->lastname;
				stuTmp->no = studentCur->no;
				stuTmp->socialID = studentCur->socialID;
				stuTmp->studentID = studentCur->studentID;
				Student* stu = cSelect->stu;
				if (!stu) cSelect->stu = stuTmp;
				else {
					while (stu->sNext) stu = stu->sNext;
					stu->sNext = stuTmp;
				}
				Session* sCur1 = 0, * sCur2 = cSelect->session;
				while (sCur2) {
					Session* sTmp = new Session;
					sTmp->sNext = 0;
					sTmp->s = sCur2->s;
					if (!sCur1) cTmp->session = sTmp;
					else sCur1->sNext = sTmp;
					sCur1 = sTmp;
					sCur2 = sCur2->sNext;
				}
				if (!data->course) data->course = cTmp;
				else {
					Course* cCur = data->course;
					while (cCur->cNext) cCur = cCur->cNext;
					cCur->cNext = cTmp;
				}
				cout << "The course has been enrolled.\n";
			}
			system("pause");
		}
	} while (choose != 0);	
}

void viewListCourse(Course* cCur) {
	cout << "No ID         Name             Teacher              Credits    Students    Sessions\n";
	int z = 1;
	while (cCur) {
		stringstream ss;
		ss << cCur->enrolled << '/' << cCur->max;
		string s;
		ss >> s;
		cout << left << setw(3) << z << setw(11) << cCur->id << setw(17) << cCur->name << setw(21) << cCur->teacher << setw(11) << cCur->credits << setw(12) << s;
		z++;
		Session* sTmp = cCur->session;
		while (sTmp) {
			cout << sTmp->s << ", ";
			sTmp = sTmp->sNext;
		}
		cout << endl;
		cCur = cCur->cNext;
	}
}

void viewListEnrolledCourses(Data* data) {
	if (!data->course) {
		cout << "There is no course that has been enrolled!\n";
	}
	else {
		cout << "----------LIST ENROLLED COURSES----------\n";
		viewListCourse(data->course);
	}
	system("pause");
}

void removeEnrolledCourse(Data* data, Course* course) {
	if (!data->course) {
		cout << "There is no course that has been enrolled!\n";
		return;
	}
	else {
		int choose;
		Course* cSelect = 0;
		do {
			cSelect = data->course;
			viewListEnrolledCourses(data);
			cout << "0. Back.\n";
			cout << "Enter no. of the course you want to remove.\n";
			cin >> choose;
			if (choose == 0) return;
			else {
				for (int i = 0; i < choose - 1; i++)
					if (cSelect) cSelect = cSelect->cNext;
			}
			if (choose == 0) return;
			system("cls");
			if (!cSelect) {
				cout << "The course is not exist!\n";
				choose = -1;
			}
		} while (choose == -1);
		if (cSelect == data->course) {
			data->course = cSelect->cNext;
		}
		else {
			Course* cCur = data->course;
			while (cCur->cNext != cSelect) cCur = cCur->cNext;
			cCur->cNext = cSelect->cNext;
		}
		while (cSelect->session) {
			Session* sTmp = cSelect->session;
			cSelect->session = sTmp->sNext;
			delete sTmp;
		}
		Course* cTmp = course;
		while (cTmp->id != cSelect->id && cTmp->name != cSelect->name) {
			cTmp = cTmp->cNext;
		}
		if (cTmp->stu->studentID == data->id) {
			Student* sTmp = cTmp->stu;
			cTmp->stu = sTmp->sNext;
			delete sTmp;
		}
		else {
			Student* sCur = cTmp->stu;
			while (sCur->sNext->studentID != data->id) {
				sCur = sCur->sNext;
			}
			Student* sTmp = sCur->sNext;
			sCur->sNext = sTmp->sNext;
			delete sTmp;
		}
		delete cSelect;
		system("pause");
	}
}

// When a course registration session is close.
void viewListCoursesInSemester(Data* data) {
	if (!data->course) {
		cout << "There is no course in this semester!\n";
	}
	else {
		cout << "----------LIST COURSES IN SEMESTER----------\n";
		viewListCourse(data->course);
	}
	system("pause");
}

// When the scoreboard has been published
void viewScoreboard() {

}

// <--------- Student --------->