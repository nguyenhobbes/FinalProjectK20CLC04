#include  "CourseRegistrationSystem.h"

void createClasses(ClassNode*& ClassList, int& classes) {
	ifstream classID("CLASS_ID.txt");
	if (!classID.is_open()) {
		cout << "Can not load file CLASS_ID" << endl;
	}
	else {
		classID >> classes;
		ClassList = new ClassNode;
		ClassNode* Cur = ClassList;
		classID >> Cur->ID;
		Cur->Next = nullptr;
		for (int i = 0; i < classes - 1; i++) {
			Cur->Next = new ClassNode;
			Cur = Cur->Next;
			classID >> Cur->ID;
			Cur->Next = nullptr;
		}
	}
	classID.close();
}

void importFileStudent(ClassNode*& ClassList, char FileStudent[], int& classes, int& ClassNumber) {
	createClasses(ClassList, classes);
	ClassNode* Cur = ClassList;
	for (int i = 0; i < ClassNumber - 1; i++) {
		Cur = Cur->Next;
	}
	strcpy(FileStudent, Cur->ID);
	strcat(FileStudent, "txt");
}

void addStudentsToClasses(ClassNode*& ClassList, StudentList*& Student, int& studentNumber, char FileStudent[]) {
	ClassNode* Cur = ClassList;
	fstream student(FileStudent);
	if (!student.is_open()) {
		studentNumber = 0;
	}
	else {
		student >> studentNumber;
		Student = new StudentList[studentNumber];
		for (int i = 0; i < studentNumber; i++) {
			student >> Student[i].STT;
			student >> Student[i].MSSV;
			student.ignore();
			getline(student, Student[i].Name);
			student >> Student[i].DateOfBirth;
			student >> Student[i].sex;
		}
	}
}

void displayStudentList(StudentList*& Student, int& studentNumber) {
	cout << "List of students: " << endl;
	for (int i = 0; i < studentNumber; i++) {
		cout << Student[i].STT << "\t" << Student[i].MSSV << "\t" << Student[i].Name << "\t" << Student[i].DateOfBirth << "\t" << Student[i].sex << endl;
	}
}

void displayClassesList(ClassNode*& ClassList, int& classes) {
	cout << "List of classes: " << endl;
	for (int i = 0; i < classes; i++) {
		cout << i + 1 << ". " << ClassList->ID << endl;
		ClassList = ClassList->Next;
	}
	cout << endl;
}

void deleteClassesList(ClassNode*& ClassList) {
	ClassNode* Cur = ClassList;
	while (ClassList != nullptr) {
		ClassList = ClassList->Next;
		delete Cur;
		Cur = ClassList;
	}
}

