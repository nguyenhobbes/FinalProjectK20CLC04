#include "CourseRegistrationSystem.h"

// <--------- Account Setting --------->

// For Login System

void logIn(Account* account, string& accountCur, string& type) {
	Account* tmp;
	string username, password;
	do {
		tmp = account;
		cout << "Input Username:\n";
		getline(cin, username);
		cout << "Input password:\n";
		getline(cin, password);
		while (tmp) {
			if (tmp->username == username) {
				if (tmp->password == password) {
					accountCur = username;
					type = tmp->type;
					system("cls");
					cout << "Logged in!\n";
					return;
				}
				break;
			}
			tmp = tmp->aNext;
		}
		system("cls");
		cout << "Invalid login, please try again.\n";
	} while (tmp == 0 || tmp->password != password);
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

// <--------- Account Setting --------->

