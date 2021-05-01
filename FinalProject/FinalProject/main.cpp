#include "CourseRegistrationSystem.h"

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 170;
	sizeOfBuff.Y = 100;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 1000, 700, SWP_SHOWWINDOW | SWP_NOMOVE); }
	changeColor(11);
	loadingScreen();

	Setting* sett = 0;
	Account* account = 0;
	Semester* semester = 0, * sSel = 0;
	Data* data = 0, *dSel = 0;
	string accountCur = "", type = "";
	Student* studentCur = 0;
	Score* score = 0;
	schYear* sY = 0;
	time_t now = time(0);
	tm* rt = localtime(&now);
	ifstream fi;
	ofstream fo;
	fi.open("Settings.csv");
	if (fi.is_open() && !fi.eof()) {
		loadSettings(fi, sett);
		fi.close();
	}
	else {
		cout << "Can't load data of file Accounts.csv.\n";
		fi.clear();
	}
	fi.open("Accounts.csv");
	if (fi.is_open() && !fi.eof()) {
		loadAccountData(fi, account);
		fi.close();
	}
	else {
		cout << "Can't load data of file Accounts.csv.\n";
		fi.clear();
	}
	fi.open("Classes.csv");
	if (fi.is_open() && !fi.eof()) {
		loadClassData(fi,sY);
		fi.close();
	}
	else fi.clear();;
	fi.open("Semester.csv");
	if (fi.is_open() && !fi.eof()) {
		loadSemesterData(fi, semester, sSel);
		fi.close();
	}
	fi.open("StudentData.csv");
	if (fi.is_open() && !fi.eof()) {
		loadStudentCourseData(fi, data);
		fi.close();
	}
	else fi.clear();
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
			if (type == "Student") {
				getStudentData(sY, studentCur, data, dSel, accountCur);
			}
			if (accountCur != "") {
				int choose1 = 0;
				do {
					bool check = 1;
					system("cls");
					cout << "1. View profile.\n";
					cout << "2. Change password.\n";
					cout << "3. Log out.\n";
					if (type == "Staff") {
						cout << "4. View list of classes.\n";
						cout << "5. View list of students in a class.\n";
						cout << "6. View list of courses.\n";
						cout << "7. View list of students in a course.\n";
						if (sett && checkBeginTime(sett->ys, sett->ye, rt)) {
							cout << "8. Create a year school.\n";
							cout << "9. Create 1st class.\n";
							cout << "10. Add new 1st year students to classes.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose1 > 7 && choose1 < 11) check = 0;
							switch (choose1) {
							case 8:
								createSchoolYear(sY);
								break;
							case 9:
								create1stClass(sY);
								break;
							case 10:
								add1stStudentsTo1stClasses(fi, sY, account, data);
								break;
							}
						}
						else if (sett && (checkBeginTime(sett->s1, sett->e1, rt) || checkBeginTime(sett->s2, sett->e2, rt) || checkBeginTime(sett->s3, sett->e3, rt))) {
							cout << "8. Create a semester.\n";
							cout << "9. Create a course registration session.\n";
							cout << "10. Add a course to the semester.\n";
							cout << "11. View list of courses.\n";
							cout << "12. Update course information.\n";
							cout << "13. Delete a course.\n";
							cout << "14. Change semester.\n";
							if (sSel) cout << "Current semester: " << sSel->name << "-" << sSel->schoolYear << endl;
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose1 > 7 && choose1 < 15) check = 0;
							switch (choose1) {
							case 8:
								createSemester(semester, sSel);
								break;
							case 9:
								createRegSession(sSel);
								break;
							case 10:
								addCourseToSemester(sSel);
								break;
							case 11:
								if (!sSel) cout << "You have to create a semester first!\n";
								else viewListCourses(sSel->course);
								break;
							case 12:
								if (!sSel) cout << "You have to create a semester first!\n";
								updateCourseInfo(sSel->course);
								break;
							case 13:
								if (!sSel) cout << "You have to create a semester first!\n";
								deleteCourse(sSel->course);
								break;
							case 14:
								if (!sSel) cout << "You have to create a semester first!\n";
								changeSemester(semester, sSel);
								break;
							}
						}
						else if (sSel && checkEndTime(sSel->end, rt)) {
							cout << "8. Export list of students in a course to a CSV file.\n";
							cout << "9. Import the scoreboard of a course.\n";
							cout << "10. View the scoreboard of a course.\n";
							cout << "11. Update a student result.\n";
							cout << "12. View the scoreboard of a class.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose1 > 7 && choose1 < 13) check = 0;
							switch (choose1) {
							case 8:
								exportListStudent(fo, sSel->course);
								break;
							case 9:
								importScoreboard(fi, sSel->course, score);
								break;
							case 10:
								viewCourseScoreboard(sSel->course);
								break;
							case 11:
								updateStudentResult(sSel->course);
								break;
							case 12:
								viewClassScoreboard(sY, data, sSel->course);
								break;
							}
						}
						else {
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
						}
						if (choose1 > 3 && choose1 < 8) check = 0;
						switch (choose1) {
						case 4:
							viewListClasses(sY);
							system("pause");
							break;
						case 5:
							viewListStudentInClass(sY); break;
						case 6:
							if (!sSel) cout << "You have to create a semester first!\n";
							else viewListCourses(sSel->course);
							system("pause");
							break;
						case 7:
							if (!sSel) cout << "You have to create a semester first!\n";
							else viewListStudentInCourse(sSel->course);
							system("pause");
							break;
						}
					}
					else {
						if (sSel && checkRegTime(sSel->regStart, sSel->regEnd, rt)) {
							cout << "4. Enroll a course.\n";
							cout << "5. View list of enrolled course.\n";
							cout << "6. Remove a course from enrolled list.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose1 > 3 && choose1 < 7) check = 0;
							switch (choose1) {
							case 4: 
								enrollCourse(data, sSel->course, studentCur); break;
							case 5:
								viewListEnrolledCourses(data); break;
							case 6:
								removeEnrolledCourse(data, sSel->course); break;
							}
						}
						else if (sSel && checkEndTime(sSel->regEnd, rt)) {
							cout << "4. View list of courses in this semester.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose == 4) {
								viewListStudentCourses(sSel->course);
								check = 0;
							}
						}
						else if (sSel && checkEndTime(sSel->end, rt)) {
							cout << "4. View list of my courses.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							if (choose1 == 4) {
								viewListStudentCourses(dSel->course);
								check = 0;
							}
						}
					}
					switch (choose1) {
					case 1:
						viewProfile(sY, accountCur, type);
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
					default:
						if (check) {
							cout << "Invalid selection!\n";
							system("pause");
						}
						break;
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
	fo.open("Semester.csv");
	if (fo.is_open()) {
		saveSemesterData(fo, semester, sSel);
		fo.close();
	}
	else cout << "Can't save the semester data!\n";
	fo.open("StudentData.csv");
	if (fo.is_open()) {
		saveStudentCourseData(fo, data);
		fo.close();
	}
	else cout << "Can't save the student data!\n";

	fo.open("Classes.csv", ios::out);
	if (fo.is_open()) {
		saveClassData(fo, sY);
		fo.close();
	}
	else cout << "Can't save the course data of student!\n";
	fo.open("Accounts.csv");
	if (fo.is_open()) {
		saveAccountData(fo, account);
		fo.close();
	}
	else cout << "Can't save the account data!\n";
	studentCur = 0;
	deleteSemesterData(semester, sSel);
	deleteAccountData(account);
	deleteStudentCourseData(data);
	deleteClassData(sY);
	delete sett;
	return 0;
}