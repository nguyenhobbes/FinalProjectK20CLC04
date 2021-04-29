#include "CourseRegistrationSystem.h"

int main() {
	Account* account = 0;
	Class* c = 0;
	Semester* semester = 0, * sSel = 0;
	Course* course = 0;
	Data* data = 0;
	string accountCur = "", type = "";
	Student* studentCur = 0;
	Score* score = 0;
	time_t now = time(0);
	tm* rt = localtime(&now);
	ifstream fi;
	ofstream fo;
	fi.open("Accounts.csv");
	if (fi.is_open()) {
		loadAccountData(fi, account);
		fi.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	fi.open("Classes.csv");
	if (fi.is_open()) {
		loadClassData(fi, c);
		fi.close();
	}
	fi.open("Semester.csv");
	if (fi.is_open()) {
		loadSemesterData(fi, semester, sSel);
		fi.close();
	}
	fi.open("StudentData.csv");
	if (fi.is_open()) {
		loadStudentCourseData(fi, data);
		fi.close();
	}
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
					if (type == "Staff") {
						cout << "4. View list of classes.\n";
						cout << "5. View list of students in a class.\n";
						cout << "6. View list of courses.\n";
						cout << "7. View list of students in a course.\n";
						if (rt->tm_mon == 8 && rt->tm_mday < 15) {
							cout << "8. Create a year school.\n";
							cout << "9. Create 1st class.\n";
							cout << "10. Add new 1st year students to classes.\n";
						}
						else if ((rt->tm_mon == 8 && rt->tm_mday >= 24 && rt->tm_mday < 30) ||
							(rt->tm_mon == 0 && rt->tm_mday >= 9 && rt->tm_mday < 15) ||
							(rt->tm_mon == 4 && rt->tm_mday >= 24 && rt->tm_mday < 30)) {
							cout << "8. Create a semester.\n";
							cout << "9. Create a course registration session.\n";
							cout << "10. Add a course to the semester.\n";
							cout << "11. View list of courses.\n";
							cout << "12. Update course information.\n";
							cout << "13. Delete a course.\n";
						}
					}
					else {
						if (sSel && checkRegTime(sSel->regStart, sSel->regEnd))
					}
					cout << "Enter selection: ";
					cin >> choose1;
					switch (choose1) {
					case 1:
						viewProfile(c, accountCur, type);
						break;
					case 2:
						system("cls");
						changePassword(fo, account, accountCur);
						fo.open("Accounts.csv");
						if (fo.is_open()) {
							saveAccountData(fo, account);
							fo.close();
						}
						else cout << "Can't open file Accounts.csv.\n";
						break;
					case 3:
						logOut(accountCur);
						break;
						/*
					case 3:
						if (type == "Staff") {
							int sel;
							do {
								system("cls");
								cout << "1. Create School Year.\n";
								cout << "2. Create Course.\n";
								cout << "3. Score.\n";
								cout << "Select 0 to exit: "; cin >> sel;
								system("cls");
								if (sel == 1) {
									string schoolYear = "", cl = "";
									createSchoolYear(schoolYear);
									create1stClass(cl);
									cout << "Input csv file name. Ex: Studens.csv\n";
									string fname = "";
									cin >> fname;
									fi.open(fname);
									if (fi.is_open()) {
										add1stStudentsTo1stClasses(fi, schoolYear, cl, c, account, data);
										fo.open("Accounts.csv");
										if (fo.is_open()) {
											saveAccountData(fo, account);
											fo.close();
										}
										else cout << "Can't save data of the file Accounts.csv.\n";
										fo.open("Classes.csv");
										if (fo.is_open()) {
											saveClassData(fo, c);
											fo.close();
										}
										else cout << "Can't save data of the file Classes.csv.\n";
										fo.open("StudentData.csv");
										if (fo.is_open()) {
											saveStudentCourseData(fo, data);
											fo.close();
										}
										else cout << "Can't save data of the file StudentData.csv.\n";
										fi.close();
									}
									else cout << "Can't add student from file " << fname << "!\n";
									system("pause");
								}
								else if (sel == 2) {
									int selectCourse;
									do {
										system("cls");
										cout << "1. Create semester.\n";
										cout << "2. Create a course registration session.\n";
										cout << "3. Add a course.\n";
										cout << "4. View list of course.\n";
										cout << "5. Update course information.\n";
										cout << "6. Delete a course.\n";
										cout << "Select 0 to exit: "; cin >> selectCourse;
										system("cls");
										if (selectCourse == 1) {
											createSemester(semester);
										}
										else if (selectCourse == 2) {
											createRegSession(semester);
										}
										else if (selectCourse == 3) {
											addCourseToSemester(semester);
										}
										else if (selectCourse == 4) {
											if (!course) cout << "Nothing!" << endl;
											else viewListCourses(course);
										}
										else if (selectCourse == 5) {
											updateCourseInfo(course);
										}
										else {
											deleteCourse(course);
										}
										cout << endl;
										system("pause");
									} while (selectCourse != 0);
								}
								else if (sel == 3) {

								}
							} while (sel != 0);
						}

						else {

						}*/
					}
				} while (choose1 != 3);
			}
		}
		else if (choose == 0) break;
		else {
			cout << "Invalid selection!\n";
			system("pause");
		}
	} while (choose != 0);
	/*
	string schoolYear = "", cl = "";
	createSchoolYear(schoolYear);
	create1stClass(cl);
	cout << "Input csv file name.\n";
	string fname = "";
	cin >> fname;
	//fname += ".csv\0";
	fi.open(fname);
	if (fi.is_open()) {
		add1stStudentsTo1stClasses(fi, schoolYear, cl, c, account, data);
		fi.close();
	}
	else cout << "Can't open file " << fname << "!\n";
	fo.open("Accounts.csv");
	if (fo.is_open()) {
		saveAccountData(fo, account);
		fo.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
		fo.close();
	}
	else cout << "Can't open file Classes.csv.\n";
	fo.open("StudentData.csv");
	if (fo.is_open()) {
		saveStudentCourseData(fo, data);
		fo.close();
	}
	else cout << "Can't open file StudentData.csv.\n";
	*/
	/* ----------- Create semester
	createSemester(semester);
	int choose = 0;
	do {
		cout << "1. Create a course registration session.\n";
		cout << "2. Add a course to the semester.\n";
		cout << "3. View list of courses.\n";
		cout << "4. Update course information.\n";
		cout << "5. Delete a course.\n";
		cout << "0. Exit.\n";
		cout << "Enter selection:\n";
		cin >> choose;
		system("cls");
		switch (choose) {
		case 1:
			createRegSession(semester);
			break;
		case 2:
			addCourseToSemester(semester);
			break;
		case 3:
			viewListCourses(semester->course);
			break;
		case 4:
			updateCourseInfo(semester->course);
			break;
		case 5:
			deleteCourse(semester->course);
			break;
		case 0:
			break;
		default:
			cout << "Invalid selection.\n";
			choose = -1;
			break;
		}
	} while (choose != 0);
	fo.open("Semester.csv");
	if (fo.is_open()) {
		saveSemesterData(fo, semester);
		fo.close();
	}
	else cout << "Can't open file Semester.csv.\n";
	*/
	/* ------------- Enroll course
	Data* dSelect = data;
	while (dSelect && dSelect->id != accountCur) dSelect = dSelect->dNext;
	int choose;
	do {
		cout << "1. Enroll a course.\n";
		cout << "2. View list of enrolled course.\n";
		cout << "3. Remove a course from enrolled list.\n";
		cout << "0. Exit.\n";
		cout << "Select the information you want to update:\n";
		cin >> choose;
		system("cls");
		switch (choose) {
		case 1:
			if (!semester) {
				cout << "There is an error!\n";
				break;
			}
			enrollCourse(dSelect, semester->course, studentCur);
			fo.open("Classes.csv");
			if (fo.is_open()) {
				saveClassData(fo, c);
				fo.close();
			}
			else cout << "Can't save the course data of student";
			break;
		case 2:
			viewListEnrolledCourses(dSelect);
			break;
		case 3:
			if (!semester) {
					cout << "There is an error!\n";
					break;
			}
			removeEnrolledCourse(dSelect, semester->course);
			break;
		case 0:
			break;
		default:
			cout << "Invalid selection!\n";
			break;
		}
	} while (choose != 0);
	*/
	/*
	getStudentData(c, studentCur, accountCur);
	Data* dSelect = data;
	while (dSelect && dSelect->id != accountCur) dSelect = dSelect->dNext;
	enrollCourse(dSelect, semester->course, studentCur);
	fo.open("Semester.csv");
	if (fo.is_open()) {
		saveSemesterData(fo, semester);
		fo.close();
	}
	else cout << "Can't save the semester data\n";
	fo.open("StudentData.csv");
	if (fo.is_open()) {
		saveStudentCourseData(fo, data);
		fo.close();
	}
	else cout << "Can't save the student data\n";

	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
		fo.close();
	}
	else cout << "Can't save the course data of student";
	studentCur = 0;
	*/
	/*
	int choose;
	do {
	cout << "1. Export list of students in a course to a CSV file.\n";
	cout << "2. Import the scoreboard of a course.\n";
	cout << "3. View the scoreboard of a course.\n";
	cout << "4. Update a student result.\n";
	cout << "5. View the scoreboard of a class.\n";
	cout << "0. Exit.\n";
	cout << "Enter selection:\n";
	cin >> choose;
	system("cls");
	switch (choose) {
	case 1:
		exportListStudent(fo, semester->course);
		break;
	case 2:
		importScoreboard(fi, semester->course, score);
		break;
	case 3:
		viewCourseScoreboard(semester->course);
		break;
	case 4:
		updateStudentResult(semester->course);
		break;
	case 5:
		viewClassScoreboard();
		break;
	case 0:
		break;
	default:
		cout << "Invalid selection.\n";
		choose = -1;
		break;
	}
	} while (choose != 0);
	*/
	deleteSemesterData(semester, sSel);
	deleteAccountData(account);
	deleteStudentCourseData(data);
	deleteClassData(c);
	return 0;
}