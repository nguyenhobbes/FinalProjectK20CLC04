#include "CourseRegistrationSystem.h"

int main() {
	Account* account = 0;
	Student* student = 0;
	Class* c = 0;
	string accountCur = "1", type = "Staff";
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
	else cout << "Can't open file Classes.csv.\n";
	/* ------------ Menu
	int choose = 0;
	do {
		cout << "Log in\n";
		cout << "Choose select: ";
		cin >> choose;
		switch (choose) {
		case 1:
			logIn(account, accountCur, type);
			break;
		case 0:
			break;
		}
	} while (choose == 0);
	*/
	/*  ----------- Change Password
	fo.open("Accounts.csv");
	if (fo.is_open()) {
		changePassword(fo, account, accountCur);
		fo.close();
	}
	else cout << "Can't open file Accounts.csv.\n";
	*/

	string schoolYear = "", cl = "";
	createSchoolYear(schoolYear);
	create1stClass(cl);
	cout << "Input csv file name. Ex: student.csv\n";
	string fname = "";
	cin >> fname;
	fi.open(fname);
	if (fi.is_open()) {
		add1stStudentsTo1stClasses(fi, schoolYear, cl, c);
		fi.close();
	}
	else cout << "Can't open file Classes.csv.\n";
	fo.open("Classes.csv");
	if (fo.is_open()) {
		saveClassData(fo, c);
		fo.close();
	}
	else cout << "Can't open file Classes.csv.\n";
	deleteAccountData(account);
	deleteStudentData(student);
	deleteClassData(c);
	return 0;
}