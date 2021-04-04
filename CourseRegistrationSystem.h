#ifndef _CourseRegistrationSystem_
#define _CourseRegistrationSystem_

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct ClassNode {
	ClassNode* ClassID, *Next;
	char ID[10];
};

struct StudentList {
	int STT;
	string Name;
	char MSSV[10], DateOfBirth[11], sex[7], ClassName[10];
};

void createClasses(ClassNode*& ClassList, int& classes);

#endif;