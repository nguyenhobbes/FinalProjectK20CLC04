#include "CourseRegistrationSystem.h"

int main() {
	Account* account = 0;
	Class* c = 0;
	Semester* semester = 0, * sSel = 0;
	Data* data = 0, *dSel = 0;
	string accountCur = "", type = "";
	string schoolYear = "", cl = "";
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
			if (type == "Student") {
				getStudentData(c, studentCur, data, dSel, accountCur);
			}
			if (accountCur != "") {
				int choose1 = 0;
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
							cout << "Enter the selection: ";
							cin >> choose1;
							switch (choose1) {
							case 8:
								createSchoolYear(schoolYear);
								break;
							case 9:
								create1stClass(cl);
								break;
							case 10:
								if (schoolYear == "") cout << "You have to create school year first!\n";
								else if (cl == "") cout << "You have to create the class name first!\n";
								else {
									add1stStudentsTo1stClasses(fi, schoolYear, cl, c, account, data);
								}
								break;
							}
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
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
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
							switch (choose1) {
							case 1:
								exportListStudent(fo, sSel->course);
								break;
							case 2:
								importScoreboard(fi, sSel->course, score);
								break;
							case 3:
								viewCourseScoreboard(sSel->course);
								break;
							case 4:
								updateStudentResult(sSel->course);
								break;
							case 5:
								viewClassScoreboard(c, data, sSel->course);
								break;
							}
						}
						else {
							cout << "Enter the selection: ";
							cin >> choose1;
							system("cls");
						}
						switch (choose1) {
						case 4:
							viewListClasses(c);
							system("pause");
							break;
						case 5:
							viewListStudentInClass(c); break;
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
							if (choose == 4) viewListStudentCourses(sSel->course);
						}
						else if (sSel && checkEndTime(sSel->end, rt)) {
							cout << "4. View list of my courses.\n";
							cout << "Enter the selection: ";
							cin >> choose1;
							if (choose1 == 4) {
								viewListStudentCourses(dSel->course);
							}
						}
					}
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
					default:
						cout << "Invalid selection!\n";
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

	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
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
	deleteClassData(c);
	return 0;
}