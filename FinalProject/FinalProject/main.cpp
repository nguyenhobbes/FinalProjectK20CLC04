#include "CourseRegistrationSystem.h"

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 150;
	sizeOfBuff.Y = 100;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 850, 600, SWP_SHOWWINDOW | SWP_NOMOVE); }
	changeColor(11);
	loadingScreen();

	Setting* sett = 0;
	Account* account = 0;
	Semester* semester = 0, * sSel = 0;
	Data* data = 0, *dSel = 0;
	string accountCur = "", type = "";
	Student* studentCur = 0;
	schYear* sY = 0;
	time_t now = time(0);
	tm* rt = localtime(&now);
	ifstream fi;
	ofstream fo;
	Score* score;
	bool imported = 0, updated = 0;
	fi.open("Settings.csv");
	if (fi.is_open()) {
		loadSettings(fi, sett);
		fi.close();
	}
	else {
		cout << "Can't load data of file Accounts.csv.\n";
		fi.clear();
	}
	fi.open("Accounts.csv");
	if (fi.is_open()) {
		loadAccountData(fi, account);
		fi.close();
	}
	else {
		cout << "Can't load data of file Accounts.csv.\n";
		fi.clear();
	}
	fi.open("Classes.csv");
	if (fi.is_open()) {
		loadClassData(fi,sY);
		fi.close();
	}
	else fi.clear();;
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
	else fi.clear();
	
	if (sSel && sett && sett->p){
		if (checkBeginTime(sSel->start, sSel->end, rt)) {
			sett->p = 0;
			fo.open("Settings.csv");
			if (fo.is_open()) {
				fo << "Time,Start,End\n";
				fo << "School year," << sett->ys << ',' << sett->ye << endl;
				fo << "Semester 1," << sett->s1 << ',' << sett->e1 << endl;
				fo << "Semester 2," << sett->s2 << ',' << sett->e2 << endl;
				fo << "Semester 3," << sett->s3 << ',' << sett->e3 << endl;
				fo << "Publish," << sett->p;
			}
			else fo.clear();
		}
		else importScoreboard(fi, sSel->course);
	}
	int choose = 0;
	do {
		choose = 0;
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
					choose1 = 3;
					bool check = 1;
					system("cls");
					gotoxy(10, 2);
					cout << "1. View profile.\n";
					gotoxy(10, 3);
					cout << "2. Change password.\n";
					gotoxy(10, 4);
					cout << "3. Log out.\n";
					if (type == "Staff") {
						gotoxy(10, 5);
						cout << "4. View list of classes.\n";
						gotoxy(10, 6);
						cout << "5. View list of students in a class.\n";
						gotoxy(10, 7);
						cout << "6. View list of courses.\n";
						gotoxy(10, 8);
						cout << "7. View list of students in a course.\n";
						if (sett && checkBeginTime(sett->ys, sett->ye, rt)) {
							gotoxy(10, 9);
							cout << "8. Create a year school.\n";
							gotoxy(10, 10);
							cout << "9. Create 1st class.\n";
							gotoxy(10, 11);
							cout << "10. Add new 1st year students to classes.\n";
							gotoxy(10, 12);
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
							gotoxy(10, 9);
							cout << "8. Create a semester.\n";
							gotoxy(10, 10);
							cout << "9. Create a course registration session.\n";
							gotoxy(10, 11);
							cout << "10. Add a course to the semester.\n";
							gotoxy(10, 12);
							cout << "11. Update course information.\n";
							gotoxy(10, 13);
							cout << "12. Delete a course.\n";
							gotoxy(10, 14);
							cout << "13. Change semester.\n";
							gotoxy(10, 15);
							if (sSel) cout << "Current semester: " << sSel->name << "/" << sSel->schoolYear << endl;
							else cout << "Current semester: null.\n";
							gotoxy(10, 16);
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
								if (!sSel) {
									cout << "You have to create a semester first!\n";
									system("pause");
								}
								else updateCourseInfo(sSel->course);
								
								break;
							case 12:
								if (!sSel) cout << "You have to create a semester first!\n";
								else deleteCourse(sSel->course);
								system("pause");
								break;
							case 13:
								if (!sSel) cout << "You have to create a semester first!\n";
								else changeSemester(semester, sSel);
								break;
							}
						}
						else if (sSel && checkEndTime(sSel->end, rt)) {
							gotoxy(10, 9);
							cout << "8. Export list of students in a course to a CSV file.\n";
							gotoxy(10, 10);
							cout << "9. Import the scoreboard of a course.\n";
							gotoxy(10, 11);
							cout << "10. View the scoreboard of a course.\n";
							gotoxy(10, 12);
							cout << "11. Update a student result.\n";
							gotoxy(10, 13);
							cout << "12. View the scoreboard of a class.\n";
							gotoxy(10, 14);
							cout << "13. Publish the scoreboard.";
							gotoxy(10, 15);
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (choose1 > 7 && choose1 < 13) check = 0;
							switch (choose1) {
							case 8:
								exportListStudent(fo, sSel->course);
								break;
							case 9:
								if (imported) {
									cout << "You had been imported the scoreboard!\n";
									system("pause");
								}
								else {
									imported = 1;
									importScoreboard(fi, sSel->course);
									cout << "Imported score successfully!\n";
									system("pause");
								}
								break;
							case 10:
							{
								Course* cTmp = sSel->course;
								viewListCourses(cTmp);
								string s;
								cout << "Enter the name of course you want to see: ";
								cin >> s;
								while (cTmp && cTmp->name != s) {
									cTmp = cTmp->cNext;
								}
								if (!cTmp) cout << "The course is not exist!\n";
								else viewCourseScoreboard(cTmp);
								system("pause");
								break;
							}
							case 11:
								updateStudentResult(sSel->course);
								updated = 1;
								break;
							case 12:
								viewClassScoreboard(sY, data, sSel->course);
								break;
							case 13:
								if (!sett) {
									cout << "Error!\n";
									break;
								}
								sett->p = 1;
								fo.open("Settings.csv");
								if (fo.is_open()) {
									fo << "Time,Start,End\n";
									fo << "School year," << sett->ys << ',' << sett->ye << endl;
									fo << "Semester 1," << sett->s1 << ',' << sett->e1 << endl;
									fo << "Semester 2," << sett->s2 << ',' << sett->e2 << endl;
									fo << "Semester 3," << sett->s3 << ',' << sett->e3 << endl;
									fo << "Publish," << sett->p;
								}
								else fo.clear();
								cout << "Published successfully!\n";
								system("pause");
								check = 0;
								break;
							}
						}
						else {
							gotoxy(10, 9);
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
					int z = 4;
						if (sSel && checkRegTime(sSel->regStart, sSel->regEnd, rt)) {
							z = 8;
							gotoxy(10, 5);
							cout << "4. Enroll a course.\n";
							gotoxy(10, 6);
							cout << "5. View list of enrolled course.\n";
							gotoxy(10, 7);
							cout << "6. Remove a course from enrolled list.\n";
							if (sett && sett->p) {
								gotoxy(10, z);
								cout << "7. View scoreboard.\n";
								z++;
							}
							gotoxy(10, z);
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (sett && sett->p && choose1 == 7) {
								viewScoreboard(sSel->course);
								check = 0;
							}
							if (choose1 > 3 && choose1 < 7) check = 0;
							switch (choose1) {
							case 4: 
								enrollCourse(dSel, sSel->course, studentCur); break;
							case 5:
								viewListEnrolledCourses(dSel, sSel->course);
								system("pause");
								break;
							case 6:
								removeEnrolledCourse(dSel, sSel->course); break;
							}
						}
						else if (sSel && checkEndTime(sSel->regEnd, rt)) {
							z = 6;
							gotoxy(10, 5);
							cout << "4. View list of courses in this semester.\n";
							if (sett && sett->p) {
								gotoxy(10, z);
								cout << "5. View scoreboard.\n";
								z++;
							}
							gotoxy(10, z);
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (sett && sett->p && choose1 == 5) {
								viewScoreboard(sSel->course);
								check = 0;
							}
							if (choose1 == 4) {
								viewListCoursesInSemester(dSel, sSel->course);
								check = 0;
							}
						}
						else {
							z = 5;
							if (sett && sett->p) {
								gotoxy(10, z);
								cout << "4. View scoreboard.\n";
								z++;
							}
							gotoxy(10, z);
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
							if (sett && sett->p && choose1 == 4) {
								viewScoreboard(sSel->course);
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
	if (sSel && updated) saveStudentResult(fo, sSel->course);
	deleteSemesterData(semester, sSel);
	deleteAccountData(account);
	deleteStudentCourseData(data);
	deleteClassData(sY);
	delete sett;
	return 0;
}