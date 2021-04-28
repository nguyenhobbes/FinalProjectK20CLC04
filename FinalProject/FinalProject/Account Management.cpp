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
			while (tmp) {
				fo << tmp->username << ',' << tmp->password << ',' << tmp->type;
				tmp = tmp->aNext;
				if (tmp) fo << endl;
			}
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
}

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

void saveAccountData(ofstream& fo, Account* account) {
	while (account) {
		fo << account->username << ',' << account->password << ',' << account->type;
		account = account->aNext;
		if (account) fo << endl;
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
	system("cls");
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
					system("pause");
					return;
				}
				student = student->sNext;
			}
			c = c->cNext;
		}
	}
}

// <--------- Account Setting --------->

