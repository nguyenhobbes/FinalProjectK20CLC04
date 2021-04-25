#include "CourseRegistrationSystem.h"

// <--------- Account Setting --------->

// For Login System

void logIn(Account* account, string& accountCur, string& type) {
	system("cls");
	Account* tmp = account;
	string username, password;
	cin.ignore();
	cout << "Input Username: ";
	getline(cin, username);
	cout << "Input password: ";
	getline(cin, password);
	system("cls");
	while (tmp) {
		if (tmp->username == username) {
			if (tmp->password == password) {
				accountCur = username;
				type = tmp->type;
				cout << "Logged in!\n";
			}
			break;
		}
		tmp = tmp->aNext;
	}
	if (!tmp || tmp->password != password) cout << "Invalid login.\n";
	system("pause");
}

void changePassword(ofstream& fo, Account* account, string accountCur) {
	Account* tmp = account;
	if (account->username != accountCur)
		account = account->aNext;
	do {
		string password;
		cout << "Input current password:\n";
		cin >> password;
		if (account->password == password)
		{
			cout << "Input new password:\n";
			cin >> password;
			string newpassword;
			cout << "Reinput new password:\n";
			cin >> newpassword;
			if (password == newpassword) {
				account->password = newpassword;
				system("cls");
				cout << "Password's changed!\n";
				break;
			}
			else {
				system("cls");
				cout << "2 passwords are not match.\n";
			}
		}
		else {
			system("cls");
			cout << "Wrong password!\n";
		}
	} while (1);
	while (tmp) {
		fo << tmp->username << ',' << tmp->password;
		if (tmp->aNext) fo << endl;
		tmp = tmp->aNext;
	}

}

void saveAccountData(ofstream& fo, Account* account) {
	while (account) {
		fo << account->username << ',' << account->password << ',' << account->type << endl;
		account = account->aNext;
	}
}

void logOut(string& accountCur) {
	accountCur = "";
}

void deleteAccountData(Account*& account) {
	while (account)
	{
		Account* tmp = account;
		account = account->aNext;
		delete tmp;
	}
}

void viewProfile(Class* c, string accountCur, string type) {
	if (type == "Staff") {
		cout << "Name: " << accountCur << ".\n";
	}
	else {
		while (c) {
			Student* student = c->stu;
			while (student) {
				if (student->studentID == accountCur) {
					cout << "-----------------------------\n";
					cout << "Name: " << student->firstname << ' ' << student->lastname << ".\n";
					cout << "Gender: " << student->gender << ".\n";
					cout << "Date of birth: " << student->dob << ".\n";
					cout << "Student ID: " << student->studentID << ".\n";
					cout << "Social ID: " << student->socialID << ".\n";
					cout << "-----------------------------\n";
					return;
				}
				student = student->sNext;
			}
			c = c->cNext;
		}
	}
}

// <--------- Account Setting --------->

