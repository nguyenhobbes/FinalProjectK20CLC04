#include "moodle.h"

HANDLE	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

student::student()
{
	no = 0;
	id = 1;
	gender = 0;		//0: Male, 1: Female, */-1: Other/* :d	
	dob.dd = 1;
	dob.mm = 1;
	dob.yyyy = 0;

	// Struct student lưu trữ trong course
	midterm = 0;			// Điểm giữa kỳ
	final_point = 0;			// Điểm cuối kỳ
	lab = 0;			// Điểm thực hành
	bonus = 0;			// Điểm cộng
	gpa = 0;			// Điểm trung bình (Nếu có)
	n_date = 0;
	attendance = NULL;	// điểm danh hs trong một khóa học, dùng kèm trong course date
	//courses			= NULL;
}
student::~student()
{
	if (attendance != NULL)
		delete[] attendance;

	/*if (courses != NULL)
		delete[] courses;*/
}
course::course()
{
	start_date.dd = 1;
	start_date.mm = 1;
	start_date.yyyy = 2018;
	end_date.dd = 2;
	end_date.mm = 1;
	end_date.yyyy = 2018;
	course_date = NULL;
	n_course_date = 0;
	n_student = 0;
	for (int i = 0; i < 7; i++)
	{
		dow[i] = false;
		start_hour[i].hh = 0;
		start_hour[i].mm = 0;
		end_hour[i].hh = 0;
		end_hour[i].mm = 0;
	}
}
course::~course()
{
	if (course_date != NULL)
		delete[] course_date;
}
term::term()
{
	no = 0;		// HK1, HK2. HK3 - (Autumn, Spring, Summer)
	n_course = 0;		// SL course trong một term
	courses = NULL;
}
term::~term()
{
	if (courses != NULL)
		delete[] courses;
}
academic_year::academic_year()
{
	start = 0;				//Năm bắt đầu năm học
	end = 0;
	terms = NULL;		// i = 0: HK1, i=1: HK2, i =2: HK3
	n_term = 0;				// Số HK có trong năm học
}
academic_year::~academic_year()
{
	if (terms != NULL)
		delete[] terms;
}
lecturer::lecturer()
{
	n_year = 0;
	years = NULL;
}
lecturer::~lecturer()
{
	if (years != NULL)
		delete[] years;
}
studentID::studentID()
{
	id = 0;
}

template <class T> void	push_back(T* &arr, int &n, T &item)
{
	// Thêm phần tử vào cuối mảng động
	// Sửa n (số phần tử trong mảng)

	if (arr == NULL)
	{
		arr = new T[1];
		arr[0] = item;
		n++;
		return;
	}
	T* new_arr = new T[(n + 1)];
	for (int i = 0; i < n; i++)
	{
		new_arr[i] = arr[i];
	}
	new_arr[n] = item;
	delete[] arr;
	arr = new_arr;
	n++;
}
template <class T> void	add_back(T* &arr, int n, T &item)
{
	// Thêm phần tử cuối vào mảng
	// KHÔNG SỬA n
	if (arr == NULL)
	{
		arr = new T[1];
		arr[0] = item;
		return;
	}
	T* new_arr = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		new_arr[i] = arr[i];
	}
	new_arr[n] = item;
	delete[] arr;
	arr = new_arr;
}
template <class T> void	moreSize(T* &arr, int &n)
{
	if (arr == NULL)
	{
		arr = new T[1];
		n++;
	}
	else
	{
		T* new_arr = new T[n + 1];
		for (int i = 0; i < n; i++)
		{
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
		n++;
	}
}

void	strLwr(string &s)
{
	for (size_t i = 0; i < s.size(); ++i)
	{
		char character = tolower(s[i]);
		s[i] = character;
	}
}
void	strUpr(string &s)
{
	for (size_t i = 0; i < s.size(); ++i)
	{
		char character = toupper(s[i]);
		s[i] = character;
	}
}

void	textColor(int x)
{
	SetConsoleTextAttribute(hStdout, x);
}
bool	yesNoAns()
{
	// Hàm trả về false nếu nhập vào "no", "n", "khong", "ko", "k", "non", "0", "o", "null"
	// Còn lại trả về true
	string		ans;
	//cin.ignore();
	textColor(Input__);
	getline(cin, ans, '\n');
	strLwr(ans);
	string	yes[] = { "yes", "ys", "y", "co", "c", "oui", "1" , "vang", "tiep tuc", "tiep" , "continue", "i love you" ,
		"si", "hello", "haii", "ok" , "co minh xinh dep", "co tu dep xiu", "tuonglaituoisang" };
	string	no[] = { "no", "n", "khong", "ko", "k", "non", "0", "o", "null" , "nope" , "dep",
		"oh no", "shut up", "iie", "del", "mr.thanh dep trai" ,"ktlt so easy", "1+1=3", "wt" };
	int		i = 0,
		len = 19;
	while (true)
	{
		if (ans.find("?") != string::npos)
		{
			textColor(Notice);
			cout << "\tValid Commands for Yes and No: " << endl;
			textColor(NormalT); cout << "\t"; textColor(TitleBoard);
			cout << setfill('*') << setw(46) << "*" << setfill(' ') << endl;
			textColor(NormalT);  cout << "\t"; textColor(TitleBoard);
			cout << "|  " << setw(19) << left << "YES" << "|  " << setw(20) << left << "NO" << "|" << endl;
			textColor(NormalT); cout << "\t"; textColor(TitleBoard);
			cout << "|" << setfill('-') << setw(44) << "-" << "|" << setfill(' ') << endl;
			for (int i = 0; i < len; i++)
			{
				textColor(NormalT); cout << "\t"; textColor(InBoard);
				cout << "|  " << setw(19) << left << yes[i] << "|  " << setw(20) << left << no[i] << "|" << endl;
			}
			textColor(NormalT); cout << "\t"; textColor(InBoard);
			cout << setfill('*') << setw(46) << "*" << setfill(' ') << endl;
			textColor(NormalT);
		}
		else
		{
			for (i = 0; i < len; i++)
			{
				if (ans == no[i])
				{
					textColor(NormalT);
					return false;
				}
				else
				{
					if (ans == yes[i])
					{
						textColor(NormalT);
						return true;
					}
				}
			}
		}
		textColor(NormalT);
		cout << "\t>>(Yes/No/?): ";
		textColor(Input__);
		getline(cin, ans, '\n');
		strLwr(ans);
		textColor(NormalT);
	}
}
bool	checkValidDate(date d)
{
	//Kiểm tra tính hợp lệ của định dạng struct date
	if (d.dd > 31 || d.dd <= 0)
		return false;
	if (d.mm > 12 || d.mm <= 0)
		return false;
	switch (d.mm)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if (d.dd < 1 || d.dd > 31)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
	case 4:
	case 6:

	case 9:
	case 11:
	{

		if (d.dd < 1 || d.dd>30)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
	case 2:
	{
		bool isLeap = false;
		if (d.yyyy % 4 == 0 && d.yyyy % 100 != 0 || d.yyyy % 400 == 0)
			isLeap = true;
		if (isLeap)
		{
			if (d.dd > 29)
				return false;
		}
		else
		{
			if (d.dd > 28)
				return false;
		}
	}
	}
	return true;

}
int		askCommand(int lastCommand)
{
	// Hàm hỏi người dùng nhập số lệnh để thực thi chương trình
	// 1. <Lệnh>
	// 2. <Lệnh>
	// ...
	// [lastCommand]. <Lệnh>
	// >> /*Người dùng nhập lệnh để thực thi*/
	// Trả về giá trị int là số lệnh hợp lệ
	// Lặp cho đến khi nào người dùng nhập hợp lệ thì thôi

	int command;
	while (true)
	{
		textColor(NormalT);
		cout << "    >> ";
		getNum(command);
		if (command >= 1 && command <= lastCommand)
		{
			textColor(NormalT);
			return command;
		}
		textColor(Notice);
		cout << "    !Invalid command." << endl;
	}
	textColor(NormalT);
}
int		askCommand(int firstCommand, int lastCommand)
{
	int command;
	while (true)
	{
		textColor(NormalT);
		cout << "\t>> ";
		getNum(command);
		if (command >= firstCommand && command <= lastCommand)
		{
			textColor(NormalT);
			return command;
		}
		textColor(Notice);
		cout << "    !Invalid command." << endl;
	}
	textColor(NormalT);
}
int		askManyCommands(int first_command, int last_command, int* &selected_command)
{
	int		n = 0;
	do
	{
		int		command;
		textColor(NormalT);
		cout << "\t>> ";
		string		s;
		stringstream selected;
		textColor(Input__);
		getline(cin, s, '\n');
		selected << s;
		while (!selected.eof())
		{
			string temp;
			selected >> temp;
			if (stringstream(temp) >> command)
			{
				if (command >= first_command && command <= last_command)
					push_back(selected_command, n, command);
			}
		}
		sortAscending(selected_command, n);
		n = removeDuplicates(selected_command, n);
		sortAscending(selected_command, n);
		if (n == 0)
		{
			textColor(Notice);
			cout << "    You did not choose any valid command, please choose again!!" << endl;
			continue;
		}
		textColor(WOInfo);
		cout << "    You selected command(s): ";
		textColor(Input__);
		for (int i = 0; i < n; i++)
		{
			cout << selected_command[i] << " ";
		}
		cout << endl;
		textColor(NormalT);
		break;
	} while (true);
	textColor(NormalT);
	return n;
}
string	intToMonth(int n)
{
	switch (n)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "";
	}
}
int		monthToString(string s)
{
	string month[] = { "january", "febuary", "march", "april", "may", "june",
		"july", "august", "september", "october", "november", "december" };
	strLwr(s);
	for (int i = 0; i < 12; i++)
	{
		if (month[i] == s)
			return i + 1;
	}
	return 0;
}
int		monthToSemesterInt(int mm)
{
	if ((mm == 1) || (mm == 2) || (mm == 3) || (mm == 4))
		return 2;
	if ((mm == 5) || (mm == 6) || (mm == 7) || (mm == 8))
		return 3;
	if ((mm == 12) || (mm == 9) || (mm == 10) || (mm == 11))
		return 1;
	return 0;
}
string	monthToSemesterString(int mm)
{
	if ((mm == 1) || (mm == 2) || (mm == 3) || (mm == 4))
		return "2nd";
	if ((mm == 5) || (mm == 6) || (mm == 7) || (mm == 8))
		return  "3rd";
	if ((mm == 12) || (mm == 9) || (mm == 10) || (mm == 11))
		return "1st";
	return "";
}
string	dateToPass(date d)
{
	string default_password;
	if (d.dd < 10)
	{
		//trường hợp ngày nhỏ hơn 10 thì thêm '0' vào trước
		default_password += "0";
	}
	default_password += to_string(d.dd);

	if (d.mm < 10)
		default_password += "0";
	default_password += to_string(d.mm) + to_string(d.yyyy);

	return sha256(default_password);
}
string dateToPassNotEcrypted(date d)
{
	string default_password;
	if (d.dd < 10)
	{
		//trường hợp ngày nhỏ hơn 10 thì thêm '0' vào trước
		default_password += "0";
	}
	default_password += to_string(d.dd);

	if (d.mm < 10)
		default_password += "0";
	default_password += to_string(d.mm) + to_string(d.yyyy);
	return default_password;
}
int		getCurrentSemester()
{
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	return monthToSemesterInt(now.tm_mon + 1);
}
int		changeStartYearOfACourseToMatchWithNewAcademicYear(int old_month, int new_start_year)
{
	int sem = monthToSemesterInt(old_month);
	if (sem == 2 || sem == 3)
		return (new_start_year + 1);
	return new_start_year;
}
int		monthToAcademicYear(int mm, int start_year)
{
	// Ví dụ năm học 2018 - 2019
	// Nếu tháng 8 -> Học kỳ 1 -> Trả về 2018
	// Nếu tháng 5 -> Học kỳ 3 -> Trả về 2019
	int sem = monthToSemesterInt(mm);
	if (sem == 2 || sem == 3)
		return start_year - 1;
	return start_year;
}
int		semesterToAcademicYear(int sem, int start_year)
{
	// Ví dụ năm học 2018 - 2019
	// Học kỳ 1 -> Trả về 2018
	// Học kỳ 3 -> Trả về 2019
	if (sem == 2 || sem == 3)
		return start_year + 1;
	return start_year;
}
int		getCurrentAcademicYear()
{
	// Lấy thời gian khóa học hiện tại
	// Trả về năm học bắt đầu

	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	int sem = getCurrentSemester();
	if (sem == 2 || sem == 3)
		return (now.tm_year + 1900 - 1);
	return (now.tm_year + 1900 - 1);
}
template <class T> void	showStudentList(T* &s, int n, bool is_showing_class)
{
	textColor(NormalT);
	cout << "\t    ";
	textColor(TitleBoard);
	cout << setw(7) << left << "|  No" << "|  "
		<< setw(10) << left << "   ID" << "|  "
		<< setw(28) << left << "Lastname" << "|  "
		<< setw(15) << left << "Firstname" << "|  "
		<< setw(8) << left << "Class" << "|" << endl;
	textColor(NormalT);
	cout << "\t    ";
	textColor(TitleBoard);
	cout << "|" << setfill('-')			// set fill bằng ký tự '-' thay vì ' '
		<< setw(79) << "-" << "|" << endl
		<< setfill(' ');
	for (int i = 0; i < n; i++)
	{
		textColor(NormalT);
		cout << "\t    ";
		textColor(InBoard);
		cout << "|  " << setw(4) << left << i + 1 << "|  "
			<< setw(10) << left << s[i].id << "|  "
			<< setw(28) << left << s[i].last_name << "|  "
			<< setw(15) << left << s[i].first_name << "|  "
			<< setw(8) << left << s[i].class_name << "|" << endl;
	}
	textColor(NormalT);
	cout << "\t    ";
	textColor(InBoard);
	cout << setfill('*')			// set fill bằng ký tự '-' thay vì ' '
		<< setw(81) << "*" << endl
		<< setfill(' ');
	textColor(NormalT);
}
void	showAllInfoStudentList(student* &s, int n, bool is_showing_pass)
{
	if (!is_showing_pass)
	{
		textColor(NormalT);
		cout << "    ";
		textColor(SpTitleFunc);
		cout << setfill('*') << setw(35) << "*"
			<< "This is student list of class " << s->class_name << setw(35) << "*" << setfill(' ') << endl;
		textColor(NormalT);
		cout << "    ";
	}
	else
	{
		textColor(SpTitleFunc);
		if (n != 0)
			cout << setfill('*') << setw(41) << "*"
			<< "This is student list of class " << s->class_name << setw(42) << "*" << setfill(' ') << endl;
	}
	textColor(TitleBoard);
	cout << "|  No  |"
		<< setw(12) << left << "     ID" << "|"
		<< setw(30) << left << "  Lastname" << "|"
		<< setw(13) << left << "  Firstname" << "|"
		<< setw(10) << left << "  Gender" << "|"
		<< setw(14) << left << "  DoB" << "|"
		<< setw(13) << left << "  Account" << "|";
	if (is_showing_pass)
	{
		cout << setw(12) << left << "  Password" << "|" << endl << "|"
			<< setfill('-')						// set fill bằng ký tự '-' thay vì ' '
			<< setw(117) << "-" << "|" << endl
			<< setfill(' ');
	}
	else
	{
		cout << endl;
		textColor(NormalT);
		cout << "    ";
		textColor(TitleBoard);
		cout << "|" << setfill('-')				// set fill bằng ký tự '-' thay vì ' '
			<< setw(104) << "-" << "|" << endl
			<< setfill(' ');
	}
	for (int i = 0; i < n; i++)
	{
		if (!is_showing_pass)
		{
			textColor(NormalT);
			cout << "    ";
		}
		textColor(InBoard);
		cout << "|  " << setw(4) << i + 1 << "|  "
			<< setw(10) << left << s[i].id << "|  "
			<< setw(28) << left << s[i].last_name << "|  "
			<< setw(11) << left << s[i].first_name << "|  ";
		if (s[i].gender == 0)
			cout << setw(8) << left << "Male" << "|  ";
		else
		{
			if (s[i].gender == 1)
				cout << setw(8) << left << "Female" << "|  ";
			else
				cout << setw(8) << left << "Other" << "|  ";
		}
		cout << setw(4) << s[i].dob.yyyy << "-" << setw(2) << s[i].dob.mm << "-" << setw(4) << left << s[i].dob.dd << "|  "
			<< setw(11) << left << s[i].account << "|";
		if (is_showing_pass)
			cout << "  " << setw(10) << dateToPassNotEcrypted(s[i].dob) << "|" << endl;
		else
			cout << endl;
	}
	if (is_showing_pass)
	{
		cout << setfill('*')						// set fill bằng ký tự '-' thay vì ' '
			<< setw(119) << "*" << endl
			<< setfill(' ');
	}
	else
	{
		textColor(NormalT);
		cout << "    ";
		textColor(InBoard);
		cout << setfill('*')				// set fill bằng ký tự '-' thay vì ' '
			<< setw(106) << "*" << endl
			<< setfill(' ');
	}
}
template <class t> void	pointColor(t point)
{
	if (point < 5)
		textColor(BelowP);
	if (point < 8 && point >= 5)
		textColor(MidP);
	if (point >= 8)
		textColor(AboveP);
}
template <class t> void	getNum(t &n)
{
	// Hàm cin >> temp;
	// Kiểm tra người dùng có nhập đúng kiểu dữ liệu không
	// Nếu không đúng kiểu dữ liệu thì lặp cho đến khi nào nhập đúng
	// Dùng cho kiểu dữ liệu số (int, char, float, double,..)

	while (true)
	{
		textColor(Input__);
		cin >> n;
		// Kiểm tra xem người dùng có nhập đúng kiểu dữ liệu hay không
		if (cin.fail())
		{
			cin.clear(); // Nếu nhập lỗi thì xóa trạng thái lỗi trong buffer
			cin.ignore(32767, '\n'); // Bỏ đi những kí tự không hợp lệ
			textColor(Notice);
			cout << "    Invalid input, please try again!" << endl;
			textColor(NormalT);
			cout << "\t>> ";
		}
		else
		{
			cin.ignore(32767, '\n');
			textColor(NormalT);
			return;
		}
	}
	textColor(NormalT);
}
template <class T> void	sortAscending(T* &s, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (s[i] > s[j])
			{
				T temp;
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
}
template <class T> int	merge2Arrays(T &arr1, int n1, T &arr2, int n2, T & arr3)
{
	// !arr1 and arr2 must be sorted
	// Return number of elements of arr3
	int i = 0, j = 0, k = 0;

	// Traverse both array 
	while (i < n1 && j < n2)
	{
		if (arr1[i] < arr2[j])
			arr3[k++] = arr1[i++];
		else
			arr3[k++] = arr2[j++];
	}

	// Store remaining elements of first array 
	while (i < n1)
		arr3[k++] = arr1[i++];

	// Store remaining elements of second array 
	while (j < n2)
		arr3[k++] = arr2[j++];
	return k;
}
template <class T> int	removeDuplicates(T* &arr, int n)
{
	// Xoá các phần tử trùng trong mảng và giữ lại một phần tử
	// !Mảng phải đc sắp xếp thứ tự
	if (n == 0 || n == 1)
		return n;

	int j = 0;

	for (int i = 0; i < n - 1; i++)
		if (arr[i] != arr[i + 1])
			arr[j++] = arr[i];

	arr[j++] = arr[n - 1];

	return j;
}
template <class COURSE> bool askingCourseID(COURSE &c)
{
	int	ans = 0;
	do
	{
		textColor(NormalT);
		cout << "    Please enter Course ID: ";
		textColor(Input__);
		getline(cin, c.id, '\n');
		strUpr(c.id);
		textColor(NormalT);
		cout << "    Please enter class: ";
		textColor(Input__);
		getline(cin, c.class_name, '\n');
		strUpr(c.class_name);

		ans = isCourseInSemesterTXTExist(c);
		if ((ans == -1) || (ans == 0))
		{
			textColor(Notice);
			cout << "\tThis ID was not found." << endl;
			textColor(NormalT);
			cout << "\n    Do you want to try again? (Yes/No/?): ";
			if (yesNoAns() == false)
			{
				textColor(NormalT);
				return false;
			}
		}
		else
		{
			textColor(NormalT);
			return true;
		}
	} while (true);

}
int	currentlyRunningCourse(courseID *&all_course, int n_c, int &return_course_date_j, dayhour &return_course_date)
{
	// Tìm xem lớp học nào đang học theo giờ hiện tại
	// Trả về vị trí của mảng, nếu không có khóa học nào đang học thì trả về -1
	// Trả về ngày giờ học chi tiết của tiết học vào return_course_date
	// Trả về thứ tự ngày trong mảng c.course_date[] vào return_course_date_j

	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	course c;

	for (int i = 0; i < n_c; i++)
	{
		readCourseTXT_OnlyCourseInfo(all_course[i].id, all_course[i].class_name, c);
		courseDateGenerator(c);
		for (int j = 0; j < c.n_course_date; j++)
		{
			if (c.course_date[j].dd == now.tm_mday
				&& c.course_date[j].mm == now.tm_mon + 1
				&& c.course_date[j].yyyy == now.tm_year + 1900
				&& (c.course_date[j].start_hh <= now.tm_hour
					&& c.course_date[j].start_min <= now.tm_min)
				&& (c.course_date[j].end_hh >= now.tm_hour
					&& c.course_date[j].end_hh >= now.tm_min))
			{
				return_course_date = c.course_date[j];
				return_course_date_j = j;
				return i;
			}
		}
	}
	return -1;
}
void classNameExtractor(string path, string &class_name)
{
	// !Hàm này đã cũ, cẩn thận khi sử dụng hàm này
	// Mục đích của hàm để lấy tên lớp từ tên file.csv
	// input: đường dẫn đến file.csv 
	//ví dụ như data\\18CLC6.csv;

	int index = 0;

	// Giả sử đường dẫn file có dạng data\\18clc6.csv
	// Hàm sẽ đọc ngược từng kí tự trong chuỗi đó,
	// bắt đầu từ vị trí strlen(temp_path)-5 do bỏ đuôi .csv 
	// và đọc ngược lại đến khi thấy ký tự '\\' là dừng
	int len = (int)path.length();
	char temp_class_name[1000];
	for (int i = len - 5; i >= 0; i--)
	{
		if (path[i] != '\\' && path[i] != ':')
		{
			temp_class_name[index++] = path[i];
		}
		else
			break;
	}
	temp_class_name[index] = 0; // thêm '\0' vào vị trí cuối
	_strrev(temp_class_name); //Đảo ngược chuỗi
	_strupr_s(temp_class_name, 999);
	class_name = temp_class_name;
}
bool viewLecturerGeneralSchedule(bool is_lecturer, term& this_term)
{
	course* c = NULL;
	char s[][7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	if (!this_term.n_course)
		return false;
	c = new course[this_term.n_course];
	for (int i = 0; i < this_term.n_course; i++)
	{
		// Đọc thông tin từng khóa học
		readCourseTXT_OnlyCourseInfo(this_term.courses[i].id, this_term.courses[i].class_name, c[i]);
	}
	int* index_temp = new int[this_term.n_course];
	int n_index = 0;
	textColor(SpTitleFunc);
	cout << "Education's Schedule:" << endl;
	for (int i = 0; i < 7; i++)
	{
		textColor(NormalT);
		cout << s[i] << ": ";

		// index_temp là một mảng tạm đọc chứa các vị trí đánh dấu mảng dow[]
		// Ví dụ:
		//							i ------>
		//	course*					 CN		 2		 3	   4	  5		6		7		j
		//		0:	course1.dow[] = { false, false, false, true_, true_, false, false};	|
		//		1:	course2.dow[] = { false, true_, false, true_, false, false, false};	|
		//		2:	course3.dow[] = { false, false, true_, false, false, false, true};	v
		// Dùng vòng for duyệt từng thứ
		// như thứ 2 course 2 có tiết -> index_temp = [1] chứa vị trí của course2 trong mảng course
		// thứ 4 -> index temp = [0, 1]
		textColor(Notice);
		for (int j = 0; j < this_term.n_course; j++)
		{
			if (c[j].dow[i])
			{
				index_temp[n_index++] = j;
			}
		}

		// Sắp xếp thứ tự giờ học
		for (int k = 0; k < n_index - 1; k++)
		{
			for (int l = k; l < n_index; l++)
			{
				if (c[index_temp[k]].start_hour[i] > c[index_temp[l]].start_hour[i])
				{
					swap(index_temp[k], index_temp[l]);
				}
			}
		}

		for (int m = 0; m < n_index; m++)
		{
			cout << c[index_temp[m]].id << " ["
				<< c[index_temp[m]].start_hour[i].hh << ":"
				<< c[index_temp[m]].start_hour[i].mm << "-"
				<< c[index_temp[m]].end_hour[i].hh << ":"
				<< c[index_temp[m]].end_hour[i].mm << "]";
			if (is_lecturer)
			{
				cout << " - " << c[index_temp[m]].class_name;
			}
			if (m < n_index - 1)
				cout << "\t";
		}
		if (n_index == 0)
		{
			textColor(OInfo);
			cout << "<No course>";
			textColor(Notice);
		}
		cout << endl;
		n_index = 0;
		textColor(NormalT);
	}
	textColor(SpTitleFunc);
	cout << endl << "Course of this term:" << endl;
	textColor(NormalT);
	for (int o = 0; o < this_term.n_course; o++)
	{
		cout << o + 1 << "  "
			<< c[o].id << ": "
			<< setw(50) << left << c[o].name;
		if (!is_lecturer)
		{
			cout << "\t" << c[o].lecturer;
		}
		if (is_lecturer)
		{
			cout << " - " << c[o].class_name;
		}
		cout << "\t" << c[o].start_date.dd << "/" << c[o].start_date.mm << "/" << c[o].start_date.yyyy << " - "
			<< c[o].end_date.dd << "/" << c[o].end_date.mm << "/" << c[o].end_date.yyyy << endl;
	}
	delete[]c;
	delete[]index_temp;
	return true;

}
void viewAllCourseInformation(const course &c)
{
	// Xem thông tin course 
	cout << "\tCourse ID: " << c.id << endl
		<< "\tCourse name: " << c.name << endl
		<< "\tLecturer Account: " << c.lecturer << endl
		<< "\tStart date: " << c.start_date.dd << "/" << c.start_date.mm << "/" << c.start_date.yyyy << endl
		<< "\tEnd date  : " << c.end_date.dd << "/" << c.end_date.mm << "/" << c.end_date.yyyy << endl;
	cout << "\tDay of week: " << endl;
	char dow[][10] = { "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday", "Sunday" };
	for (int i = 0; i < 7; i++)
	{
		if (c.dow[i])
		{
			cout << "\t    " << dow[i] << ": "
				<< c.start_hour[i].hh << ":" << c.start_hour[i].mm << " - "
				<< c.end_hour[i].hh << ":" << c.end_hour[i].mm << endl;
		}
	}
	cout << "\tRomm: " << c.room << endl;
}

// Account - Login
void	studentAccountGenerator(student &s)
{
	// input: biến s có cấu trúc student
	// ouput: none
	// thêm username và default pasword cho biến s;

	s.account = "s" + to_string(s.id);
	s.default_password = "";

	s.password = dateToPass(s.dob);
}
bool	lecturerAcountGenerator(lecturer &l, const course &c, int start_yr, int end_yr, int term_no)
{
	// Tạo tài khoản lecturer tự động, dùng trong import semester.txt
	lecturer*		lecturers = NULL;
	int				n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	if (isLecturerExist(l) == 1)
	{
		delete[]lecturers;
		return false;
	}
	l.password = sha256(l.account);
	if (l.name.length() == 0)
		l.name = l.account;
	//l.years.resize(1);
	moreSize(l.years, l.n_year);
	//l.years[0].terms.resize(1);
	moreSize(l.years[0].terms, l.years[0].n_term);
	l.years[0].start = start_yr;
	l.years[0].end = end_yr;
	l.years[0].terms[0].no = term_no;
	//l.years[0].terms[0].courses.resize(1);
	moreSize(l.years[0].terms[0].courses, l.years[0].terms[0].n_course);
	l.years[0].terms[0].courses[0].id = c.id;
	l.years[0].terms[0].courses[0].class_name = c.class_name;
	push_back(lecturers, n_lecturer, l);
	saveLecturerTXT(lecturers, n_lecturer);
	delete[]lecturers;
	return true;
}
bool	loginStudentAccount(string &user_name, student &s)
{
	// Kiểm tra user_name có hợp lệ hay không 
	// Nếu có thì trả về giá trị true
	// Hàm này chạy bằng cách tìm fle s[MSSV].txt có trong folder [class_name] nào hay không
	// user_name tên 18127105 hoặc s18127105 vẫn hợp lệ

	// Kiểm tra tính hợp lệ của user_name

	if (!isdigit(user_name[0]) && user_name[0] != 's')
		return false;
	for (int i = 1; i < user_name.length(); i++)
	{
		if (!isdigit(user_name[i]))
			return false;
	}
	if (user_name[0] == 's')
		user_name.erase(0, 1); // bỏ chữ 's' lấy các ký tự còn lại
	int id = stoi(user_name); // chuyển user_name thành id để lát nữa xài hàm
	if (findStudentByID(id, s))
		return true;

	return false;
}
int		loginLecturerAccount(string user_name, lecturer &l)
{
	// Hàm tìm tài khoản trong file lecturer
	// Trong file lecturer.txt có tài khoản admin
	// 10 nếu là lecturer
	// 0 nêu không tồn tại
	for (int i = 1; i < user_name.length(); i++)
	{
		if (isdigit(user_name[i]))
			return 0;
	}
	l.account = user_name;
	if (isLecturerExist(l))
	{
		return 10;
	}
	return 0;
}
int		loginAccount(string &user_name, student &s, lecturer &l)
{
	// 0: Không có tên user
	// 1: student
	// 10: Lecturer
	// 100: Admin
	if (user_name == "admin")
		return 100;
	if (loginStudentAccount(user_name, s))
		return 1;
	int login = 0;
	login = loginLecturerAccount(user_name, l);
	return login;
}

// Tạo đường dẫn đến file
void	classFolderPath(string class_name, string &path)
{
	// Input: class_name chứa tên lớp, path là đường dẫn cần lấy
	// Nếu chưa có thư mục class thì tạo
	// Đường dẫn trả về có dạng data\\[class_name]
	// ví dụ data\\18CLC6
	//	PATH[25] TRỞ LÊN MỚI CHẠY ĐƯỢC!!!

	_mkdir("data");
	strUpr(class_name);
	path = "data\\" + class_name + "\\";
	_mkdir(path.c_str());

}
void	studentTXTPath(string class_name, int id, string &path)
{
	// Input: tên lớp học, MSSV, path để lát nữa chứa đường dẫn
	// Xuất đường dẫn đến file [MSSV.txt]
	// vd: \data\\18CLC6\\s18127105.txt

	_mkdir("data");
	strUpr(class_name);
	path = "data\\" + class_name + "\\";
	_mkdir(path.c_str());
	path += "s" + to_string(id) + ".txt";
}
void	classTXTPath(string class_name, string &path)
{
	// Input: Tên lớp học, path để lát nữa chứa đường dẫn
	// Xuất đường dẫn đến file [class].txt
	// Ví dụ: data\\18CLC6\\18CLC6.txt
	//	PATH[50] TRỞ LÊN MỚI CHẠY ĐƯỢC!!!
	_mkdir("data");
	strUpr(class_name);
	path = "data\\" + class_name + "\\";
	_mkdir(path.c_str());
	path += class_name + ".txt";
}
void	courseIDTXTPath(string class_name, string course_id, string &path)
{
	_mkdir("data");
	strUpr(class_name);
	path = "data\\" + class_name + "\\";
	_mkdir(path.c_str());
	path += course_id + ".txt";
}

// CSV
int		checkDateStrDDMMYYYY(date &d, char delim)
{
	// Hàm cũ, cẩn thận khi dùng !!!
	// return 1	-> Không lỗi
	// return -1 -> Không đọc được ngày
	// return 0 -> Ngày không hợp lệ

	char temp[1000];
	// Để chạy được định dạng YYYY/MM/DD hoặc YYYY-MM-DD
	char *token = NULL, *next_token = NULL;
	cin.getline(temp, 12, delim);
	for (int i = 0; i < strlen(temp); i++)
	{
		if ((temp[i] > '9' || temp[i] < '0') && temp[i] != '/' && temp[i] != '-' && temp[i] != ' ')
			return -1;
	}
	token = strtok_s(temp, "/- ", &next_token);
	d.dd = atoi(temp);
	token = strtok_s(NULL, "/- ", &next_token);
	if (token == NULL)
		return -1;
	d.mm = atoi(token);
	token = strtok_s(NULL, "/- ", &next_token);
	d.yyyy = atoi(token);
	if (!checkValidDate(d))
		return 0;
	return 1;

} //
int		importDate(ifstream &fin, date &d, char delim)
{
	// return 1	-> Không lỗi
	// return -1 -> Không đọc được ngày
	// return 0 -> Ngày không hợp lệ

	char temp[1000];
	// Để chạy được định dạng YYYY/MM/DD hoặc YYYY-MM-DD
	char *token = NULL, *next_token = NULL;
	fin.getline(temp, 12, delim);
	for (int i = 0; i < strlen(temp); i++)
	{
		if ((temp[i] > '9' || temp[i] < '0') && temp[i] != '/' && temp[i] != '-')
			return -1;
	}
	try
	{
		token = strtok_s(temp, "/- ", &next_token);
		d.yyyy = atoi(temp);
		token = strtok_s(NULL, "/- ", &next_token);
		if (token == NULL)
			return -1;
		d.mm = atoi(token);
		token = strtok_s(NULL, "/- ", &next_token);
		d.dd = atoi(token);
	}
	catch (const std::invalid_argument&)
	{
		return -1;
	}
	catch (const std::out_of_range&)
	{
		return -1;
	}

	if (!checkValidDate(d))
		return 0;
	return 1;

} //
int		weekToInt(char* token)
{
	char temp[10];
	strcpy_s(temp, token);
	_strlwr_s(temp, 10);
	char dow1[7][10] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };
	char dow2[7][2] = { "1", "2", "3", "4", "5", "6", "7" };
	char dow3[][7] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat", "sun" };
	for (int i = 0; i < 7; i++)
	{
		if (strcmp(temp, dow1[i]) == 0 || strcmp(temp, dow2[i]) == 0)
			return i;
	}
	return -1;
} //
bool	readDOWInSemesterTXT(bool dow[7], const char* str)
{
	char temp[50];
	strcpy_s(temp, str);
	char *token = NULL, *next_token = NULL;
	token = strtok_s(temp, " ;-&", &next_token);
	int weekday;
	while (token)
	{
		weekday = weekToInt(token);
		if (weekday >= 0)
		{
			dow[weekday] = true;
		}
		else
			return false;
		token = strtok_s(NULL, " ;-&", &next_token);
	}
	return true;
} //
hour	strToHour(char* token)
{
	char temp[1000];
	strcpy_s(temp, 100, token);
	hour h;
	char *temp_token = NULL, *next_token = NULL;
	temp_token = strtok_s(temp, ": ,;\t-", &next_token);
	if (token == NULL)
	{
		return h = { 0, 0 };
	}
	else
		h.hh = atoi(temp_token);

	if (next_token == NULL)
	{
		return h = { 0, 0 };
	}
	else
		h.mm = atoi(next_token);
	return h;
} //
bool	readHourInSemesterCSV(bool dow[7], hour hours[7], const char* str)
{
	// !!!Hàm này đã cũ, cẩn thận khi sử dụng
	char temp[1000];
	strcpy_s(temp, 1000, str);
	char *token = NULL, *next_token = NULL;
	token = strtok_s(temp, " ;-&", &next_token);
	int n = 0;
	int temp_hour[7] = { 0 }, // Lưu các vị trí có ngày trong mảng dow
		n_temp = 0;
	while (token)
	{
		for (int i = n; i < 7; i++)
		{
			if (dow[i] == true)
			{
				n = i;
				temp_hour[n_temp++] = i;
				break;
			}
		}
		hours[n++] = strToHour(token);
		token = strtok_s(NULL, " ;-&", &next_token);
	}
	if (n == 1 && n != n_temp)
	{
		for (int i = 1; i < n_temp; i++)
		{
			hours[temp_hour[n_temp]] = hours[temp_hour[0]];
		}
	}
	return true;
} //
bool	importSemesterCSV(course* &courses, int &n_course, string path, int start_yr, int end_yr, int term_no)
{
	// path: đường dẫn đến fime [semester.csv]
	// start_yr, end_yr : năm học 
	// term_no: học kỳ 1, 2, 3

	ifstream		fin;
	fin.open(path);

	if (fin.fail())
		return false;
	string			temp;

	// lấy dòng đầu tiên ra, không đọc dòng đó
	getline(fin, temp, '\n');
	char			n;
	streamoff		a;
	while (!fin.eof())
	{
		lecturer		l;
		course			c;
		student*		s = NULL;
		int				n_student = 0;
		fin.get(n);
		a = fin.tellg();
		if (n == '\n' || n == ' ' || n == '\t' || n == ',' || a < 0)
			break;
		else
			fin.seekg(-1, ios::cur);
		getline(fin, temp, ',');
		getline(fin, c.id, ',');
		getline(fin, c.name, ',');
		getline(fin, c.class_name, ',');
		getline(fin, c.lecturer, ',');
		l.account = c.lecturer;
		if (!importDate(fin, c.start_date, ','))
			return false;
		if (!importDate(fin, c.end_date, ','))
			return false;
		getline(fin, temp, ',');
		readDOWInSemesterTXT(c.dow, temp.c_str());
		getline(fin, temp, ',');
		readHourInSemesterCSV(c.dow, c.start_hour, temp.c_str());
		getline(fin, temp, ',');
		readHourInSemesterCSV(c.dow, c.end_hour, temp.c_str());
		getline(fin, c.room, '\n');
		courseDateGenerator(c);

		importStudentToCourse(c, s, n_student);														// Xong [course].txt
		saveCourseIDTXT(c, s, n_student, c.class_name);										// course.txt
		saveAllStudentCourse(s, n_student, c, start_yr, end_yr, term_no);			// [student].txt
		if (!lecturerAcountGenerator(l, c, start_yr, end_yr, term_no))
			addCourseToLecturerTXT(l, c, start_yr, end_yr, term_no);					// lecturer.txt
		addCourseToSemesterTXT(c, start_yr, end_yr, term_no);							// Semester.txt
		push_back(courses, n_course, c);
		l.name = "";
	}
	fin.close();
	return true;
}
bool	exportScoreboardCSV(student* s, int n, const course &c)
{
	string			file_name = "Scoreboard" + c.id + " " + c.class_name + ".csv";
	ofstream		fout;
	fout.open(file_name);
	if (!fout.is_open())
		return false;

	fout << "No,Student ID,Lastname,Firstname,Midterm,Final,Lab,Bonus" << endl;
	for (int i = 0; i < n; i++)
	{
		fout << i + 1 << ","
			<< s[i].id << ","
			<< s[i].last_name << ","
			<< s[i].first_name << ","
			<< s[i].midterm << ","
			<< s[i].final_point << ","
			<< s[i].lab << ","
			<< s[i].bonus << endl;
	}
	fout.close();
	return true;
}
bool	exportAttendanceCSV(student* s, int n, course c)
{
	string			file_name = "AttendanceList" + c.id + " " + c.class_name + ".csv";
	ofstream		fout;
	fout.open(file_name);
	if (!fout.is_open())
		return false;

	fout << "No,Student ID,Name,";
	for (int i = 0; i < c.n_course_date; i++)
	{
		fout << c.course_date[i].dd << "/"
			<< c.course_date[i].mm << " "
			<< c.course_date[i].start_hh << ":";

		if (i != c.n_course_date - 1)
			fout << c.course_date[i].start_min << ",";
		else
			fout << c.course_date[i].start_min << endl;
	}
	for (int i = 0; i < n; i++)
	{
		fout << i + 1 << ","
			<< s[i].id << ","
			<< s[i].last_name << " "
			<< s[i].first_name << ",";
		for (int j = 0; j < c.n_course_date; j++)
		{
			if (s[i].attendance[j])
				fout << "V";
			else
				fout << "A";
			if (j != c.n_course_date - 1)
				fout << ",";
			else
				fout << endl;
		}
	}
	fout.close();
	return true;
}
int		checkStudentCSV(student* &student_list, int &n, string path, string class_name, studentID *& existed_student, int &n_existed)
{
	// Kiểm tra file csv có hợp lệ không
	// Nếu đường dẫn file csv không hợp lệ									-> Trả về-100
	// Nếu file đọc không được														-> Trả về -1
	// Nếu file có định dạng ngày không hợp lệ							-> Trả về -111
	// Nếu file có các học sinh đã tồn tại										-> Trả về 0 
	// Nếu file đọc ngon lành, không có data đã bị tồn tại sẵn	-> Trả về 1

	ifstream	fin;
	fin.open(path);

	//char class_name[10];
	//classNameExtractor(path, class_name); // Lấy tên lớp từ tên file csv
	if (fin.fail())
		return -100;

	string		temp;
	// Lấy dòng đầu tiên ra, không đọc dòng đó:
	getline(fin, temp, '\n');
	student		s;
	studentID	s_existed;
	char	catch_err_eof;
	int		catch_err = 0;
	while (!fin.eof())
	{
		if (!fin.get(catch_err_eof))
			break;
		//catch_err = fin.tellg();
		if (catch_err_eof == '\n' || catch_err_eof == ' ' || catch_err_eof == '\t' || catch_err_eof == ',' || catch_err < 0)
			break;
		else
			fin.seekg(-1, ios::cur);
		// 6 dòng trên dùng để tránh trường hợp dòng cuối cùng của file chứa kí tự xuống dòng  dẫn đến lỗi file
		try
		{
			getline(fin, temp, ',');
			s.no = stoi(temp);
			getline(fin, temp, ',');
			s.id = stoi(temp);
		}
		catch (const std::invalid_argument&)
		{
			return -1;
		}
		catch (const std::out_of_range&)
		{
			return -1;
		}

		getline(fin, s.last_name, ',');
		getline(fin, s.first_name, ',');
		if (findStudentByID(s.id, s))
		{
			s_existed = s;
			push_back(existed_student, n_existed, s_existed);
		}
		getline(fin, temp, ',');
		strLwr(temp);
		if (temp == "male")
			s.gender = 0;
		else
		{
			if (temp == "female")
				s.gender = 1;
			else
				s.gender = -1;
		}
		catch_err = importDate(fin, s.dob, '\n');
		if (catch_err == -1)
			return -1;						// Đọc file bị lỗi
		else if (catch_err == 0)
			return -111;					// Định dạng ngày bị lỗi

		studentAccountGenerator(s);
		s.class_name = class_name;
		push_back(student_list, n, s);
		temp = "";
	}
	fin.close();
	if (n_existed == 0)
		return 1;
	return 0;
}
void	importStudentCSV(student* &s, int &n, studentID *& existed_student, int &n_existed, int command)
{
	// Thêm HS từ file student.csv
	//		command:
	//		1. Skip student(s) who already has data
	//		2. Delete ALL existing data and importing ALL student(s)

	int temp_index = 0;
	textColor(Notice);
	student			*new_student = NULL;	// Danh sách chứa HS mới (Không trùng dữ liệu cũ)
	int				n_new = 0;
	student			s_temp;
	cout << "\t\t    Deleting: 0/" << n_existed;
	if (command == 2)		// Nếu muốn xóa hết data
	{
		int b = 0;
		for (int i = 0; i < n_existed; i++)
		{
			academic_year *temp_yr = NULL;
			int				n_temp = 0;
			loadStudentData(s_temp, temp_yr, n_temp, existed_student[i].class_name, existed_student[i].id);
			removeAStudentNameInAllCourseIDTXT(s_temp, temp_yr, n_temp);
			removeStudentTXT(existed_student[i].id, existed_student[i].class_name);
			removeStudentFromStudentList(existed_student[i].id, existed_student[i].class_name);
			b = 0;
			if (n_existed < 9)
				b += 1;
			else
				b += 2;
			if (i < 9)
				b += 1;
			else
				b += 2;
			for (int j = 0; j <= b; j++)
			{
				cout << "\b";
			}
			cout << i + 1 << "/" << n_existed;
			b = 0;
			delete[] temp_yr;
		}
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		// Nếu muốn skip data bị trùng
		if (command == 1)
		{
			//Kiểm tra từng HS xem thử ai bị trùng
			if (s[i] == existed_student[temp_index])
			{
				temp_index++;
				continue;
			}
			else
				push_back(new_student, n_new, s[i]);
			// Lưu thông tin HS mới vào student.txt
		}
		else
		{
			push_back(new_student, n_new, s[i]);
		}
		saveStudent(s[i]);
	}
	sortAscending(new_student, n_new);
	// Hiện bảng danh sách HS đã import
	if (command == 1)
		showAllInfoStudentList(new_student, n_new, true);
	else
		showAllInfoStudentList(s, n, true);

	// Lưu danh sách HS để tiện đường tìm

	student		*student_list = NULL;		// Danh sách HS đã có rồi
	int			n_list = 0;
	bool		flag = readStudentList(student_list, n_list, s[0].class_name);
	sortAscending(s, n);					//
	sortAscending(student_list, n_list);

	student		*all_student = new student[n + n_list];	// Danh sách HS có rồi + đã import
	int			n_all = removeDuplicates(all_student, merge2Arrays(s, n, student_list, n_list, all_student));

	// Nếu chưa tồn tại class.txt
	if (!flag)
		exportStudentList(s, n, s[0].class_name);
	// Nếu đã tồn tại thì
	else
		exportStudentList(all_student, n_all, s[0].class_name);
	delete[] all_student;
	all_student = NULL;
	addClass(s[0].class_name);

	textColor(Notice);
	cout << "\t\t    Import student information from .CSV file successfully!" << endl;
	if (n_existed == n_all)
	{
		cout << "\t\t   *But there is no any student to import!" << endl;
	}

	// Thêm Các khóa học hiện tại vào các file HS mới import
	courseID	*current_course = NULL;
	int			n_current = 0;
	if (n != n_existed &&
		readCurrentSemesterOfAClass(current_course, n_current, s[0].class_name) == 1)
	{
		cout << endl
			<< "Do you want to add new student to this course?: ";
		if (yesNoAns())
		{
			time_t	bg = time(0);
			tm		now;
			int		sem = getCurrentSemester(),
				start_yr = 0, end_yr = 0;
			localtime_s(&now, &bg);
			if (sem == 1)
			{
				start_yr = now.tm_year + 1900;
				end_yr = start_yr - 1;
			}
			else
			{
				start_yr = now.tm_year + 1900 - 1;
				end_yr = start_yr + 1;
			}
			if (command == 2)
			{
				saveAllCourseToAllStudent(s, n, current_course, n_current, start_yr, end_yr, sem);
			}
			else
				saveAllCourseToAllStudent(new_student, n_new, current_course, n_current, start_yr, end_yr, sem);
			for (int i = 0; i < n_current; i++)
			{
				course c;
				readCourseIDTXT(current_course[i].id, c, student_list, n_list, s[0].class_name);
				sortAscending(student_list, n_list);
				all_student = new student[n_list + n_new];
				n_all = merge2Arrays(new_student, n_new, student_list, n_list, all_student);
				saveCourseIDTXT(c, all_student, n_all, s[0].class_name);
				delete[] all_student;
			}
		}
	}
	delete[] new_student;
	if (student_list != NULL)
		delete[] student_list;
}
void	showStudentCSVTemplate()
{
	textColor(NormalT);
	cout << "\n\t";
	textColor(SpTitleFunc);
	cout << setfill('*') << setw(39) << "*"
		<< left << "Student(s) of class CLASS" << setfill('*') << setw(39) << "*" << setfill(' ') << endl;
	textColor(NormalT);
	cout << "\t";
	textColor(TitleBoard);
	cout << "|" << setw(14) << left << "    No  |"
		<< setw(7) << left << "ID" << "|"
		<< setw(36) << left << "  Lastname" << "|"
		<< setw(17) << left << "  Firstname" << "|"
		<< setw(9) << left << "  Gender" << "|"
		<< setw(14) << left << "      DoB" << "|" << endl;
	textColor(NormalT);
	cout << "\t";
	textColor(TitleBoard);
	cout << setfill('-')
		<< setw(103) << "-" << endl
		<< setfill(' ');
	string template_last_name = "Last Name",
		template_firstname = "First Name";
	for (int i = 1; i <= 3; i++)
	{
		textColor(NormalT);
		cout << "\t";
		textColor(InBoard);
		cout << "|    " << setw(4) << left << i << "|  "
			<< setw(10) << left << 18127099 + i << "|"
			<< "  Last Name " << i << setw(24) << right << "|"
			<< "  First Name " << i << setw(4) << right << "|";
		if (i - 1 == 0)
			cout << setw(9) << left << "  Male" << "|";
		else
		{
			if (i - 1 == 1)
				cout << setw(9) << left << "  Female" << "|";
			else
				cout << setw(9) << left << "  Other" << "|";
		}
		cout << setw(4) << 2000 << "-" << setw(2) << 12 << "-" << setw(6) << 31 << "|" << endl;
	}
	textColor(NormalT);
	cout << "\t";
	textColor(InBoard);
	cout << setfill('*')
		<< setw(103) << "*" << endl
		<< setfill(' ');
	textColor(NormalT);
}
void	exportStudentCSVTemplate()
{
	ofstream fout;
	fout.open("[Class_name].csv");
	fout << "No,ID,Last name,First Name,Gender,Date of Birth" << endl
		<< "1,18127001,Last name 1,First name 1,Female,2000-12-31" << endl
		<< "2,181270002,Last name 2,First name 2,Male,2000-02-25" << endl
		<< "3,181270003,Last name 3,First name 3,Other,2000-03-11" << endl;
	fout.close();
}

// Student[id].txt
bool	saveStudent(student s)
{
	// Hàm nay đã cũ! Khuyến cáo không nên sử dụng hàm nãy nữa, 

	// Xài hàm saveStudent(const student &s, academic_year* &student_course, int n_course) thay cho hàm này


	// [vi]
	// input: một biến kiểu dữ liệu cấu trúc student
	// output: true nếu mở file thành công, false nếu mở không được
	// Dùng chung hàm exportStudentTXT()

	string			path;
	studentTXTPath(s.class_name, s.id, path);

	ofstream		fout;
	fout.open(path);

	if (fout.fail())
		return false;

	fout << "No,Student ID,Lastname,Firstname,Gender,DoB,Account,Password,Class" << endl
		<< s.no << "," << s.id << "," << s.last_name << "," << s.first_name << ","
		<< s.gender << "," << s.dob.yyyy << "-" << s.dob.mm << "-" << s.dob.dd << ","
		<< s.account << "," << s.password << "," << s.class_name << endl
		<< 0 << endl; //File chưa lưu thông tin khóa học

	fout.close();
	return true;
}
bool	saveStudent(const student &s, academic_year* &student_course, int n_course)
{
	// input: một biến kiểu dữ liệu cấu trúc student
	// output: true nếu mở file thành công, false nếu mở không được

	string path;
	studentTXTPath(s.class_name, s.id, path);

	ofstream fout;
	fout.open(path);

	if (fout.fail())
		return false;
	fout << "No,Student ID,Lastname,Firstname,Gender,DoB,Account,Password,Class" << endl;
	fout << s.no << "," << s.id << "," << s.last_name << "," << s.first_name << ",";
	fout << s.gender << "," << s.dob.yyyy << "-" << s.dob.mm << "-" << s.dob.dd << ",";
	fout << s.account << "," << s.password << "," << s.class_name << endl;
	saveSemesterCourses(fout, student_course, n_course);
	fout.close();
	return true;
}
template <class COURSE> void removeACourseInStudentIDTXT(const student &s, academic_year* &student_course, int n_course, const COURSE &c)
{
	string path;
	studentTXTPath(s.class_name, s.id, path);

	ofstream fout;
	fout.open(path);

	if (fout.fail())
		return;
	fout << "No,Student ID,Lastname,Firstname,Gender,DoB,Account,Password,Class" << endl;
	fout << s.no << "," << s.id << "," << s.last_name << "," << s.first_name << ",";
	fout << s.gender << "," << s.dob.yyyy << "-" << s.dob.mm << "-" << s.dob.dd << ",";
	fout << s.account << "," << s.password << "," << s.class_name << endl;
	removeACourseInSemesterCourses(fout, student_course, n_course, c);
	fout.close();
}
void	exportStudentTXT(student* student_list, int n, string class_name)
{
	// input: một mảng s[] có cấu trúc student
	//				biến n chứa số lượng phần tử mảng s[]
	//				class_name là tên của lớp (18CLC6)
	//				Ý là các file txt sẽ xuất ra trong một folder data\[class_name]\ và trong folder đó chứa file txt xuất
	//				ví dụ như muốn xuất hết dữ liệu trong mảng student ra các file khác nhau dạng txt ở trong
	//				foder data\\18CLC6\\:
	//							exportCSVToFiles(s, n, "data\\18CLC6", ".txt");
	// output: none

	//Lưu ý về cách hoạt động của hàm này:
	// Hàm sẽ xuất lần lượt từng file có dạng: "s[student.id].txt"
	// trong đó [student.id]là MSSV trong student.id
	// ví dụ như các file sẽ xuất ra có dạng: "s18127068.txt", "s18127084.txt" hay là "s18127197.txt"

	for (int i = 0; i < n; i++)
	{
		saveStudent(student_list[i]);
	}
}
student	readStudentData(int id, string class_name)
{
	// Input: id là MSSV, class_name là tên lớp
	// Output: struct student chứa thông tin được đọc từ file đó
	// Đọc dữ liệu học sinh từ một file lưu trữ trong thư mục //data//[class_name]//
	// VD: đọc file 18127105.txt

	string			temp;
	student		s;
	studentTXTPath(class_name, id, temp);
	ifstream		fin;
	fin.open(temp);

	getline(fin, temp, '\n');

	getline(fin, temp, ',');
	s.no = stoi(temp);
	getline(fin, temp, ',');
	s.id = stoi(temp);
	getline(fin, s.last_name, ',');
	getline(fin, s.first_name, ',');
	getline(fin, temp, ',');
	s.gender = stoi(temp);
	getline(fin, temp, '-');
	s.dob.yyyy = stoi(temp);
	getline(fin, temp, '-');
	s.dob.mm = stoi(temp);
	getline(fin, temp, ',');
	s.dob.dd = stoi(temp);
	getline(fin, s.account, ',');
	getline(fin, s.password, ',');
	getline(fin, s.class_name, '\n');
	fin.close();
	return s;
}
bool	readStudentData(int id, string class_name, student &s)
{
	// Input: id là MSSV, class_name là tên lớp, student s để lát nữa đưa dữ liệu vào
	// Output: struct student chứa thông tin được đọc từ file đó
	// Đọc dữ liệu học sinh từ một file lưu trữ trong thư mục //data//[class_name]//
	// VD: đọc file 18127105.txt

	string			temp;
	studentTXTPath(class_name, id, temp);

	ifstream		fin;
	fin.open(temp);
	if (fin.fail())
		return false;

	getline(fin, temp, '\n');

	getline(fin, temp, ',');
	s.no = stoi(temp);
	getline(fin, temp, ',');
	s.id = stoi(temp);
	getline(fin, s.last_name, ',');
	getline(fin, s.first_name, ',');
	getline(fin, temp, ',');
	s.gender = stoi(temp);
	getline(fin, temp, '-');
	s.dob.yyyy = stoi(temp);
	getline(fin, temp, '-');
	s.dob.mm = stoi(temp);
	getline(fin, temp, ',');
	s.dob.dd = stoi(temp);
	getline(fin, s.account, ',');
	getline(fin, s.password, ',');
	getline(fin, s.class_name, '\n');
	fin.close();
	return true;
}
bool	loadStudentData(student &s, academic_year* &student_course, int &n_course, string class_name, int id)
{
	// Input: id là MSSV, class_name là tên lớp, student s để lát nữa đưa dữ liệu vào
	// Output: struct student chứa thông tin được đọc từ file đó
	// Đọc dữ liệu học sinh từ một file lưu trữ trong thư mục //data//[class_name]//
	// VD: đọc file 18127105.txt

	string		temp;
	studentTXTPath(class_name, id, temp);
	ifstream	fin;
	fin.open(temp);
	if (fin.fail())
		return false;

	getline(fin, temp, '\n');

	getline(fin, temp, ',');
	s.no = stoi(temp);
	getline(fin, temp, ',');
	s.id = stoi(temp);
	getline(fin, s.last_name, ',');
	getline(fin, s.first_name, ',');
	getline(fin, temp, ',');
	s.gender = stoi(temp);
	getline(fin, temp, '-');
	s.dob.yyyy = stoi(temp);
	getline(fin, temp, '-');
	s.dob.mm = stoi(temp);
	getline(fin, temp, ',');
	s.dob.dd = stoi(temp);
	getline(fin, s.account, ',');
	getline(fin, s.password, ',');
	getline(fin, s.class_name, '\n');
	fin >> n_course;
	if (n_course == 0)
	{
		return false;
	}
	else
		fin.seekg(-1, ios::cur);
	readSemesterCourses(fin, student_course, n_course);

	fin.close();
	return true;
}
bool	isStudentExist(int id)
{
	// Hàm tìm file [MSSV].txt có tồn tại hay không
	// Nếu có thì trả về giá trị true
	// Giống hàm findStudentByID() nhưng chỉ xét HS đó có tồn tại hay không

	// mở file class.txt để xem danh sách lớp, từ đó mở được folder [class_name]
	ifstream			fin_class;
	fin_class.open("data\\class.txt");

	if (fin_class.fail())
		return false;

	string*		class_name = NULL;
	int			n_class = 0;
	if (!readClassTXT(class_name, n_class))
		return false;
	fin_class.close();

	// Từ các class_name đọc được, mở từng folder xem user_name có hay không
	string		path;
	for (int i = 0; i < n_class; i++)
	{
		ifstream fin;
		studentTXTPath(class_name[i], id, path);
		fin.open(path);
		if (fin.is_open())
		{
			fin.close();
			delete[] class_name;
			return true;
		}
	}
	delete[] class_name;
	return false;
}
bool	isStudentExist(int id, string &existed_class)
{
	// Hàm tìm file [MSSV].txt có tồn tại hay không
	// Nếu có thì trả về giá trị true và tên lớp của HS đó
	// Giống hàm findStudentByID() nhưng chỉ xét HS đó có tồn tại hay không
	// mở file class.txt để xem danh sách lớp, từ đó mở được folder [class_name]
	ifstream			fin_class;
	fin_class.open("data\\class.txt");

	if (fin_class.fail())
		return false;

	string*		class_name = NULL;
	int			n_class = 0;
	if (!readClassTXT(class_name, n_class))
		return false;
	fin_class.close();

	// Từ các class_name đọc được, mở từng folder xem user_name có hay không
	string		path;
	for (int i = 0; i < n_class; i++)
	{
		ifstream fin;
		studentTXTPath(class_name[i], id, path);
		fin.open(path);
		if (fin.is_open())
		{
			existed_class = class_name[i];
			fin.close();
			delete[] class_name;
			return true;
		}
	}
	delete[] class_name;
	return false;
}
bool	findStudentByID(int id, student &s)
{
	// Hàm tìm file [MSSV].txt có tồn tại hay không
	// Nếu có thì trả về giá trị true và thông tin HS lưu trong biến s

	// mở file class.txt để xem danh sách lớp, từ đó mở được folder [class_name]

	ifstream		fin_class;
	fin_class.open("data\\class.txt");
	if (fin_class.fail())
		return false;

	string*	class_name = NULL;
	int		n = 0;
	if (!readClassTXT(class_name, n))
		return false;
	fin_class.close();

	// Từ các class_name đọc được, mở từng folder xem user_name có hay không
	for (int i = 0; i < n; i++)
	{
		if (readStudentData(id, class_name[i], s))
		{
			delete[] class_name;
			return true;
		}
	}
	delete[] class_name;
	return false;
}
void	removeStudentTXT(int id, string class_name)
{
	// Xóa file [MSSV].txt
	string path;
	studentTXTPath(class_name, id, path);
	remove(path.c_str());
}
void	moveStudentTXT(student &s, string new_class)
{
	// Hàm chuyển học sinh từ lớp s.class_name sang new_class
	removeStudentFromStudentList(s.id, s.class_name);
	academic_year	*s_yr = NULL;
	int				n_yr = 0;
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	removeStudentTXT(s.id, s.class_name);
	s.class_name = new_class;
	// Thêm HS mới vào student list [Class].txt
	student		*student_temp = NULL;
	int			 n = 0;
	if (readStudentList(student_temp, n, s.class_name))
		s.no = n;
	else
		s.no = 1;

	// Thêm dữ liệu mới vào file list, nếu chưa tồn tại file list thì thêm mới
	//student_temp[n - 1] = s;
	push_back(student_temp, n, s);
	sortAscending(student_temp, n);
	exportStudentList(student_temp, n, s.class_name);

	// Nếu chưa tồn tại lớp thì thêm lớp mới 
	addClass(s.class_name);

	// Sửa lớp của HS trong các file course
	for (int i = 0; i < n_yr; i++)
	{
		for (int j = 0; j < s_yr[i].n_term; j++)
		{
			for (int k = 0; k < s_yr[i].terms[j].n_course; k++)
			{
				course c;
				student *s_list = NULL;
				int		n_list = 0;
				readCourseIDTXT(s_yr[i].terms[j].courses[k].id, c, s_list, n_list, s_yr[i].terms[j].courses[k].class_name);
				for (int l = 0; l < n_list; l++)
				{
					if (s_list[l].id == s.id)
					{
						s_list[l].class_name = s.class_name;
						break;
					}
				}
				saveCourseIDTXT(c, s_list, n_list, c.class_name);
			}
		}

	}
	// Xuất dữ liệu HS mới ra file 
	delete[]student_temp;
	saveStudent(s, s_yr, n_yr);
	delete[]s_yr;
}
void	editAllDataOfAStudent(student &s)
{
	academic_year	*s_yr = NULL;
	int n_yr = 0;
	cout << "This is the information of the student before changing their data:" << endl;
	viewProfileInfo(s.account);
	cout << endl;
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	changeID(s);
	cout << endl;
	saveStudent(s, s_yr, n_yr);
	changeName(s);
	cout << endl;
	saveStudent(s, s_yr, n_yr);
	changeGender(s);
	cout << endl;
	saveStudent(s, s_yr, n_yr);
	changeBirthday(s);
	cout << endl;
	saveStudent(s, s_yr, n_yr);
	delete[]s_yr;
}
void	editSomeDataOfAStudent(student &s)
{
	academic_year	*s_yr = NULL;
	int n_yr = 0;
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	textColor(OInfo);
	cout << "    Please choose: " << endl
		<< "\t1. ID" << endl
		<< "\t2. Name" << endl
		<< "\t3. Date Of Birth" << endl
		<< "\t4. Gender" << endl
		<< "\t5. Reset Student's Password" << endl;
	textColor(NormalT);
	cout << "You can choose many commands at once." << endl;
	textColor(Notice);
	cout << "    Remember that, all commands must be separated by at least one space and when you enter something wrong we ignore!" << endl;
	textColor(NormalT);
	int*	commands = NULL;
	int		n_command = askManyCommands(1, 5, commands);
	cout << endl;
	cout << "This is the information of the student before changing their data:" << endl;
	viewProfileInfo(s.account);
	cout << endl;
	for (int i = 0; i < n_command; i++)
	{
		switch (commands[i])
		{
		case 1:
		{
			changeID(s);
			cout << endl;
			break;
		}
		case 2:
		{
			changeName(s);
			cout << endl;
			break;
		}
		case 3:
		{
			changeBirthday(s);
			cout << endl;
			break;
		}
		case 4:
		{
			changeGender(s);
			cout << endl;
			break;
		}
		case 5:
		{
			s.password = dateToPass(s.dob);
			textColor(Notice);
			cout << "    Reset password successfully!" << endl;
			cout << endl;
			break;
		}
		default:
			break;
		}
		saveStudent(s, s_yr, n_yr);
	}
	delete[]commands;
	delete[]s_yr;
	s_yr = NULL;
}

// class.txt
bool	readClassTXT(string* &class_name)
{
	// Đọc danh sách lớp có trong file class.txt
	fstream fin;
	fin.open("data\\class.txt", ios::in);
	if (fin.fail())
		return false;
	int n = 0;
	/*while (!fin.eof())
	{
		moreSize(class_name, n, n+1);
		getline(fin, class_name[n - 1], '\n');
		if (class_name[n - 1] == "")
		{
			resize(class_name, resize(n - 1);
			break;
		}
	}*/
	fin >> n;
	if (class_name != NULL)
		delete[] class_name;
	class_name = new string[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, class_name[n - 1], '\n');
	}
	fin.close();
	return true;
}
bool	readClassTXT(string* &class_name, int &n_class)
{
	// Đọc danh sách lớp có trong file class.txt
	fstream fin;
	fin.open("data\\class.txt", ios::in);
	if (fin.fail())
		return false;
	/*while (!fin.eof())
	{
		moreSize(class_name, n, n+1);
		getline(fin, class_name[n - 1], '\n');
		if (class_name[n - 1] == "")
		{
			resize(class_name, resize(n - 1);
			break;
		}
	}*/
	fin >> n_class;
	fin.ignore();
	if (class_name != NULL)
		delete[] class_name;
	class_name = new string[n_class];
	for (int i = 0; i < n_class; i++)
	{
		getline(fin, class_name[i], '\n');
	}
	fin.close();
	return true;
}
void	addClass(string class_name)
{
	fstream		fin;
	ofstream		fout;
	fin.open("data\\class.txt", ios::in);
	strUpr(class_name);
	if (fin.fail())
	{
		ofstream fout;
		fout.open("data\\class.txt"); //Nếu chưa có file thì tạo file mới
		fout << 1 << endl;
		fout << class_name << endl;
		fout.close();
		return;
	}

	string*		class_name_list = NULL;
	string		temp;
	int			n = 0;
	//Lấy dữ liệu để kiểm tra lớp có trong danh sách không
	fin >> n;
	fin.ignore();
	class_name_list = new string[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, class_name_list[i], '\n');
	}
	fin.close();
	for (int i = 0; i < n; i++)
	{
		if (class_name_list[i] == class_name)
		{
			fin.close();
			delete[]class_name_list;
			return; //Nếu có lớp rồi thì khỏi thêm nữa
		}
	}
	// Nếu chưa có lớp class_name trong danh sách thì thêm vào
	fout.open("data\\class.txt");
	fout << n + 1 << endl;
	for (int i = 0; i < n; i++)
		fout << class_name_list[i] << endl;
	fout << class_name << endl;
	delete[]class_name_list;
	fout.close();

}
bool	removeClass(string class_name)
{
	string*			class_name_list = NULL;
	int				n_class = 0;
	if (!readClassTXT(class_name_list, n_class))
		return false;
	ofstream fout;
	fout.open("data\\class.txt");
	strUpr(class_name);
	fout << n_class - 1 << endl;
	for (int i = 0; i < n_class; i++)
	{
		if (class_name_list[i] == class_name)
			continue;
		fout << class_name_list[i] << endl;
	}
	fout.close();
	return true;
}
bool	isClassExist(string class_name)
{
	string* class_list = NULL;
	int		n_class_list = 0;
	readClassTXT(class_list, n_class_list);
	for (int i = 0; i < n_class_list; i++)
	{
		if (class_list[i] == class_name)
			return true;
	}
	return false;
}

// File [CLass_name].txt
void	exportStudentList(student* student_list, int n, string class_name)
{
	// Lưu danh sách học sinh của một lớp đã đọc từ file csv ra một file khác để lưu trữ
	// Bao gồm STT, MSSV, Họ tên
	// Dòng đầu tiên chứa số lượng HS
	string path;
	classTXTPath(class_name, path);
	ofstream fout;
	fout.open(path);
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << student_list[i].no << "," << student_list[i].id << "," << student_list[i].last_name << "," << student_list[i].first_name << endl;
	}
	fout.close();
}
bool	readStudentList(student* &student_list, int &n, string class_name)
{
	// Đọc danh sách HS có trong file [Class].txt
	// Nếu tồn tại danh sách lớp đó thì trả về giá trị true, không có thì false
	string path;
	classTXTPath(class_name, path);

	ifstream fin;
	fin.open(path);

	if (fin.fail())
		return false;
	string temp;
	getline(fin, temp, '\n');
	n = stoi(temp);
	if (student_list != NULL)
		delete[]student_list;
	student_list = new student[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, temp, ',');
		student_list[i].no = i + 1;
		getline(fin, temp, ',');
		student_list[i].id = stoi(temp);
		getline(fin, student_list[i].last_name, ',');
		getline(fin, student_list[i].first_name, '\n');
		student_list[i].class_name = class_name;
	}
	fin.close();
	return true;
}
void	addNewStudent(student s)
{
	// Input: struct student s là thông tin HS cần thêm; 
	// Thêm thông tin sinh viên vào file [MSSV].txt, [Class].txt, nếu chưa có tên lớp thì tạo

	string path;
	studentTXTPath(s.class_name, s.id, path);
	strUpr(s.class_name);
	// Thêm HS mới vào student list [Class].txt
	student		*student_temp = NULL;
	int			 n = 0;
	if (readStudentList(student_temp, n, s.class_name))
		s.no = n;
	else
		s.no = 1;

	// Thêm dữ liệu mới vào file list, nếu chưa tồn tại file list thì thêm mới
	//student_temp[n - 1] = s;
	push_back(student_temp, n, s);
	sortAscending(student_temp, n);
	exportStudentList(student_temp, n, s.class_name);

	// Nếu chưa tồn tại lớp thì thêm lớp mới 
	addClass(s.class_name);

	// Xuất dữ liệu HS mới ra file 
	delete[]student_temp;
	saveStudent(s);
}
bool	isInStudentList(int id, string class_name)
{
	// Tìm hs có trong ds hs hay không dựa trên id
	// input: biến id kiểu nguyên là id hs cần tìm
	//			path là đường dẫn đến file danh sách hs (vd: 18CLC6.txt)
	// output: true nếu tìm đc hs có id input, false nếu ko tìm thấy id hoặc file list không tồn tại

	student*		s_temp = NULL;
	int				n = 0;
	if (readStudentList(s_temp, n, class_name))
	{
		for (int i = 0; i < n; i++)
		{
			if (s_temp[i].id == id)
				return true;
		}
	}
	delete[] s_temp;
	return false;
}
void	removeStudentFromStudentList(int id, string class_name)
{
	// Xóa thông tin sinh viên khỏi danh sách sinh viên [class_name].txt

	student*	student_list = NULL;
	int			n = 0;
	string		path;

	readStudentList(student_list, n, class_name);

	classTXTPath(class_name, path);

	ofstream		fout;
	int				temp;

	fout.open(path);
	fout << n - 1 << endl;
	for (int i = 0; i < n; i++)
	{
		if (student_list[i].id == id)
		{
			continue;
			temp = i;
		}
		fout << student_list[i].no << "," << student_list[i].id << "," << student_list[i].last_name << "," << student_list[i].first_name << endl;
	}
	fout.close();
	if (n == 1)
	{
		removeClass(class_name);
		remove(path.c_str()); // Xoá luôn file [class_name].txt
		classFolderPath(class_name, path);
		_rmdir(path.c_str()); //Xóa luôn thư mục
	}
	delete[] student_list;
}

// [Course].txt
bool	readCourseIDTXT(string course_id, course &course_read, student* &s, int &n, string class_name)
{
	fstream		fin;
	string		path;
	courseIDTXTPath(class_name, course_id, path);

	fin.open(path);
	if (fin.fail())
		return false;

	getline(fin, course_read.id, '\n');
	getline(fin, course_read.name, '\n');
	getline(fin, course_read.class_name, '\n');
	getline(fin, course_read.lecturer, '\n');
	fin >> course_read.start_date.yyyy;
	fin >> course_read.start_date.mm;
	fin >> course_read.start_date.dd;
	fin >> course_read.end_date.yyyy;
	fin >> course_read.end_date.mm;
	fin >> course_read.end_date.dd;

	int		count = 0,
		temp;
	for (int i = 0; i < 7; i++)
	{
		// Đọc thứ chứa tiết trong tuần
		int		c;
		fin >> c;
		if (c == 0)
			course_read.dow[i] = false;
		else
		{
			course_read.dow[i] = true;
			count++;
		}
	}
	int		 j = 0;
	for (int i = 0; i < count; i++)
	{
		// Đọc ngày giờ từng tiết học
		while (true)
		{
			if (course_read.dow[j] == true)
			{
				fin >> course_read.start_hour[j].hh;
				fin >> course_read.start_hour[j].mm;
				fin >> course_read.end_hour[j].hh;
				fin >> course_read.end_hour[j].mm;
				j++;
				break;
			}
			j++;
		}
	}
	courseDateGenerator(course_read);
	fin.ignore();
	getline(fin, course_read.room, '\n');
	string temp_str;
	getline(fin, temp_str, '\n');

	course_read.n_student = stoi(temp_str);

	if (s != NULL)
		delete[]s;
	s = new student[course_read.n_student];
	for (int i = 0; i < course_read.n_student; i++)
	{
		/*fin >> s[i].id;
		fin.ignore(1, ' ');*/
		getline(fin, temp_str, ' ');
		s[i].id = stoi(temp_str);
		getline(fin, s[i].last_name, ',');
		getline(fin, s[i].first_name, ',');
		getline(fin, s[i].class_name, '\n');
		//s[i].attendance.resize(course_read.course_date.size());
		s[i].n_date = course_read.n_course_date;
		s[i].attendance = new bool[course_read.n_course_date];
		for (j = 0; j < course_read.n_course_date; j++)
		{
			fin >> temp;
			if (temp)
				s[i].attendance[j] = true;
			else
				s[i].attendance[j] = false;
		}
		fin.ignore();
		getline(fin, temp_str, ' ');
		s[i].midterm = stod(temp_str);
		getline(fin, temp_str, ' ');
		s[i].final_point = stod(temp_str);
		getline(fin, temp_str, ' ');
		s[i].lab = stod(temp_str);
		getline(fin, temp_str, '\n');
		s[i].bonus = stod(temp_str);
	}
	n = course_read.n_student;
	fin.close();
	return true;
}
void	saveCourseIDTXT(course &course_save, student* &s, int n, string class_name)
{
	// Lưu file [course].txt
	ofstream	fout;
	string		path;
	courseIDTXTPath(class_name, course_save.id, path);
	courseDateGenerator(course_save);
	fout.open(path);

	fout << course_save.id << endl;
	fout << course_save.name << endl;
	fout << course_save.class_name << endl;
	fout << course_save.lecturer << endl;
	fout << course_save.start_date.yyyy << " " << course_save.start_date.mm << " " << course_save.start_date.dd << endl;
	fout << course_save.end_date.yyyy << " " << course_save.end_date.mm << " " << course_save.end_date.dd << endl;
	int		count = 0;

	for (int i = 0; i < 7; i++)
	{ // Đọc thứ chứa tiết trong tuần
		if (course_save.dow[i] == false)
			fout << "0";
		else
		{
			fout << "1";
			count++;
		}
		if (i < 6)
			fout << " ";
		else
			fout << "\n"; // Vị trí cuối cần xuống dòng
	}
	int		j = 0;
	for (int i = 0; i < count; i++)
	{ // Đọc ngày giờ từng tiết học
		while (true)
		{
			if (course_save.dow[j] == true)
			{
				fout << course_save.start_hour[j].hh << " " << course_save.start_hour[j].mm << endl;
				fout << course_save.end_hour[j].hh << " " << course_save.end_hour[j].mm << endl;
				j++;
				break;
			}
			j++;
		}
	}
	fout << course_save.room << endl;
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << s[i].id << " ";
		fout << s[i].last_name << "," << s[i].first_name << "," << s[i].class_name << endl;
		j = 0;
		s[i].n_date = course_save.n_course_date;
		if (s[i].attendance == NULL)
			s[i].attendance = new bool[course_save.n_course_date]();
		for (j = 0; j < course_save.n_course_date; j++)
		{
			//fout << s[i].attendance[j];
			if (s[i].attendance[j])
				fout << 1;
			else
				fout << 0;
			if (j < course_save.n_course_date - 1)
				fout << " ";
			else
				fout << endl;
		}
		fout << s[i].midterm << " " << s[i].final_point << " " << s[i].lab << " " << s[i].bonus << endl;
	}
	course_save.n_student = n;
	fout.close();
}
void	removeStudentFromCourseIDTXT(course &course_save, student* &s, int n, string class_name, int id_delete)
{
	// Xoá tên HS nào có id trùng với id trong mảng id_delete
	// Lưu ý là HS đó sẽ không được xóa trong mảng s, mảng s vẫn như cũ
	// Lưu file [course].txt
	ofstream	fout;
	string		path;
	courseIDTXTPath(class_name, course_save.id, path);
	courseDateGenerator(course_save);
	fout.open(path);

	fout << course_save.id << endl;
	fout << course_save.name << endl;
	fout << course_save.class_name << endl;
	fout << course_save.lecturer << endl;
	fout << course_save.start_date.yyyy << " " << course_save.start_date.mm << " " << course_save.start_date.dd << endl;
	fout << course_save.end_date.yyyy << " " << course_save.end_date.mm << " " << course_save.end_date.dd << endl;
	int		count = 0;

	for (int i = 0; i < 7; i++)
	{ // Đọc thứ chứa tiết trong tuần
		if (course_save.dow[i] == false)
			fout << "0";
		else
		{
			fout << "1";
			count++;
		}
		if (i < 6)
			fout << " ";
		else
			fout << "\n"; // Vị trí cuối cần xuống dòng
	}
	int		j = 0;
	for (int i = 0; i < count; i++)
	{ // Đọc ngày giờ từng tiết học
		while (true)
		{
			if (course_save.dow[j] == true)
			{
				fout << course_save.start_hour[j].hh << " " << course_save.start_hour[j].mm << endl;
				fout << course_save.end_hour[j].hh << " " << course_save.end_hour[j].mm << endl;
				j++;
				break;
			}
			j++;
		}
	}
	fout << course_save.room << endl;
	fout << n - 1 << endl;
	for (int i = 0; i < n; i++)
	{
		if (s[i].id == id_delete)
		{
			continue;
		}
		fout << s[i].id << " ";
		fout << s[i].last_name << "," << s[i].first_name << "," << s[i].class_name << endl;
		j = 0;
		s[i].n_date = course_save.n_course_date;
		if (s[i].attendance == NULL)
			s[i].attendance = new bool[course_save.n_course_date]();
		for (j = 0; j < course_save.n_course_date; j++)
		{
			//fout << s[i].attendance[j];
			if (s[i].attendance[j])
				fout << 1;
			else
				fout << 0;
			if (j < course_save.n_course_date - 1)
				fout << " ";
			else
				fout << endl;
		}
		fout << s[i].midterm << " " << s[i].final_point << " " << s[i].lab << " " << s[i].bonus << endl;
	}
	course_save.n_student = --n;
	fout.close();
}
void	removeStudentsFromCourseIDTXT(course &course_save, student* &s, int n, string class_name, int* id_delete, int n_delete)
{
	// Xóa nhiều HS cùng một lúc
	// Xoá tên HS nào có id trùng với id trong mảng id_delete
	// Lưu ý là HS đó sẽ không được xóa trong mảng s, mảng s vẫn như cũ
	// Lưu file [course].txt
	ofstream	fout;
	string		path;
	courseIDTXTPath(class_name, course_save.id, path);
	courseDateGenerator(course_save);
	fout.open(path);

	fout << course_save.id << endl;
	fout << course_save.name << endl;
	fout << course_save.class_name << endl;
	fout << course_save.lecturer << endl;
	fout << course_save.start_date.yyyy << " " << course_save.start_date.mm << " " << course_save.start_date.dd << endl;
	fout << course_save.end_date.yyyy << " " << course_save.end_date.mm << " " << course_save.end_date.dd << endl;
	int		count = 0;

	for (int i = 0; i < 7; i++)
	{ // Đọc thứ chứa tiết trong tuần
		if (course_save.dow[i] == false)
			fout << "0";
		else
		{
			fout << "1";
			count++;
		}
		if (i < 6)
			fout << " ";
		else
			fout << "\n"; // Vị trí cuối cần xuống dòng
	}
	int		j = 0;
	for (int i = 0; i < count; i++)
	{ // Đọc ngày giờ từng tiết học
		while (true)
		{
			if (course_save.dow[j] == true)
			{
				fout << course_save.start_hour[j].hh << " " << course_save.start_hour[j].mm << endl;
				fout << course_save.end_hour[j].hh << " " << course_save.end_hour[j].mm << endl;
				j++;
				break;
			}
			j++;
		}
	}
	fout << course_save.room << endl;
	fout << n - n_delete << endl;
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i].id == s[id_delete[index] - 1].id)
		{
			if (index < n_delete - 1)
				index++;
			continue;
		}
		fout << s[i].id << " ";
		fout << s[i].last_name << "," << s[i].first_name << "," << s[i].class_name << endl;
		j = 0;
		s[i].n_date = course_save.n_course_date;
		if (s[i].attendance == NULL)
			s[i].attendance = new bool[course_save.n_course_date]();
		for (j = 0; j < course_save.n_course_date; j++)
		{
			//fout << s[i].attendance[j];
			if (s[i].attendance[j])
				fout << 1;
			else
				fout << 0;
			if (j < course_save.n_course_date - 1)
				fout << " ";
			else
				fout << endl;
		}
		fout << s[i].midterm << " " << s[i].final_point << " " << s[i].lab << " " << s[i].bonus << endl;
	}
	course_save.n_student = n - n_delete;
	fout.close();
}
void	saveAllStudentCourse(student* &s, int n, const course &c, int start_yr, int end_yr, int term_no)
{
	// Lưu thông tin khóa học vào tất cả hs chứa trong mảng student s

	academic_year*	student_yr = NULL;
	int				n_yr = 0;
	for (int i = 0; i < n; i++)
	{
		loadStudentData(s[i], student_yr, n_yr, s[i].class_name, s[i].id);
		addCourseToStructAcademicYear(c, student_yr, n_yr, start_yr, end_yr, term_no);
		saveStudent(s[i], student_yr, n_yr);
		delete[] student_yr;
		student_yr = NULL;
		n_yr = 0;
	}
	if (student_yr != NULL)
		delete[] student_yr;
}
void	removeAStudentNameInCourseTXT(const student &s, const string &course_id)
{
	course		course_save;
	student		*student_list = NULL;
	int			n_student = 0;
	readCourseIDTXT(course_id, course_save, student_list, n_student, s.class_name);
	// Lưu file [course].txt
	ofstream	fout;
	string		path;
	courseIDTXTPath(s.class_name, course_save.id, path);
	courseDateGenerator(course_save);
	fout.open(path);

	fout << course_save.id << endl;
	fout << course_save.name << endl;
	fout << course_save.class_name << endl;
	fout << course_save.lecturer << endl;
	fout << course_save.start_date.yyyy << " " << course_save.start_date.mm << " " << course_save.start_date.dd << endl;
	fout << course_save.end_date.yyyy << " " << course_save.end_date.mm << " " << course_save.end_date.dd << endl;
	int		count = 0;

	for (int i = 0; i < 7; i++)
	{ // Đọc thứ chứa tiết trong tuần
		if (course_save.dow[i] == false)
			fout << "0";
		else
		{
			fout << "1";
			count++;
		}
		if (i < 6)
			fout << " ";
		else
			fout << "\n"; // Vị trí cuối cần xuống dòng
	}
	int		j = 0;
	for (int i = 0; i < count; i++)
	{ // Đọc ngày giờ từng tiết học
		while (true)
		{
			if (course_save.dow[j] == true)
			{
				fout << course_save.start_hour[j].hh << " " << course_save.start_hour[j].mm << endl;
				fout << course_save.end_hour[j].hh << " " << course_save.end_hour[j].mm << endl;
				j++;
				break;
			}
			j++;
		}
	}
	fout << course_save.room << endl;
	fout << n_student - 1 << endl;
	for (int i = 0; i < n_student; i++)
	{
		if (student_list[i] == s)
			continue;
		fout << student_list[i].id << " ";
		fout << student_list[i].last_name << "," << student_list[i].first_name << "," << student_list[i].class_name << endl;
		j = 0;
		student_list[i].n_date = course_save.n_course_date;
		if (student_list[i].attendance == NULL)
			student_list[i].attendance = new bool[course_save.n_course_date]();
		for (j = 0; j < course_save.n_course_date; j++)
		{
			if (student_list[i].attendance[j])
				fout << 1;
			else
				fout << 0;
			if (j < course_save.n_course_date - 1)
				fout << " ";
			else
				fout << endl;
		}
		fout << student_list[i].midterm << " " << student_list[i].final_point << " " << student_list[i].lab << " " << student_list[i].bonus << endl;
	}
	course_save.n_student = n_student - 1;
	fout.close();
	delete[]student_list;
}
void	removeAStudentNameInAllCourseIDTXT(const student &s, academic_year* &c, int n_c)
{
	// Xóa tên học sinh trong TẤT CẢ các file khóa học có tên HS đó
	for (int i = 0; i < n_c; i++)
	{
		for (int j = 0; j < c[i].n_term; j++)
		{
			for (int k = 0; k < c[i].terms[j].n_course; k++)
			{
				removeAStudentNameInCourseTXT(s, c[i].terms[j].courses[k].id);
			}
		}
	}
}
template <class COURSE> void	saveAllCourseToAllStudent(student *&s, int n_student, COURSE *&c, int n_course, int start_yr, int end_yr, int term_no)
{
	academic_year*	student_yr = NULL;
	int				n_yr = 0;
	for (int i = 0; i < n_student; i++)
	{
		loadStudentData(s[i], student_yr, n_yr, s[i].class_name, s[i].id);
		for (int j = 0; j < n_course; j++)
			addCourseToStructAcademicYear(c[j], student_yr, n_yr, start_yr, end_yr, term_no);
		saveStudent(s[i], student_yr, n_yr);
		delete[] student_yr;
		student_yr = NULL;
		n_yr = 0;
	}
	if (student_yr != NULL)
		delete[] student_yr;
}
bool	importStudentToCourse(course &c, student* &s, int &n)
{
	// Tự dộng thêm hs vào khóa học
	// Course c:  khóa học cần thêm
	// student: mảng chứa student của một lớp
	// n: Số Hs trong student

	fstream		fin;
	string		path;
	classTXTPath(c.class_name, path);
	fin.open(path);
	if (fin.fail())
		return false;
	if (!readStudentList(s, n, c.class_name))
		return false;
	c.n_student = n;
	return true;
}

// semester.txt
bool	readSemesterTXT(academic_year* &year, int &n)
{
	ifstream fin;
	fin.open("data\\semester.txt");
	if (fin.fail())
		return false;
	readSemesterCourses(fin, year, n);
	fin.close();
	return true;
}
void	saveSemesterTXT(academic_year* &year, int n)
{
	ofstream fout;
	_mkdir("\\data");
	fout.open("data\\semester.txt");
	saveSemesterCourses(fout, year, n);
	fout.close();
}
/////////////////////////////////////
template <class COURSE> int	isCourseInSemesterTXTExist(COURSE &c)
{
	// Kiểm tra cousre đã tồn tại hay không bằng cách tìm course trong file semester.txt
	// Return 1: Tìm thấy
	// 0: Không tìm thấy
	// -1: Không mở được file

	academic_year*		yr = NULL;
	int					n = 0;
	if (!readSemesterTXT(yr, n))
		return -1; //File ko tồn tại
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < yr[i].n_term; j++)
		{
			for (int k = 0; k < yr[i].terms[j].n_course; k++)
			{
				if (yr[i].terms[j].courses[k] == c)
				{
					delete[] yr;
					return 1; // Tìm thấy
				}
			}
		}
	}
	delete[] yr;
	return 0; // Không tìm thấy
}
void	readSemesterCourses(ifstream &fin, academic_year* &year, int &n)
{
	fin >> n;
	if (year != NULL)
		delete[]year;
	if (n == 0)
		return;
	year = new academic_year[n];
	for (int i = 0; i < n; i++)
	{
		fin >> year[i].start;
		fin >> year[i].end;
		fin >> year[i].n_term;
		if (year[i].n_term == 0)
		{
			fin.ignore();
			continue;
		}
		year[i].terms = new term[year[i].n_term];
		for (int j = 0; j < year[i].n_term; j++)
		{
			fin >> year[i].terms[j].no;
			fin >> year[i].terms[j].n_course;
			if (year[i].terms[j].n_course == 0)
			{
				fin.ignore();
				continue;
			}
			year[i].terms[j].courses = new courseID[year[i].terms[j].n_course];
			fin.ignore();
			for (int k = 0; k < year[i].terms[j].n_course; k++)
			{
				getline(fin, year[i].terms[j].courses[k].id, ' ');
				if (k < year[i].terms[j].n_course - 1)
					getline(fin, year[i].terms[j].courses[k].class_name, ' ');
				else
					getline(fin, year[i].terms[j].courses[k].class_name, '\n');
			}
		}
	}
}
void	saveSemesterCourses(ofstream &fout, academic_year* &year, int n)
{
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << year[i].start << " " << year[i].end << endl;
		if (year[i].n_term == 0)
		{
			fout << 0 << endl;
			continue;
		}
		fout << year[i].n_term << endl;
		for (int j = 0; j < year[i].n_term; j++)
		{
			if (year[i].terms[j].n_course == 0)
			{
				fout << year[i].terms[j].no << " " << 0 << endl;
				continue;
			}
			fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
			for (int k = 0; k < year[i].terms[j].n_course; k++)
			{
				fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
				if (k < year[i].terms[j].n_course - 1)
					fout << " ";
				else
					fout << endl;
			}
		}
	}
}
template <class COURSE> void	removeACourseInSemesterCourses(ofstream &fout, academic_year* year, int n, const COURSE &c_delete)
{
	// Xoá tên một khóa học trong file 
	// Lưu ý là không xóa khóa học đó trong mảng year;
	fout << n << endl;
	int get_delete_term = 0,
		i = 0, j = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < year[i].n_term; j++)
		{
			for (k = 0; k < year[i].terms[j].n_course; k++)
			{

				if (c_delete.id == year[i].terms[j].courses[k].id)
					break;
			}
			if (k < year[i].terms[j].n_course)
			{
				break;
			}
		}
		if (j < year[i].terms[j].n_course)
		{
			get_delete_term = j;
			break;
		}
	}
	for (int i = 0; i < n; i++)
	{
		fout << year[i].start << " " << year[i].end << endl;
		fout << year[i].n_term << endl;
		for (int j = 0; j < year[i].n_term; j++)
		{
			if (j == get_delete_term)
			{
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course - 1;
				if (year[i].terms[j].n_course != 1)
					fout << " ";
			}
			else
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
			for (int k = 0; k < year[i].terms[j].n_course; k++)
			{
				if (c_delete.id == year[i].terms[j].courses[k].id)
				{
					if (year[i].terms[j].n_course == 1 || k == year[i].terms[j].n_course - 1)
						fout << endl;
					continue;
				}
				fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
				if (k < year[i].terms[j].n_course - 1)
					fout << " ";
				else
					fout << endl;
			}
		}
	}
}
template <class COURSE> bool	addCourseToStructAcademicYear(const COURSE &c, academic_year* &years, int &n_year, int start_yr, int end_yr, int term_no)
{
	int i;
	for (i = 0; i < n_year; i++) //Tìm vị trí chứa năm học có khóa học trong mảng, nếu không tìm thấy thì tạo năm học mới
	{
		if (years[i].start == start_yr && years[i].end == end_yr)
			break;
	}
	if (i < n_year) //Nếu năm học đó rồi
	{
		int j; // Kiểm tra đã tồn tại học kỳ hay chưa
		for (j = 0; j < years[i].n_term; j++)
		{
			if (years[i].terms[j].no == term_no)
				break;
		}
		if (j < years[i].n_term)
		{
			int k = 0;
			for (int k = 0; k < years[i].terms[j].n_course; k++)
			{
				if (years[i].terms[j].courses[k].id == c.id && years[i].terms[j].courses[k].class_name == c.class_name)
					return 0; // Đã tồn tại khóa học
			}
			int temp = years[i].terms[j].n_course;
			moreSize(years[i].terms[j].courses, years[i].terms[j].n_course);
			years[i].terms[j].courses[temp].id = c.id;
			years[i].terms[j].courses[temp].class_name = c.class_name;
			//years[i].terms[j].n_course++;
		}
		else
		{
			int temp = years[i].n_term;
			moreSize(years[i].terms, years[i].n_term);
			moreSize(years[i].terms[temp].courses, years[i].terms[temp].n_course);
			years[i].terms[temp].n_course = 1;
			years[i].terms[temp].no = term_no;
			years[i].terms[j].courses[0].id = c.id;
			years[i].terms[j].courses[0].class_name = c.class_name;

		}
	}
	else // Nếu chưa có năm học nào
	{
		int temp = n_year;
		moreSize(years, n_year);
		moreSize(years[temp].terms, years[temp].n_term);
		moreSize(years[temp].terms[0].courses, years[temp].terms[0].n_course);
		years[temp].start = start_yr;
		years[temp].end = end_yr;
		years[temp].terms[0].no = term_no;
		years[temp].terms[0].courses[0].id = c.id;
		years[temp].terms[0].courses[0].class_name = c.class_name;
	}
	return true;
}
bool	addCourseToSemesterTXT(const course &c, int start_yr, int end_yr, int term_no)
{
	// Thêm thông tin khóa học vèo file semester.txt
	int						 n_yr = 0;
	academic_year* yr = NULL;
	readSemesterTXT(yr, n_yr);

	if (addCourseToStructAcademicYear(c, yr, n_yr, start_yr, end_yr, term_no))
	{
		saveSemesterTXT(yr, n_yr);
		delete[] yr;
		return 1;
	}
	delete[] yr;
	return 0;
}
int		readCurrentSemesterOfAClass(courseID* &current, int &n_course, string class_name)
{
	time_t	bg = time(0);
	tm		now;
	int		sem = getCurrentSemester();
	int		n_all = 0,
		i = 0, j = 0, k = 0;
	academic_year *all_year = NULL;
	localtime_s(&now, &bg);
	if (!readSemesterTXT(all_year, n_all))
		return -1;
	for (i = 0; i < n_all; i++)
	{
		if (sem == 2 || sem == 3)
			if (all_year[i].end == now.tm_year + 1900)
				break;
		if (sem == 1)
			if (all_year[i].start == now.tm_year + 1900)
				break;
	}
	if (i >= n_all)
	{
		delete[] all_year;
		return 0;
	}
	for (j = 0; j < all_year[i].n_term; j++)
	{
		if (sem == all_year[i].terms[j].no)
			break;
	}
	if (j >= all_year[i].n_term)
	{
		delete[] all_year;
		return 0;
	}
	n_course = 0;
	for (k = 0; k < all_year[i].terms[j].n_course; k++)
	{
		if (all_year[i].terms[j].courses[k].class_name == class_name)
			push_back(current, n_course, all_year[i].terms[j].courses[k]);
	}
	delete[] all_year;
	if (n_course == 0)
	{
		return 0;
	}
	return 1;
}

// lecturer.txt
bool	readLecturerTXT(lecturer* &lecturers, int &n)
{
	ifstream fin;
	fin.open("data\\lecturer.txt");
	if (fin.fail())
		return false;

	fin >> n;
	fin.ignore();
	if (lecturers != NULL)
		delete[]lecturers;
	if (n == 0)
	{
		fin.ignore();
		return true;
	}
	lecturers = new lecturer[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, lecturers[i].account, '\n');
		getline(fin, lecturers[i].name, '\n');
		getline(fin, lecturers[i].password, '\n');
		readSemesterCourses(fin, lecturers[i].years, lecturers[i].n_year);
	}
	return true;
}
void	saveLecturerTXT(lecturer* &lecturers, int n)
{
	ofstream fout;
	_mkdir("\\data");
	fout.open("data\\lecturer.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << lecturers[i].account << endl;
		fout << lecturers[i].name << endl;
		fout << lecturers[i].password << endl;
		saveSemesterCourses(fout, lecturers[i].years, lecturers[i].n_year);
	}
}
int		addCourseToLecturerTXT(lecturer &l, const course &c, int start_yr, int end_yr, int term_no)
{
	// Thêm khóa học vào lecturer l trong file lecturer txt
	// return 1: Thêm thành công
	// 0: Không thành công
	// -1: Không mở được file

	if (!isLecturerExist(l))
		return -1; //GV không tồn tại

	lecturer*	lecturers = NULL;
	int			n = 0;
	readLecturerTXT(lecturers, n);
	if (addCourseToStructAcademicYear(c, l.years, l.n_year, start_yr, end_yr, term_no))
	{
		for (int i = 0; i < n; i++)
		{
			if (lecturers[i].account == l.account)
			{
				lecturers[i] = l;
				break;
			}
		}
		saveLecturerTXT(lecturers, n);
		delete[] lecturers;
		return 1;
	}
	delete[] lecturers;
	return 0;
}
int		isLecturerExist(lecturer &l)
{
	// Kiểm tra tồn tại tài khoản lecturer trong file lecturer.txt hay không
	// return 0: không tìm thấy
	// 1: Tìm thấy 
	// -1: Không có file lecturer.txt
	// Nếu tìm thấy thì lưu thông tin lecturer vào l

	lecturer*			lecturers = NULL;
	int					n_lecturer = 0;
	if (!readLecturerTXT(lecturers, n_lecturer))
	{
		delete[] lecturers;
		return -1; // Ko tồn tại file lecturer.txt
	}
	for (int i = 0; i < n_lecturer; i++)
	{
		if (l.account == lecturers[i].account)
		{
			/*l.name = lecturers[i].name;
			l.n_year = lecturers[i].n_year;
			l.years = new academic_year[l.n_year];
			*/
			l = lecturers[i];
			delete[] lecturers;
			return 1; // Tìm thấy
		}
	}
	delete[] lecturers;
	return 0; // Không tìm thấy
}

void	resetPassword(string lecturer_acc);
int		function01(string &user_name)
{
	textColor(NormalT);
	cout << "\t\t\t\t\t\t\t      ";
	textColor(TitleFunc);
	cout << "Login" << endl;

	student		s;
	lecturer	l;
	int			login = 0;
	textColor(NormalT);
	cout << "Username: ";
	textColor(Input__);
	getline(cin, user_name, '\n');
	while (true)
	{
		login = loginAccount(user_name, s, l);
		if (login == 0)
		{
			textColor(Notice);
			cout << "    The username you entered is invalid! ";
			cout << "Please try to enter it again." << endl;
			textColor(NormalT);
			cout << "\nUsername: ";
			textColor(Input__);
			getline(cin, user_name, '\n');
		}
		else
		{
			textColor(NormalT);
			break;
		}
	}
	textColor(NormalT);
	int limit = 0;

	while (true)
	{
		cout << "Enter your password: ";
		string		pass,
			pass_from_file;
		int i = 0;
		int get_pass_character;
		int detect_arrow_key = 0;
		pass = "";
		while (true)
		{
			get_pass_character = _getch();
			if (get_pass_character && get_pass_character != 224)
			{
				if (get_pass_character != '\b' && get_pass_character != '\r')
				{
					cout << '*';
					pass += get_pass_character;
				}
				if (get_pass_character == 8 && pass.length() >= 0)
				{
					if (pass.length() > 0)
					{
						pass.pop_back();
						cout << "\b \b";
					}
					if (pass.length() == 0)
					{
						cout << " \b";
					}
				}
				if (get_pass_character == 13)
				{
					break;
				}
			}
			else
			{
				detect_arrow_key = _getch();
			}
		}
		//cout << "\nYour password you have inputed is: " << pass << endl;
		string		real_pass = sha256(pass);
		if (login == 1)
			pass_from_file = s.password;
		else
			if (login == 10)
				pass_from_file = l.password;
			else
				pass_from_file = readAdminPassword();
		if (!(real_pass == pass_from_file))
		{
			textColor(Notice);
			limit++;
			if ((limit >= 0) && (limit < 5))
			{
				cout << "\n    Invalid inputted password, please try to input again!" << endl;
				if (limit == 4)
				{
					cout << "*Please try to input the last time! If you are wrong at this time, you need to try at another time!" << endl;
					if (login == 100 || login == 10) // Nếu là admin nhập sai mk thì reset mk
					{
						cout << "We will reset the password if you atempt to input invalid password fifth times" << endl;
					}
				}
				textColor(NormalT);
				continue;
			}
			if (limit == 5)
			{
				cout << "\n    You have inputed wrong fifth times, please try again at another time!" << endl;
				if (login == 100)
				{
					string file_name = "data\\" + sha256("admin");
					remove(file_name.c_str());
				}
				if (login == 10)
				{
					resetPassword(user_name);
				}
				textColor(WOInfo);
				cout << "\nPlease press 'Enter'!!" << endl;
				textColor(NormalT);
				_getch();
				exit(0);
			}
		}
		else
		{
			textColor(NormalT);
			break;
		}
	}
	textColor(Notice);
	cout << "\n    Login successfully!" << endl;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go continue!!" << endl;
	textColor(NormalT);
	_getch();
	return login;
}
void	function06()
{
	// 6.	Import students of a class such as 18CLC6 from a csv file.
	textColor(NormalT);
	cout << "\t\t\t\t\t      ";
	textColor(TitleFunc);
	cout << "Import Student from CSV file" << endl;
	do
	{
		textColor(NormalT);
		cout << "Do you want to: " << endl
			<< "    1. Import CSV file if the CSV file is the same directory as the program file" << endl
			<< "    2. Input the directory to the CSV file" << endl
			<< "    3. Show me the CSV template" << endl
			<< "    4.../Back" << endl;
		textColor(Notice);
		cout << "    !The CSV file MUST be in this Format: No-ID-LastName-FisrtName-Gender-DoB" << endl;

		int		confirm = askCommand(4);
		string	path,
			class_name;
		do
		{
			switch (confirm)
			{
			case 1:
			{
				textColor(NormalT);
				cout << "    ";
				textColor(SpTitleFunc);
				cout << "You choose the command which use to import CSV file if the CSV file is the same directory as the program file!" << endl;
				textColor(NormalT);
				cout << "\tInput the name of the CSV file ";
				textColor(WOInfo);
				cout << "(eg: 18CLC6.csv)";
				textColor(NormalT);
				cout << ": ";
				break;
			}
			case 2:
			{
				textColor(NormalT);
				cout << "    ";
				textColor(SpTitleFunc);
				cout << "You choose the command which use to input the directory to the CSV file!" << endl;
				textColor(NormalT);
				cout << "\tInput the directory to the CSV file ";
				textColor(WOInfo);
				cout << "(eg: D:\\data\\18CLC6.csv)";
				textColor(NormalT);
				cout << ": ";
				break;
			}
			case 3:
			{
				textColor(NormalT);
				cout << "    ";
				textColor(SpTitleFunc);
				cout << "You choose the command which use to show me the CSV template!" << endl;
				showStudentCSVTemplate();
				exportStudentCSVTemplate();
				textColor(Notice);
				cout << "\t    !!!You can check file '[Class_name].csv" << endl;
				textColor(NormalT);
				break;
			}
			case 4:
			{
				textColor(NormalT);
				return;
			}
			default:
				break;
			}
			if (confirm != 3)
				break;
			cout << "\tDo you want to: " << endl
				<< "\t    1. Import CSV file if the CSV file is the same directory as the program file" << endl
				<< "\t    2. Input the directory to the CSV file" << endl
				<< "\t    3. ../Back";
			confirm = askCommand(3);
			if (confirm == 3)
				return;
		} while (true);
		textColor(Input__);
		getline(cin, path);
		textColor(NormalT);
		cout << "\tCLass: ";
		textColor(Input__);
		getline(cin, class_name, '\n');
		if (class_name.length() < 1)
		{
			classNameExtractor(path, class_name);
			textColor(Notice);
			cout << "\t    Choosing the class which you use it to import CSV!" << endl
				<< "\tBecause you are not choose anything so it means that we will choose " << class_name << "." << endl;
			textColor(NormalT);
		}
		strUpr(class_name);

		student*		s = NULL; //Một lớp hơn trăm HS vẫn được!
		studentID*		existed_student = NULL;
		int				n = 0,
			n_existed = 0;
		int				ans = checkStudentCSV(s, n, path, class_name, existed_student, n_existed);

		textColor(Notice);
		switch (ans)
		{
		case -1:
			cout << "    !Invalid Format" << endl;
			break;
		case -111:
			cout << "    !Invalid date Format" << endl;
			break;
		case -100:
			cout << "    !Invalid directory" << endl;
			break;
		case 1:
		{
			showAllInfoStudentList(s, n, true);
			//File thông tin HS lưu trữ trong data\[tên lớp]\s[MSSV].txt
			exportStudentTXT(s, n, class_name);

			// Lưu danh sách HS để tiện đường tìm 
			exportStudentList(s, n, class_name);
			addClass(class_name);
			textColor(Notice);
			cout << "    Import student information from .CSV file successfully!" << endl;
			textColor(NormalT);
			break;
		}
		default:
			break;
		}
		if (ans < 0)
		{
			if (s != NULL)
				delete[] s;
			if (existed_student != NULL)
				delete[]existed_student;
			textColor(NormalT);
			cout << "    Do you want to continue (Yes/No/?): ";
			if (yesNoAns())
			{
				textColor(NormalT);
				continue;
			}
			else
			{
				textColor(Notice);
				cout << "    Stop Importing .CSV file." << endl;
				textColor(WOInfo);
				cout << "\nPlease press 'Enter' to go back" << endl;
				textColor(NormalT);
				_getch();
				return;
			}
		}
		else if (ans == 0)
		{
			textColor(Notice);
			cout << "\t    Some of the data is existed in the program!!!" << endl;
			textColor(NormalT);
			cout << "\t    So, what would you want to do?" << endl
				<< "\t\t0. Show me the information of existed student(s)" << endl
				<< "\t\t1. Skip student(s) who already has data" << endl
				<< "\t\t2. Delete ALL existing data and importing ALL student(s)" << endl
				<< "\t\t3. Stop import" << endl << "\t";
			int command_e = askCommand(0, 3);
			if (command_e == 0)
			{
				showStudentList(existed_student, n_existed, true);
				cout << endl;
				textColor(NormalT);
				cout << "\tDo you want to:" << endl
					<< "\t    1. Skip student(s) who already has data" << endl
					<< "\t    2. Delete ALL existing data and importing ALL student(s)" << endl
					<< "\t    3. Stop import" << endl;
				command_e = askCommand(3);
			}
			if (command_e != 3)
				importStudentCSV(s, n, existed_student, n_existed, command_e);
		}
		if (s != NULL)
			delete[] s;
		if (existed_student != NULL)
			delete[] existed_student;
		textColor(NormalT);
		cout << "Do you want to import another CSV file? (Yes/No/?): ";
		if (yesNoAns())
		{
			textColor(NormalT);
			cout << endl;
			continue;
		}
		else
		{
			textColor(NormalT);
			cout << endl;
			break;
		}
	} while (true);
	textColor(NormalT);
}
void	function07()
{
	// 7.	Manually add a new student to a class. 
	student		s;
	cout << "\t\t\t\t\t    ";
	textColor(TitleFunc);
	cout << "Input the student's information" << endl;
	textColor(NormalT);
	cout << "    Student ID: ";
	getNum(s.id);

	if (isStudentExist(s.id))
	{
		textColor(Notice);
		cout << "    The ID of the student existed!!!" << endl;
		textColor(NormalT);
		cout << "Do you want to edit the data of that student? (Yes/No/?): ";
		if (!yesNoAns())
		{
			textColor(Notice);
			cout << "    Stop adding new student" << endl;
			textColor(NormalT);
			return;
		}
		else
		{
			cout << endl;
			function08();
			textColor(NormalT);
			return;
		}
	}
	textColor(NormalT);
	cout << "    Class: ";
	textColor(Input__);
	cin >> s.class_name;
	addClass(s.class_name);
	strUpr(s.class_name);
	cin.ignore();
	textColor(NormalT);
	cout << "    Last name: ";
	textColor(Input__);
	getline(cin, s.last_name, '\n');
	textColor(NormalT);
	cout << "    First name: ";
	textColor(Input__);
	getline(cin, s.first_name, '\n');

	while (true)
	{
		textColor(NormalT);
		cout << "    Gender (0: Male, 1: Female, -1: Other): ";
		getNum(s.gender);
		if (-1 <= s.gender && s.gender <= 1)
		{
			textColor(NormalT);
			break;
		}
		textColor(Notice);
		cout << "    !Invalid Input" << endl;
	}
	while (true)
	{
		textColor(NormalT);
		cout << "    Date Of Birth:" << endl;
		cout << "\tDay: ";
		getNum(s.dob.dd);
		cout << "\tMonth: ";
		getNum(s.dob.mm);
		cout << "\tYear:";
		getNum(s.dob.yyyy);
		if (!checkValidDate(s.dob))
		{
			textColor(Notice);
			cout << "    !Invalid date, please try again." << endl;
		}
		else
		{
			textColor(NormalT);
			break;
		}
	}
	studentAccountGenerator(s);
	addNewStudent(s);
	textColor(Notice);
	cout << "    Add new student to class " << s.class_name << " sucessfully!!" << endl;
	cout << endl;
	textColor(NormalT);
	// Thêm Các khóa học hiện tại vào các file HS mới import
	courseID	*current_course = NULL;
	int			n_current = 0;
	if (readCurrentSemesterOfAClass(current_course, n_current, s.class_name) == 1)
	{
		textColor(NormalT);
		cout << "Do you want to add this new student to all current courses?: ";
		bool _ans = yesNoAns();
		int count__ = 0;
		do
		{
			if (_ans == true)
			{
				time_t	bg = time(0);
				tm		now;
				int		sem = getCurrentSemester(),
					start_yr = 0, end_yr = 0;
				localtime_s(&now, &bg);

				if (sem == 1)
				{
					start_yr = now.tm_year + 1900;
					end_yr = start_yr - 1;
				}
				else
				{
					start_yr = now.tm_year + 1900 - 1;
					end_yr = start_yr + 1;
				}
				student *s1 = new student[1],
					*student_list = NULL;
				int		n_new = 1,
					n_list = 0;
				s1[0] = s;
				saveAllCourseToAllStudent(s1, n_new, current_course, n_current, start_yr, end_yr, sem);
				for (int i = 0; i < n_current; i++)
				{
					course c;
					readCourseIDTXT(current_course[i].id, c, student_list, n_list, s.class_name);
					push_back(student_list, n_list, s);
					sortAscending(student_list, n_list);
					saveCourseIDTXT(c, student_list, n_list, s.class_name);
					delete[] student_list;
					student_list = NULL;
				}
				textColor(Notice);
				cout << "    Adding this student to all current courses successfully!!" << endl;
				textColor(NormalT);
				return;
			}
			else
			{
				count__++;
				textColor(Notice);
				cout << "    Are you sure? This student will not be added to all current courses." << endl;
				textColor(NormalT);
				cout << "Please answer this question again. Do you want to add this new student to all current courses?: ";
				_ans = yesNoAns();
				if (!_ans)
				{
					count__++;
					textColor(Notice);
					cout << "    Stop adding this student to all current courses!" << endl;
				}
			}
		} while (count__ < 2);
	}
	textColor(NormalT);
}
void	function08()
{
	cout << "\t\t\t\t\t\t";
	textColor(TitleFunc);
	cout << "Edit an existing student";
	textColor(NormalT);
	do
	{
		int		id;
		student	s;
		cout << "\nPlease input student ID: ";
		getNum(id);
		if (!findStudentByID(id, s))
		{
			textColor(Notice);
			cout << "    The ID doesn't exist!!" << endl;
			textColor(NormalT);
			cout << "Do you want to continue (Yes/No/?): ";
			if (!yesNoAns())
				return;
			else
				continue;
		}
		textColor(NormalT);
		cout << "Do you want to edit: " << endl
			<< "    1. Edit ALL information of the student" << endl
			<< "    2. Edit some information of the student" << endl
			<< "    3. ../Back" << endl;
		int edit_mode = askCommand(3);
		cout << endl;
		if (edit_mode == 1)
			editAllDataOfAStudent(s);
		else if (edit_mode == 2)
			editSomeDataOfAStudent(s);
		else
			return;
		textColor(NormalT);
		cout << "Do you want to edit any information of another student? (Yes/No/?): ";
		if (!yesNoAns())
		{
			textColor(Notice);
			cout << "    Stop editing student(s)'s information" << endl;
			textColor(NormalT);
			break;
		}
	} while (true);
	textColor(NormalT);
}
void	function09()
{
	student			s;
	int				id, n_course;
	academic_year*	student_course = NULL;
	cout << "\t\t\t    ";
	textColor(TitleFunc);
	cout << "Removing a student (with every infomation of him/her) from class" << endl;
	textColor(NormalT);
	do
	{
		cout << "Input the ID of the student whom you want to remove: ";
		getNum(id);
		if (!findStudentByID(id, s))
		{
			textColor(Notice);
			cout << "    The ID inexists!" << endl;
			textColor(NormalT);
			cout << "\nDo you want to continue? (Yes/No/?): ";
			if (yesNoAns())
			{
				textColor(NormalT);
				continue;
			}
			else
			{
				textColor(Notice);
				cout << "    Stop removing student(s)." << endl;
				textColor(NormalT);
				return;
			}
		}
		textColor(WOInfo);
		cout << "    This is any information of the student who you want to remove:" << endl;
		viewProfileInfo(s.account);
		textColor(Notice);
		cout << "    After checking, do you want to remove this student?"
			<< "\n*Remember that, if you remove this student you can not restore the data of that student!" << endl;
		textColor(NormalT);
		cout << ">> (Yes/No/?): ";
		if (yesNoAns())
		{
			if (loadStudentData(s, student_course, n_course, s.class_name, s.id))
				removeAStudentNameInAllCourseIDTXT(s, student_course, n_course);
			removeStudentTXT(id, s.class_name);
			removeStudentFromStudentList(id, s.class_name);
			textColor(Notice);
			cout << "    Remove student sucessfully!\n" << endl;
			delete[]student_course;
		}
		else
		{
			textColor(Notice);
			cout << "    Stop removing this student from his/her class.\n" << endl;
		}
		textColor(NormalT);
		cout << "Do you want to delete another student? (Yes/No/?): ";
		if (!yesNoAns())
		{
			textColor(Notice);
			cout << "    Stop removing student(s)." << endl;
			textColor(NormalT);
			break;
		}
	} while (true);
	textColor(NormalT);
}
void	function10()
{
	// Change student from CLASS A to CLASS B
	cout << "\t\t     ";
	textColor(TitleFunc);
	cout << "Changing a student (with every infomation of him/her) from class A to class B" << endl;
	textColor(NormalT);
	do
	{
		cout << "Input the ID of the student whom you want to change class: ";
		int			id;
		student		s;
		getNum(id);
		if (!findStudentByID(id, s))
		{
			textColor(Notice);
			cout << "    The ID inexists!" << endl;
			textColor(NormalT);
			cout << "\nDo you want to continue? (Yes/No/?): ";
			if (yesNoAns())
			{
				textColor(NormalT);
				continue;
			}
			else
			{
				textColor(Notice);
				cout << "    Stop moving student(s) to another class." << endl;
				textColor(NormalT);
				return;
			}
		}
		textColor(WOInfo);
		cout << "    This is any information of the student who you want to change:" << endl;
		viewProfileInfo(s.account);
		textColor(Notice);
		cout << "    After checking, do you want to change this student to another class?"
			<< "\n*Remember that, if you change class of this student, you can not find information or this student at the old class." << endl;
		textColor(NormalT);
		cout << ">> (Yes/No/?): ";
		if (yesNoAns())
		{
			string class_name;
			textColor(NormalT);
			cout << "\tNew class: ";
			textColor(Input__);
			getline(cin, class_name, '\n');
			if (!isClassExist(class_name))
			{
				textColor(Notice);
				cout << "    The class: " << class_name << " is not exist in the data!!!" << endl;
				textColor(NormalT);
				cout << "    Do you want to: " << endl
					<< "\t1. Create new class " << class_name << " a move student " << s.first_name << " " << s.last_name << " to that class" << endl
					<< "\t2. Stop adding class" << endl;
				if (askCommand(2) == 2)
				{
					textColor(Notice);
					cout << "    Stop moving student and adding the new class! It means the class of this student is keep the old one!" << endl;
					textColor(NormalT);
					cout << "Do you want to move another student from her/his old class to new class? (Yes/No/?): ";
					if (yesNoAns())
					{
						textColor(NormalT);
						continue;
					}
					else
					{
						textColor(NormalT);
						return;
					}
				}
			}
			moveStudentTXT(s, class_name);
			textColor(Notice);
			cout << "    Moving student to class " << s.class_name << " sucessfully!" << endl;
			cout << "*The student name is moving to new class but they still in the old course of the old class! " << endl
				<< ">> If you would like to move the student course, please move to function 'Move student's Course' in COURSE menu" << endl;
			textColor(NormalT);
		}
		else
		{
			textColor(Notice);
			cout << "    Stop moving student! It means the class of this student is keep the old one!" << endl;
			textColor(NormalT);
		}
		cout << "Do you want to move another student from her/his old class to new class? (Yes/No/?): ";
		if (yesNoAns())
		{
			textColor(NormalT);
			continue;
		}
		else
		{
			textColor(Notice);
			cout << "    Stop moving student(s) to another class." << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
}
void	function11()
{
	// 11.	View list of classes.
	cout << "\t\t\t\t\t      ";
	textColor(TitleFunc);
	cout << "Showing the list of classes" << endl;
	string* class_name = NULL;
	int		n = 0;
	if (!readClassTXT(class_name, n))
	{
		textColor(Notice);
		cout << "    There is no class available now!" << endl;
		textColor(NormalT);
		return;
	}
	textColor(NormalT);
	cout << "\t";
	textColor(SpTitleFunc);
	if (n == 1)
		cout << "There is " << n << " classes:" << endl;
	else
		cout << "There are " << n << " classes:" << endl;
	for (int i = 0; i < n; i++)
	{
		textColor(NormalT);
		student*	s = NULL;
		int			n_s = 0;
		readStudentList(s, n_s, class_name[i]);
		cout << "\t\t\t\t" << setw(6) << left << class_name[i] << ": ";
		textColor(OInfo);
		cout << n_s << " student(s)" << endl;
		delete[] s;
	}
	cout << endl;
	textColor(Notice);
	cout << ">>Press 'Enter' to go back Class menu!!!" << endl;
	delete[]class_name;
	textColor(NormalT);
	_getch();
}
void	function12()
{
	// 12. View list of students in a class.
	cout << "\t\t\t\t\t  ";
	textColor(TitleFunc);
	cout << "Showing list of students in a class" << endl;
	string*		class_name = NULL;
	int			n = 0;
	if (!readClassTXT(class_name, n))
	{
		textColor(Notice);
		cout << "    There is no class available now!!" << endl;
		cout << ">>Press Any key to go back class menu" << endl;
		textColor(NormalT);
		_getch();
		return;
	}
	do
	{
		textColor(NormalT);
		cout << "Please choose class to view student list: " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "    " << i + 1 << ". " << class_name[i] << endl;
		}
		cout << "    " << n + 1 << ".../Back" << endl;
		int			command = askCommand(n + 1);
		if (command == (n + 1))
		{
			delete[] class_name;
			return;
		}
		student*	s = NULL;
		int n_s = 0;
		readStudentList(s, n_s, class_name[command - 1]);
		cout << "    Do you want to: " << endl
			<< "\t1. Quick view" << endl
			<< "\t2. Full view" << endl;
		int			view_mode = askCommand(2);
		cout << "\n";
		if (view_mode == 1)
		{
			cout << "\t    ";
			textColor(SpTitleFunc);
			cout << setfill('*') << setw(22) << "*"
				<< "This is student list of class " << class_name[command - 1] << setw(22) << "*" << setfill(' ') << endl;
			showStudentList(s, n_s, false);
		}
		else
		{
			for (int i = 0; i < n_s; i++)
			{
				readStudentData(s[i].id, s[i].class_name, s[i]);
			}
			showAllInfoStudentList(s, n_s, false);
		}
		cout << endl;
		delete[]s;
	} while (true);
	delete[]class_name;
}
void	function14Old()
{
	// 14. Import semester.txt
	cout << "\t\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Import Student from CSV file" << endl;
	do
	{
		textColor(NormalT);
		cout << "Please choose to do something with 2 command: " << endl
			<< "    1. Import CSV file if the CSV file is the same directory as the program file" << endl
			<< "    2. Input the directory to the CSV file" << endl;
		textColor(Notice);
		cout << "    !The CSV file MUST be in this Format: No,Course ID,Course Name,Class,"
			<< "Lecturer Account, Start Date, End Date, Day of Week, Start Time, End Time, Room" << endl;

		textColor(NormalT);
		int		confirm = askCommand(2);
		string	path;
		int		start_yr,
			end_yr,
			term_no;
		textColor(NormalT);
		if (confirm == 1)
		{
			cout << "    Input the name of the CSV file";
			textColor(OInfo);
			cout << " (eg: Semester2_6.csv) : ";
		}
		else
		{
			cout << "    Input the directory to the CSV file ";
			textColor(OInfo);
			cout << "(eg: D:\\data\\Semester2_6.csv): ";
		}
		textColor(Input__);
		getline(cin, path, '\n');
		textColor(NormalT);
		cout << "\tAcademic year: " << endl;
		cout << "\t    Start year: ";
		textColor(Input__);
		cin >> start_yr;
		textColor(NormalT);
		cout << "\t    End year: ";
		textColor(Input__);
		cin >> end_yr;
		textColor(NormalT);
		cout << "\t    Semester: (1: Fall, 2:Spring, 3:Summer)" << endl;
		term_no = askCommand(3);

		course*		c = NULL;
		int			n = 0;
		textColor(NormalT);
		bool		ans = importSemesterCSV(c, n, path, start_yr, end_yr, term_no);
		cout << endl;
		if (ans)
		{
			string		sTitle = "Showing file ";
			sTitle += path;
			sTitle += " from ";
			sTitle += to_string(start_yr);
			sTitle += " to ";
			sTitle += to_string(end_yr);
			cout << "\t";
			textColor(SpTitleFunc);
			cout << "\t\t\t   " << setw(64) << left << sTitle << endl;
			for (int i = 0; i < n; i++)
			{
				textColor(NormalT);
				cout << "\t";
				textColor(InBoard);
				cout << setw(6) << left << i + 1
					<< setw(10) << left << c[i].id
					<< setw(45) << left << c[i].name
					<< setw(10) << left << c[i].class_name
					<< setw(15) << left << c[i].lecturer
					<< "[...]" << endl;
			}
			textColor(Notice);
			cout << "    Import student information from .CSV file successfully!\n" << endl;
		}
		else
		{
			textColor(Notice);
			cout << "    Invalid directory or file name, or may be the file has invalid format!\n" << endl;
		}
		textColor(NormalT);
		cout << "Do you want to do this command again? (Yes/No/?): ";
		if (c != NULL)
			delete[]c;
		n = 0;
	} while (yesNoAns());
	textColor(NormalT);
}
void	function18()
{
	cout << "\t\t\t\t\t    ";
	// Delete student(s) in a course
	textColor(TitleFunc);
	cout << "Deleting student(s) in a course" << endl;
	textColor(NormalT);
	do
	{
		course c;
		if (!askingCourseID(c))
			return;
		do
		{
			student *s = NULL;
			int n_s = 0;
			readCourseIDTXT(c.id, c, s, n_s, c.class_name);
			showStudentList(s, n_s, true);
			cout << "Do you want to: " << endl
				<< "    1. Delete one student name in a course" << endl
				<< "    2. Delete many students at once" << endl
				<< "    3.../Back" << endl;
			int select_mode = askCommand(3);
			switch (select_mode)
			{
			case 1:
			{
				cout << "Please input the ID of the student whom you want to delete: ";
				int id = 0;
				do
				{
					int i = 0;
					getNum(id);
					for (i = 0; i < n_s; i++)
					{
						if (s[i].id == id)
							break;
					}
					if (i < n_s)
						break;
					textColor(Notice);
					cout << "    Please input the ID of the student who is in this course!" << endl;
					textColor(NormalT);
					cout << ">>ID: ";
				} while (true);
				removeStudentFromCourseIDTXT(c, s, n_s, c.class_name, id);
				academic_year *yr_s = NULL;
				student s_read;
				int n_yr = 0;
				loadStudentData(s_read, yr_s, n_yr, c.class_name, id);
				removeACourseInStudentIDTXT(s_read, yr_s, n_yr, c);
				delete[]yr_s;
				textColor(Notice);
				cout << "    Remove Student Sucessfully!" << endl;
				break;
			}
			case 2:
			{
				textColor(Notice);
				cout << "    Please input students' No (NOT STUDENTS' ID)!!!" << endl
					<< "You can input many command at once!!!" << endl;
				textColor(NormalT);
				int* delete_student_list = NULL;
				int n_delete = askManyCommands(1, n_s, delete_student_list);
				removeStudentsFromCourseIDTXT(c, s, n_s, c.class_name, delete_student_list, n_delete);
				for (int i = 0; i < n_delete; i++)
				{
					academic_year *yr_s = NULL;
					student s_read;
					int n_yr = 0;
					loadStudentData(s_read, yr_s, n_yr, c.class_name, s[delete_student_list[i] - 1].id);
					removeACourseInStudentIDTXT(s_read, yr_s, n_yr, c);
					delete[]yr_s;
					textColor(Notice);
					cout << "    Remove Student Sucessfully!" << endl;
					textColor(NormalT);
					break;
				}
			}
			case 3:
			{
				break;
			}
			default:
				break;
			}
			delete[]s;
			if (select_mode == 3)
				break;
			textColor(NormalT);
			cout << "Do you want to delete another student in this course? (Yes/No/?): ";
			if (!yesNoAns())
				break;
		} while (true);
		textColor(NormalT);
		cout << "Do you want to delete another student(s) in another course? (Yes/No/?): ";
		if (!yesNoAns())
			return;
	} while (true);
}
void	function19()
{
	// Add student to a course.
	cout << "\t\t\t\t\t      ";
	textColor(TitleFunc);
	cout << "Adding student to a course" << endl;
	textColor(NormalT);
	do
	{
		course c;
		if (!askingCourseID(c))
			return;
		student *s = NULL;
		student s_read;
		int n_s = 0;
		readCourseIDTXT(c.id, c, s, n_s, c.class_name);
		do
		{
			cout << "Input the ID of the student you would like to add to course '" << c.name << "': ";
			int id = 0;
			do
			{
				int i = 0;
				getNum(id);
				for (i = 0; i < n_s; i++)
				{
					if (s[i].id == id)
						break;
				}
				if (i >= n_s && findStudentByID(id, s_read))
					break;
				textColor(Notice);
				cout << "    Please input the ID of the student who is not in this course!" << endl;
				textColor(NormalT);
				cout << "Do you want to continue? (Yes/No/?): ";
				if (!yesNoAns())
				{
					delete[]s;
					return;
				}
				cout << "ID: ";
			} while (true);
			// Thêm tên HS vào [courseID.txt]
			cout << "This is the information of the student whom you want to add: " << endl;
			viewProfileInfo(s_read.account);
			cout << "Please confirm (Yes/No/?): ";
			if (!yesNoAns())
			{
				break;
			}
			academic_year *yr_s = NULL;
			int n_yr = 0;
			loadStudentData(s_read, yr_s, n_yr, s_read.class_name, id);
			push_back(s, n_s, s_read);
			sortAscending(s, n_s);
			saveCourseIDTXT(c, s, n_s, c.class_name);
			academic_year *all_year = NULL;
			int n_all = 0;
			readSemesterTXT(all_year, n_all);
			int get_year = 0, get_sem = 0, k = 0;
			for (get_year = 0; get_year < n_all; get_year++)
			{
				for (get_sem = 0; get_sem < all_year[get_year].n_term; get_sem++)
				{
					for (k = 0; k < all_year[get_year].terms[get_sem].n_course; k++)
					{
						if (all_year[get_year].terms[get_sem].courses[k] == c)
							break;
					}
					if (k < all_year[get_year].terms[get_sem].n_course)
						break;
				}
				if (get_year < n_all)
					break;
			}
			addCourseToStructAcademicYear(c, yr_s, n_yr, all_year[get_year].start,
				all_year[get_year].start + 1, all_year[get_year].terms[get_sem].no);
			saveStudent(s_read, yr_s, n_yr);
			textColor(Notice);
			cout << "    Add student successfully" << endl;
			textColor(NormalT);
			cout << "Do you want to add another student in course '" << c.name << "' (Yes/No/?): ";
			if (!yesNoAns())
				break;
			delete[] yr_s;
			delete[] all_year;
		} while (true);
		textColor(NormalT);
		cout << "Do you want to add another student in another course? (Yes/No/?): ";
		if (!yesNoAns())
			break;
		delete[]s;
		s = NULL;
	} while (true);
}
void	function20()
{
	cout << "\t\t\t\t    ";
	textColor(TitleFunc);
	cout << "Showing list of courses in the current semester" << endl;
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	int		mm = now.tm_mon + 1;
	int		yyyy = now.tm_year + 1900;

	academic_year* year = NULL;
	int		n = 0;
	int		term_ = monthToSemesterInt(mm);
	string	term_c = monthToSemesterString(mm);

	readSemesterTXT(year, n);
	bool	flag = false;
	for (int i = 0; i < n; i++)
	{
		if (((term_ == 1) && (yyyy == year[i].start)) || (((term_ == 2) || (term_ == 3)) && (yyyy == year[i].end)))
		{
			textColor(SpTitleFunc);
			cout << "   ";
			cout << "This time belongs to the " << term_c << " semester of " << year[i].start << "-" << year[i].end << endl;
			textColor(NormalT);
			cout << "\n\t";
			textColor(TitleBoard);
			cout << "|" << setw(14) << left << "\tCourse  ||";
			cout << setw(13) << left << "Class" << "|" << endl;
			textColor(NormalT);
			cout << "\t";
			textColor(TitleBoard);
			cout << "|" << setfill('-') << setw(33) << "-" << "|" << endl << setfill(' ');
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (term_ == year[i].terms[j].no)
				{
					for (int k = 0; k < year[i].terms[j].n_course; k++)
					{
						textColor(NormalT);
						cout << "\t";
						textColor(InBoard);
						cout << "|" << "\t" << setw(8) << left << year[i].terms[j].courses[k].id << "||   ";
						cout << setw(13) << year[i].terms[j].courses[k].class_name << "|" << endl;
					}
					flag = true;
				}
			}
			textColor(NormalT);
			cout << "\t";
			textColor(InBoard);
			cout << setfill('*') << setw(35) << "*" << endl << setfill(' ');
		}
	}
	if (flag == false)
	{
		textColor(Notice);
		cout << "    This school year or semester was not found.";
	}
	cout << endl;
	textColor(NormalT);
	if (year != NULL)
		delete[]year;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	_getch();
}
void	function21()
{
	courseID c;
	cout << "\t\t\t\t\t ";
	textColor(TitleFunc);
	cout << "Showing list of students in a course" << endl;
	do
	{
		askingCourseID(c);
		course course_;
		int n = 0;
		student *s = NULL;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(NormalT);
		cout << "\n\t";
		textColor(SpTitleFunc);
		cout << setfill('*') << setw(17) << "*"
			<< "List of " << c.class_name << "'s students in course " << c.id << setfill('*') << setw(18) << "*" << setfill(' ') << endl;
		textColor(NormalT);
		cout << "\t";
		textColor(TitleBoard);
		cout << setw(10) << left << "|  No  |"
			<< setw(10) << left << "   ID" << "|  "
			<< setw(35) << left << "Lastname" << "|  "
			<< setw(15) << left << "Firstname" << "|" << endl;
		textColor(NormalT);
		cout << "\t";
		textColor(TitleBoard);
		cout << "|" << setfill('-')
			<< setw(75) << "-" << "|" << endl << setfill(' ');
		for (int i = 0; i < n; i++)
		{
			textColor(NormalT);
			cout << "\t";
			if (s[i].id == 18127244)
				textColor(DucTuan);
			else
				textColor(InBoard);
			cout << "|  " << setw(4) << left << i + 1 << "|  "
				<< setw(10) << left << s[i].id << "|  "
				<< setw(35) << left << s[i].last_name << "|  "
				<< setw(15) << left << s[i].first_name << "|" << endl;
		}
		textColor(NormalT);
		cout << "\t";
		textColor(InBoard);
		cout << setfill('*')
			<< setw(77) << "*" << endl << setfill(' ');
		textColor(Notice);
		cout << "\n   Showing the student's list of class " << c.class_name << " in " << c.id << " successfully!!\n" << endl;
		textColor(NormalT);
		cout << "Do you want to view list of another class's students in another course? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	textColor(NormalT);
}
void	function22_26()
{
	cout << "\t\t\t\t\t  ";
	textColor(TitleFunc);
	cout << "Showing attendance list of a course" << endl;
	do
	{
		courseID	c;
		if (!askingCourseID(c))
			return;
		course		course_;
		int			n;
		student		*s = NULL;
		int			count_months = 0;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		do
		{
			count_months = 0;
			textColor(NormalT);
			cout << "    Choose command you want to do something which can show what you want: " << endl;

			for (int i = 0; i < course_.end_date.mm - course_.start_date.mm + 2; i++)
			{
				if (i != course_.end_date.mm - course_.start_date.mm + 1)
				{
					cout << "\t" << course_.start_date.mm + i << ". " << intToMonth(course_.start_date.mm + count_months) << endl;
					count_months++;
				}
				else
					cout << "\t" << 12 + 1 << ". Show attendance list of all months when you have that course." << endl;
			}
			int		command;
			while (true)
			{
				textColor(NormalT);
				cout << "\t>> ";
				getNum(command);
				if (command <= course_.end_date.mm  && command >= course_.start_date.mm || command == 13)
				{
					textColor(NormalT);
					break;
				}
				textColor(Notice);
				cout << "\t!Invalid command." << endl;
			}
			if (command == 13)
			{
				textColor(Notice);
				cout << "    This course have so many sessions.\n\tSo when you want to see attendance list of all months of this course, we will add this list"
					<< "on file.csv for you." << endl;
				if (exportAttendanceCSV(s, n, course_) == true)
				{
					textColor(Notice);
					cout << "\t    Its name is 'AttendanceList " << c.id << " " << c.class_name << ".csv'." << endl;
					cout << "\t\tPlease check it right now!!!! " << endl;
				}
				else
				{
					textColor(Notice);
					cout << "\t    Sorry, The attendance list exported unsuccessfully!!!";
				}
				textColor(NormalT);
			}
			else
			{
				int	count = 0;
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						count++;
				}
				string superTitle;
				superTitle = "The attendace list of class ";
				superTitle += c.class_name;
				superTitle += " at course ";
				superTitle += c.id;
				superTitle += " of ";
				superTitle += intToMonth(command);
				textColor(SpTitleFunc);
				cout << setw((33 + 6 * count)) << left << superTitle << endl;
				textColor(TitleBoard);
				cout << setw(4) << left << "No";
				cout << setw(28) << left << "|Fullname";
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						cout << setw(3) << left << "|" << setw(3) << left << course_.course_date[i].dd;
				}
				cout << "|" << endl
					<< "    |" << setw(28) << right << "|";
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						cout << setw(2) << course_.course_date[i].start_hh << ":" << setw(2) << course_.course_date[i].start_min << "|";
				}
				cout << endl;
				cout << setfill('-');
				cout << setw((33 + 6 * count)) << "-" << endl;
				cout << setfill(' ');
				textColor(InBoard);
				for (int i = 0; i < course_.n_student; i++)
				{
					cout << setw(4) << left << i + 1;
					string		fullname = "|";
					fullname += s[i].last_name;
					fullname += " ";
					fullname += s[i].first_name;
					cout << setw(28) << left << fullname << "|";
					for (int j = 0; j < course_.n_course_date; j++)
					{
						if (course_.course_date[j].mm == command)
						{
							cout << setw(5) << left;
							if (s[i].attendance[j])
							{
								textColor(Attendance_Checkin);
								cout << "  V";
								textColor(InBoard);
								cout << "|";
							}
							else
							{
								textColor(Attendance_Absent);
								cout << "  A";
								textColor(InBoard);
								cout << "|";
							}
							textColor(InBoard);
						}
					}
					cout << endl;
				}
				textColor(InBoard);
				cout << setfill('*')
					<< setw((33 + 6 * count)) << "*" << endl << setfill(' ');
				textColor(NormalT);
				cout << "Do you want to view another month attendance list of this course of this class? (Yes/No/?): ";
				if (yesNoAns() == false)
				{
					textColor(NormalT);
					cout << endl;
					break;
				}
			}
		} while (true);
		textColor(NormalT);
		cout << "Do you want to view another attendance list? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
		if (s != NULL)
			delete[]s;
		s = NULL;
	} while (true);
}
void	function24()
{
	cout << "\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Showing scoreboard when you have ID of course" << endl;
	do
	{
		courseID	c;
		if (!askingCourseID(c))
			return;
		course		course_;
		int			n = 0;
		student		*s = NULL;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(NormalT);
		cout << "\n  ";
		textColor(SpTitleFunc);
		cout << setfill('*') << setw(31) << "*"
			<< "This is the scoreboard of class " << c.class_name << " at course " << c.id << setfill('*') << setw(31) << "*" << setfill(' ') << endl;
		textColor(NormalT);
		cout << "  ";
		textColor(TitleBoard);
		cout << "|  No  |  "
			<< setw(10) << left << "   ID" << "|  "
			<< setw(30) << left << "Lastname" << "|  "
			<< setw(11) << left << "Firstname" << "|  "
			<< setw(8) << left << "Class" << "|  "
			<< setw(8) << left << "Midterm" << "|  "
			<< setw(6) << left << "Final" << "|  "
			<< setw(5) << left << "Lab" << "|  "
			<< setw(7) << left << "Bonus" << "|" << endl;
		textColor(NormalT);
		cout << "  ";
		textColor(TitleBoard);
		cout << "|" << setfill('-')
			<< setw(115) << "-" << "|" << endl
			<< setfill(' ');
		for (int i = 0; i < n; i++)
		{
			textColor(NormalT);
			cout << "  ";
			textColor(InBoard);
			cout << "|  " << setw(4) << left << i + 1 << "|  ";
			cout << setw(10) << left << s[i].id << "|  "
				<< setw(30) << left << s[i].last_name << "|  "
				<< setw(11) << left << s[i].first_name << "|  "
				<< setw(8) << left << s[i].class_name << "|     ";
			pointColor(s[i].midterm);
			cout << setw(5) << left << s[i].midterm;
			textColor(InBoard);
			cout << "|    ";
			pointColor(s[i].final_point);
			cout << setw(4) << left << s[i].final_point;
			textColor(InBoard);
			cout << "|    "
				<< setw(3) << left << s[i].lab << "|     "
				<< setw(4) << left << s[i].bonus << "|" << endl;
		}
		textColor(NormalT);
		cout << "  ";
		textColor(InBoard);
		cout << setfill('*')
			<< setw(117) << "*" << endl
			<< setfill(' ');
		if (s != NULL)
			delete[]s;
		textColor(NormalT);
		cout << "\nDo you want to view another scoreboard? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	cout << endl;
	textColor(NormalT);
}
void	function25()
{
	cout << "\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Exporting scoreboard of a course to csv file" << endl;
	do
	{
		courseID	c;
		if (!askingCourseID(c))
			return;
		course		course_;
		int			n = 0;
		student		*s = NULL;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(Notice);
		if (exportScoreboardCSV(s, n, course_) == true)
		{
			cout << "    The scoreboard of class " << c.class_name << " at course " << c.id << " was exported." << endl;
			cout << "\tIts name is 'Scoreboard " << c.id << " " << c.class_name << ".csv'." << endl << endl;
			courseDateGenerator(course_);
		}
		else
			cout << "    The scoreboard exported unsuccessfully!!!";
		if (s != NULL)
			delete[]s;
		textColor(NormalT);
		cout << "Do you want to export another scoreboard? (Yes/No/?): ";
		if (yesNoAns())
		{
			textColor(NormalT);
			continue;
		}
		else
		{
			textColor(NormalT);
			return;
		}
	} while (true);
}
void	function27()
{
	cout << "\t\t\t\t   ";
	textColor(TitleFunc);
	cout << "Exporting attendance list of a course to csv file" << endl;
	do
	{
		courseID	c;
		if (!askingCourseID(c))
			return;
		course		course_;
		int			n = 0;
		student		*s = NULL;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(Notice);
		if (exportAttendanceCSV(s, n, course_) == true)
		{
			cout << "    The attendace list of class " << c.class_name << " at course " << c.id << " was exported." << endl;
			cout << "\tIts name is 'AttendanceList " << c.id << " " << c.class_name << ".csv'." << endl << endl;
		}
		else
			cout << "    The attendance list exported unsuccessfully!!!";
		if (s != NULL)
			delete[]s;
		textColor(NormalT);
		cout << "Do you want to export another attendance list? (Yes/No/?): ";
		if (yesNoAns())
		{
			textColor(NormalT);
			continue;
		}
		else
		{
			textColor(NormalT);
			return;
		}
	} while (true);
}
void	function28(string user_name)
{
	cout << "\t\t\t";
	textColor(TitleFunc);
	cout << "Showing lecturer " << user_name << "'s list of courses in the current semester" << endl;
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	int		mm = now.tm_mon + 1;
	int		yyyy = now.tm_year + 1900;

	int		n = 0, yyyy_end, yyyy_st;
	int		term_ = monthToSemesterInt(mm);
	string	term_c = monthToSemesterString(mm);
	lecturer current;
	current.account = user_name;
	isLecturerExist(current);
	bool	flag = false;

	if (term_ == 1)
		yyyy_end = yyyy + 1, yyyy_st = yyyy;
	else
		yyyy_st = yyyy - 1, yyyy_end = yyyy;
	textColor(NormalT);
	cout << "   ";
	textColor(SpTitleFunc);
	cout << "This time belongs to the " << term_c << " semester of " << yyyy_st << "-" << yyyy_end << endl;
	textColor(NormalT);
	cout << "\n\t";
	for (int i = 0; i < current.n_year; i++)
	{
		if (current.years[i].start == yyyy_st)
		{
			textColor(TitleBoard);
			cout << "|" << setw(14) << left << "\tCourse  ||";
			cout << setw(13) << left << "Class" << "|" << endl;
			textColor(NormalT);
			cout << "\t";
			textColor(TitleBoard);
			cout << "|" << setfill('-') << setw(33) << "-" << "|" << endl << setfill(' ');
			for (int j = 0; j < current.years[i].n_term; j++)
			{
				if (current.years[i].terms[j].no == term_)
				{
					for (int k = 0; k < current.years[i].terms[j].n_course; k++)
					{
						textColor(NormalT);
						cout << "\t";
						textColor(InBoard);
						cout << "|" << "\t" << setw(8) << left << current.years[i].terms[j].courses[k].id << "||   ";
						cout << setw(13) << current.years[i].terms[j].courses[k].class_name << "|" << endl;
					}
				}
			}
		}
		flag = true;
		textColor(NormalT);
	}
	if (flag == false)
	{
		textColor(Notice);
		cout << "    This school year or semester was not found.";
	}
	textColor(NormalT);
	cout << "\t";
	textColor(InBoard);
	cout << setfill('*') << setw(35) << "*" << endl << setfill(' ');
	textColor(NormalT);
}
void	function29(string user_name)
{
	cout << "\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Showing student(s) list of lecturer's course" << endl;
	lecturer current;
	current.account = user_name;
	course		course_;
	courseID	c;
	int			n;
	student* s = NULL;
	do
	{
		if (!askingCourseIDOfALecturer(c, user_name))
		{
			break;
		}
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		string superTitle;
		superTitle = "List of ";
		superTitle += c.class_name;
		superTitle += "'s students in course ";
		superTitle += c.id;
		textColor(NormalT);
		cout << "\n\t";
		textColor(SpTitleFunc);
		cout << "\t\t" << setw(59) << left << superTitle << endl;
		textColor(NormalT);
		cout << "\t";
		textColor(TitleBoard);
		cout << setw(12) << left << "     No"
			<< setw(13) << left << "   ID"
			<< setw(35) << left << "Lastname"
			<< setw(15) << left << "Firstname" << endl;
		textColor(NormalT);
		cout << "\t";
		textColor(TitleBoard);
		cout << setfill('-')
			<< setw(75) << "-" << endl
			<< setfill(' ');
		for (int i = 0; i < n; i++)
		{
			textColor(NormalT);
			cout << "\t";
			if (s[i].id == 18127244)
				textColor(DucTuan);
			else
				textColor(InBoard);
			cout << "     " << setw(7) << left << i + 1
				<< setw(13) << left << s[i].id
				<< setw(35) << left << s[i].last_name
				<< setw(15) << left << s[i].first_name << endl;
		}
		textColor(Notice);
		cout << "\n   Showing the student's list of class " << c.class_name << "in " << c.id << " successfully!!\n" << endl;
		textColor(NormalT);
		cout << "Do you want to view list of another class's students in another course? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	if (s != NULL)
		delete[]s;
	s = NULL;
}
void	function30(string user_name)
{
	cout << "\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Showing attendance list of lecturer's course" << endl;
	lecturer current;
	current.account = user_name;
	course		course_;
	courseID	c;
	int			n;
	student* s = NULL;
	int			count_months = 0;
	do
	{
		if (!askingCourseIDOfALecturer(c, user_name))
		{
			break;
		}
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		do
		{
			count_months = 0;
			textColor(NormalT);
			cout << "    Choose command you want to do something which can show what you want: " << endl;//Chon thang de hien thi
			for (int i = 0; i < course_.end_date.mm - course_.start_date.mm + 2; i++)
			{
				if (i != course_.end_date.mm - course_.start_date.mm + 1)
				{
					cout << "\t" << course_.start_date.mm + i << ". " << intToMonth(course_.start_date.mm + count_months) << endl;
					count_months++;
				}
				else
					cout << "\t" << 12 + 1 << ". Show attendance list of all months when you have that course." << endl;
			}
			int		command;
			while (true)
			{
				textColor(NormalT);
				cout << "\t>> ";
				getNum(command);
				if (command <= course_.end_date.mm && command >= course_.start_date.mm || command == 13)
				{
					textColor(NormalT);
					break;
				}
				textColor(Notice);
				cout << "\t!Invalid command." << endl;
			}
			if (command == 13)
			{
				textColor(Notice);
				cout << "    This course have so many sessions.\n\tSo when you want to see attendance list of all months of this course, we will add this list"
					<< "on file.csv for you." << endl;
				if (exportAttendanceCSV(s, n, course_) == true)
				{
					textColor(Notice);
					cout << "\t    Its name is 'AttendanceList " << c.id << " " << c.class_name << ".csv'." << endl;
					cout << "\t\tPlease check it right now!!!! " << endl;
				}
				else
				{
					textColor(Notice);
					cout << "\t    Sorry, The attendance list exported unsuccessfully!!!";
				}
				textColor(NormalT);
			}
			else
			{
				int	count = 0;
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						count++;
				}
				string superTitle;
				superTitle = "The attendace list of class ";
				superTitle += c.class_name;
				superTitle += " at course ";
				superTitle += c.id;
				superTitle += " of ";
				superTitle += intToMonth(command);
				textColor(SpTitleFunc);
				cout << setw((33 + 6 * count)) << left << superTitle << endl;
				textColor(TitleBoard);
				cout << setw(4) << left << "No";
				cout << setw(28) << left << "|Fullname";
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						cout << setw(3) << left << "|" << setw(3) << left << course_.course_date[i].dd;
				}
				cout << "|" << endl
					<< "    |" << setw(28) << right << "|";
				for (int i = 0; i < course_.n_course_date; i++)
				{
					if (course_.course_date[i].mm == command)
						cout << setw(2) << course_.course_date[i].start_hh << ":" << setw(2) << course_.course_date[i].start_min << "|";
				}
				cout << endl;
				cout << setfill('-');
				cout << setw((33 + 6 * count)) << "-" << endl;
				cout << setfill(' ');
				textColor(InBoard);
				for (int i = 0; i < course_.n_student; i++)
				{
					cout << setw(4) << left << i + 1;
					string		fullname = "|";
					fullname += s[i].last_name;
					fullname += " ";
					fullname += s[i].first_name;
					cout << setw(28) << left << fullname << "|";
					for (int j = 0; j < course_.n_course_date; j++)
					{
						if (course_.course_date[j].mm == command)
						{
							cout << setw(5) << left;
							if (s[i].attendance[j])
							{
								textColor(Attendance_Checkin);
								cout << "  V";
								textColor(InBoard);
								cout << "|";
							}
							else
							{
								textColor(Attendance_Absent);
								cout << "  A";
								textColor(InBoard);
								cout << "|";
							}
							textColor(InBoard);
						}
					}
					cout << endl;
				}
				textColor(NormalT);
				cout << "Do you want to view another month attendance list of this course of this class? (Yes/No/?): ";
				if (yesNoAns() == false)
				{
					textColor(NormalT);
					cout << endl;
					break;
				}
			}
		} while (true);
		textColor(NormalT);
		cout << "Do you want to view another attendance list? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	if (s != NULL)
		delete[]s;
	s = NULL;
}
void	function33(string user_name)
{
	cout << "\t\t\t\t\t      ";
	textColor(TitleFunc);
	cout << "Editing score of student(s)" << endl;
	lecturer current;
	current.account = user_name;
	course		course_;
	courseID	c;
	int			n;
	student* s = NULL;
	do
	{
		if (!askingCourseIDOfALecturer(c, user_name))
			break;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(Notice);
		cout << "    Showing the scoreboard for you to help checking student's score easily!!!" << endl;
		textColor(NormalT);
		cout << "\n    ";
		textColor(SpTitleFunc);
		cout << "\t\t\tThis is the scoreboard of class " << c.class_name << " at course " << c.id << "\t\t\t\t\t   " << endl;
		textColor(NormalT);
		cout << "    ";
		textColor(TitleBoard);
		cout << setw(12) << left << "   No"
			<< setw(10) << left << "ID"
			<< setw(29) << left << "Lastname"
			<< setw(13) << left << "Firstname"
			<< setw(11) << left << "Class"
			<< setw(10) << left << "Midterm"
			<< setw(10) << left << "Final"
			<< setw(8) << left << "Lab"
			<< setw(8) << left << "Bonus" << endl;
		textColor(NormalT);
		cout << "    ";
		textColor(TitleBoard);
		cout << setfill('-')
			<< setw(111) << "-" << endl
			<< setfill(' ');
		for (int i = 0; i < n; i++)
		{
			textColor(NormalT);
			cout << "    ";
			if (s[i].id == 18127244) //Mau cua Bui Ta Duc Dat
				textColor(DucTuan);
			else
				textColor(InBoard);
			cout << "   " << setw(6) << left << i + 1;
			cout << setw(13) << left << s[i].id;
			cout << setw(29) << left << s[i].last_name;
			cout << setw(13) << left << s[i].first_name;
			cout << setw(14) << left << s[i].class_name;
			pointColor(s[i].midterm);
			cout << setw(9) << left << s[i].midterm;
			pointColor(s[i].final_point);
			cout << setw(9) << left << s[i].final_point;
			cout << setw(9) << left << s[i].lab;
			cout << setw(6) << left << s[i].bonus << endl;
		}
		textColor(NormalT);
		cout << "    After watching, do you want to change any score in this class? (Yes/No/?): ";
		if (yesNoAns())
		{
			int id, n_course;
			student cur;
			cout << "\tInput the ID of the student whom you want to changing: ";
			getNum(id);
			if (!findStudentByID(id, cur))
			{
				textColor(Notice);
				cout << "\t    The ID inexists!" << endl;
				textColor(NormalT);
				cout << "\nDo you want to continue? (Yes/No/?): ";
				if (yesNoAns())
				{
					textColor(NormalT);
					continue;
				}
				else
				{
					textColor(Notice);
					cout << "\t    Stop changing student's score." << endl;
					textColor(NormalT);
				}
			}
			for (int i = 0; i < n; i++)
			{
				if (s[i].id == cur.id)
				{
					cur = s[i];
				}
			}
			textColor(WOInfo);
			cout << "\tThis is some information of the student who you want to change:" << endl;
			textColor(NormalT);
			cout << "    ";
			textColor(TitleBoard);
			cout << setw(17) << left << "       ID"
				<< setw(29) << left << "Lastname"
				<< setw(13) << left << "Firstname"
				<< setw(11) << left << "Class"
				<< setw(10) << left << "Midterm"
				<< setw(10) << left << "Final"
				<< setw(8) << left << "Lab"
				<< setw(8) << left << "Bonus" << endl;
			textColor(NormalT);
			cout << "    ";
			textColor(TitleBoard);
			cout << setfill('-')
				<< setw(106) << "-" << endl
				<< setfill(' ');
			textColor(NormalT);
			cout << "    ";
			if (cur.id == 18127244) //Mau cua Bui Ta Duc Dat
				textColor(DucTuan);
			else
				textColor(InBoard);
			cout << "    "
				<< setw(13) << left << cur.id
				<< setw(29) << left << cur.last_name
				<< setw(13) << left << cur.first_name
				<< setw(14) << left << cur.class_name;
			pointColor(cur.midterm);
			cout << setw(9) << left << cur.midterm;
			pointColor(cur.final_point);
			cout << setw(9) << left << cur.final_point
				<< setw(9) << left << cur.lab
				<< setw(6) << left << cur.bonus << endl;
			textColor(Notice);
			cout << "\t    After checking, do you want to changing this student's score?"
				<< "\n    *Remember that, if you changing this student's score you can not restore its data!" << endl;
			textColor(NormalT);
			cout << "    >> (Yes/No/?): ";
			if (yesNoAns())
			{
				do
				{
					cout << "\t    What do you want to change? Choose at least one command (You can choose from 1 to 4 commands)!!!" << endl
						<< "\t\t1. Midterm Score\n\t\t2. Final Score" << endl
						<< "\t\t3. Lab Score\n\t\t4. Bonus Score" << endl;
					int* ans = NULL;
					int n_ans = askManyCommands(1, 4, ans);
					for (int i = 0; i < n_ans; i++)
					{
						switch (ans[i])
						{
						case 1:
						{
							cout << "\t\t    Please input the new midterm score: ";
							getNum(cur.midterm);
							break;
						}
						case 2:
						{
							cout << "\t\t    Please input the new final score: ";
							getNum(cur.final_point);
							break;
						}
						case 3:
						{
							cout << "\t\t    Please input the new lab score: ";
							getNum(cur.lab);
							break;
						}
						case 4:
						{
							cout << "\t\t    Please input the new bonus score: ";
							getNum(cur.bonus);
							break;
						}
						}
					}
					for (int i = 0; i < n; i++)
					{
						if (cur == s[i])
						{
							s[i] = cur;
							break;
						}
					}
					cout << "\t    This is some information after your changing:" << endl;
					textColor(NormalT);
					cout << "    ";
					textColor(TitleBoard);
					cout << setw(17) << left << "       ID"
						<< setw(29) << left << "Lastname"
						<< setw(13) << left << "Firstname"
						<< setw(11) << left << "Class"
						<< setw(10) << left << "Midterm"
						<< setw(10) << left << "Final"
						<< setw(8) << left << "Lab"
						<< setw(8) << left << "Bonus" << endl;
					textColor(NormalT);
					cout << "    ";
					textColor(TitleBoard);
					cout << setfill('-')
						<< setw(106) << "-" << endl
						<< setfill(' ');
					textColor(NormalT);
					cout << "    ";
					if (cur.id == 18127244) //Mau cua Bui Ta Duc Dat
						textColor(DucTuan);
					else
						textColor(InBoard);
					cout << "    "
						<< setw(13) << left << cur.id
						<< setw(29) << left << cur.last_name
						<< setw(13) << left << cur.first_name
						<< setw(14) << left << cur.class_name;
					pointColor(cur.midterm);
					cout << setw(9) << left << cur.midterm;
					pointColor(cur.final_point);
					cout << setw(9) << left << cur.final_point
						<< setw(9) << left << cur.lab
						<< setw(6) << left << cur.bonus << endl;
					textColor(NormalT);
					cout << "\t    Are you sure?";
					textColor(NormalT);
					cout << " Do you want to changing it again ? (Yes/No/?) : ";
					if (!yesNoAns())
					{
						saveCourseIDTXT(course_, s, n, cur.class_name);
						textColor(Notice);
						cout << "\t\tChanging score successfully!!!" << endl;
						textColor(NormalT);
						if (ans != NULL)
							delete[]ans;
						ans = NULL;
						break;
					}
				} while (true);
			}
			else
			{
				textColor(Notice);
				cout << "\t    Stop changing this student's score." << endl;
				textColor(NormalT);
			}
		}
		textColor(NormalT);
		cout << "    Do you want to conutinue to change student's score? (Yes/No/?): ";
		if (!yesNoAns())
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	if (s != NULL)
		delete[]s;
	textColor(NormalT);
}
void	function34(string user_name)
{
	cout << "\t\t\t\t\t";
	textColor(TitleFunc);
	cout << "Showing scoreboard of lecturer's course" << endl;
	lecturer current;
	current.account = user_name;
	course		course_;
	courseID	c;
	int			n;
	student* s = NULL;
	do
	{
		if (!askingCourseIDOfALecturer(c, user_name))
			break;
		readCourseIDTXT(c.id, course_, s, n, c.class_name);
		textColor(NormalT);
		cout << "\n    ";
		textColor(SpTitleFunc);
		cout << "\t\t\tThis is the scoreboard of class " << c.class_name << " at course " << c.id << "\t\t\t\t\t   " << endl;
		textColor(NormalT);
		cout << "    ";
		textColor(TitleBoard);
		cout << setw(12) << left << "   No"
			<< setw(10) << left << "ID"
			<< setw(29) << left << "Lastname"
			<< setw(13) << left << "Firstname"
			<< setw(11) << left << "Class"
			<< setw(10) << left << "Midterm"
			<< setw(10) << left << "Final"
			<< setw(8) << left << "Lab"
			<< setw(8) << left << "Bonus" << endl;
		textColor(NormalT);
		cout << "    ";
		textColor(TitleBoard);
		cout << setfill('-')
			<< setw(111) << "-" << endl
			<< setfill(' ');
		for (int i = 0; i < n; i++)
		{
			textColor(NormalT);
			cout << "    ";
			if (s[i].id == 18127244) //Mau cua Bui Ta Duc Dat
				textColor(DucTuan);
			else
				textColor(InBoard);
			cout << "   " << setw(6) << left << i + 1;
			cout << setw(13) << left << s[i].id;
			cout << setw(29) << left << s[i].last_name;
			cout << setw(13) << left << s[i].first_name;
			cout << setw(14) << left << s[i].class_name;
			pointColor(s[i].midterm);
			cout << setw(9) << left << s[i].midterm;
			pointColor(s[i].final_point);
			cout << setw(9) << left << s[i].final_point;
			cout << setw(9) << left << s[i].lab;
			cout << setw(6) << left << s[i].bonus << endl;
		}
		textColor(NormalT);
		cout << "\nDo you want to view another scoreboard? (Yes/No/?): ";
		if (yesNoAns() == false)
		{
			cout << endl;
			textColor(NormalT);
			return;
		}
	} while (true);
	if (s != NULL)
		delete[]s;
	s = NULL;
}
void	function35(string user_name)
{
	cout << "\t\t\t\t\t\t\t";
	textColor(TitleFunc);
	cout << "Check-in" << endl;
	textColor(NormalT);
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);// function này thế từ bg(tg hệ thống) -> now
	int dd = now.tm_mday,
		mm = now.tm_mon + 1,
		yyyy = now.tm_year + 1900,
		hh = now.tm_hour,
		min = now.tm_min;
	int current_start_year = getCurrentAcademicYear();//vd : tháng 4 là hk 2 -> năm 2018, tháng 12 là hk 1 2019
	int current_semester = getCurrentSemester();
	student s;
	academic_year* student_year = NULL;
	int n_year = 0;
	int id = stoi(user_name);

	if (findStudentByID(id, s) == true)
	{
		textColor(NormalT);
		cout << "Hello ";
		textColor(12);
		cout << s.last_name << " " << s.first_name;
		textColor(Notice);
		cout << " (" << id << ")!!!" << endl;
		textColor(NormalT);
		loadStudentData(s, student_year, n_year, s.class_name, s.id);

		// student_year = {2017 2018, 2018 2019, 2019 2020, ....}
		//					[0]			[1]			[2]
		// year[i]
		// year[i].terms[j]
		// 2018 2019:
		// 
		// 1
		// 2 <- 
		// 3
		//
		// year[i].terms[j].courses[k]
		// 
		// Tìm năm học hiện tại 2018 2019 ở vị trí  nào trong mảng

		int vitri_namhoc_trong_mang = 0;
		int vitri_hocky_trong_mang = 0;
		bool daco_vitri_hocky = false;
		for (int i = 0; i < n_year; i++)
		{

			if (student_year[i].start == current_start_year)
			{
				vitri_namhoc_trong_mang = i;
				for (int j = 0; j < student_year[i].n_term; j++)
				{
					if (student_year[i].terms[j].no == current_semester)
					{
						vitri_hocky_trong_mang = j;
						daco_vitri_hocky = true;
						break;
					}
				}
				if (daco_vitri_hocky)
				{
					break;
				}

			}
		}
		if (!daco_vitri_hocky)
		{
			textColor(Notice);
			cout << "    The currrent semester does not exist in the program's data!!" << endl
				<< "    Please wait your academic staff import the data before using this function." << endl;
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back" << endl;
			textColor(NormalT);
			_getch();
			return;
		}

		hour current_hour = { hh, min };
		// Doc tung khoa hoc trong hoc kỳ 2
		for (int k = 0; k < student_year[vitri_namhoc_trong_mang].terms[vitri_hocky_trong_mang].n_course; k++)
		{
			course c;
			readCourseTXT_OnlyCourseInfo(student_year[vitri_namhoc_trong_mang].terms[vitri_hocky_trong_mang].courses[k].id,
				student_year[vitri_namhoc_trong_mang].terms[vitri_hocky_trong_mang].courses[k].class_name, c);
			courseDateGenerator(c);
			// Duyet mang ngay thang co tiet hoc
			// Tim co ngay do hay khong
			// hom nay 2/4/2019
			// Neu tim ra ngay do thi...
			for (int i = 0; i < c.n_course_date; i++)
			{
				if (c.course_date[i].yyyy == yyyy && c.course_date[i].dd == dd && c.course_date[i].mm == mm)
				{
					/*cout << "tiet hoc thu " << i + 1*/;
					hour start_hour = { c.course_date[i].start_hh, c.course_date[i].start_min };
					hour end_hour = { c.course_date[i].end_hh, c.course_date[i].end_min };
					//if (c.course_date[i].start_hh<=hh&&c.course_date[i].end_hh>=hh)
					if (current_hour >= start_hour && current_hour <= end_hour)
					{
						// Neu bay gio da co tiet
						textColor(Notice);
						cout << "    " << c.id << " is currently runnning!!!";
						textColor(NormalT);
						cout << "Would you like to check-in? (Yes/No/?): ";
						if (!yesNoAns())
						{
							return;
						}
						student* all_s = NULL;
						int n_s = 0;
						readCourseIDTXT(c.id, c, all_s, n_s, c.class_name);
						for (int j = 0; j < n_s; j++)
						{
							if (all_s[j].id == id)
							{
								all_s[j].attendance[i] = true;
								break;
							}
						}

						saveCourseIDTXT(c, all_s, n_s, c.class_name);
						textColor(Notice);
						cout << "    Checking successfully" << endl;
						textColor(NormalT);
						delete[]all_s;
						//s = NULL;
						delete[] student_year;
						textColor(WOInfo);
						cout << "\nPlease press 'Enter' to go back" << endl;
						textColor(NormalT);
						_getch();
						return;
					}
				}
			}
		}
		textColor(Notice);
		cout << "    Currently, there is no any course available!!!" << endl;
		textColor(WOInfo);
		cout << "\nPlease press 'Enter' to go back" << endl;
		textColor(NormalT);
		_getch();
	}
	delete[]student_year;

}
void	function38(string user_name)
{
	cout << "\t\t\t\t\t   ";
	textColor(TitleFunc);
	cout << "View student's scores of a course" << endl;
	course c;
	student* s_course = NULL;
	int n_s_course = 0;
	int id = stoi(user_name);
	/*cout << "enter courses ID(ctt008): ";
	string temp;
	cin >> temp;
	cout << "enter class name (18clc6): ";
	string temp2;
	cin >> temp2;*/
	student s;
	academic_year* s_yr = NULL;
	int n_yr;
	findStudentByID(id, s);
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	if (n_yr == 0)
	{
		textColor(Notice);
		cout << "    There is no any course available right now!" << endl;
		textColor(WOInfo);
		cout << "\nPlease press 'Enter' to go back" << endl;
		textColor(NormalT);
		_getch();
		delete[]s_yr;
		delete[]s_course;
		return;
	}
	int ans = 0;
	do
	{
		textColor(NormalT);
		cout << "    Please enter Course ID: ";
		textColor(Input__);
		getline(cin, c.id, '\n');
		strUpr(c.id);
		textColor(NormalT);
		cout << "    Please enter class: ";
		textColor(Input__);
		getline(cin, c.class_name, '\n');
		strUpr(c.class_name);
		textColor(NormalT);
		int i = 0, j = 0, k = 0;
		for (i = 0; i < n_yr; i++)
		{
			for (j = 0; j < s_yr[i].n_term; j++)
			{
				for (k = 0; k < s_yr[i].terms[j].n_course; k++)
				{
					if (s_yr[i].terms[j].courses[k].id == c.id)
					{
						readCourseIDTXT(c.id, c, s_course, n_s_course, s.class_name);
						break;
					}
				}
				if (k < s_yr[i].terms[j].n_course)
				{
					break;

				}
			}
			if (j < s_yr[i].n_term)
			{
				break;
			}
		}
		if (i < n_yr)
		{
			break;
		}
		textColor(Notice);
		cout << "    Course ID not found!!!" << endl;
		textColor(NormalT);
		cout << "Do you want to continue? (Yes/No/?): ";
		if (!yesNoAns())
		{
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back" << endl;
			textColor(NormalT);
			delete[]s_yr;
			delete[]s_course;
			_getch();
			return;
		}
	} while (true);
	/*if (readCourseIDTXT(temp, c, s_course, n_s_course, temp2) == false)
	{
		cout << "\nyou enter wrong,do you want to return ??";
		if (yesNoAns() == true)
		{
			system("cls");
			string id = to_string(temp3);
			studentmenu(id);
		}
		else
		{
			exit(0);
		}
	}*/
	//sortAscending(s_course, n_s_course);

	for (int i = 0; i < n_s_course; i++)
	{
		if (s_course[i].id == s.id)
		{
			textColor(SpTitleFunc);
			cout << "Name of student:" << endl;
			textColor(OInfo);
			cout << "    - " << setw(12) << left << "Last name:"
				<< s_course[i].last_name << endl
				<< "    - " << setw(12) << left << "First name:"
				<< s_course[i].first_name << endl;
			textColor(SpTitleFunc);
			cout << "Student's scores in course " << c.id << ": " << endl;
			textColor(NormalT);
			cout << "    - " << setw(20) << left << "Mid term point:";
			textColor(Notice);
			cout << s_course[i].midterm << endl;
			textColor(NormalT);
			cout << "    - " << setw(20) << left << "Lab point:";
			textColor(Notice);
			cout << s_course[i].lab << endl;
			textColor(NormalT);
			cout << "    - " << setw(20) << left << "Final point:";
			textColor(Notice);
			cout << s_course[i].final_point << endl;
			textColor(NormalT);
			cout << "    - " << setw(20) << left << "Bonus point:";
			textColor(Notice);
			cout << s_course[i].bonus << endl;
			textColor(NormalT);
			break;
		}
	}
	delete[]s_yr;
	delete[]s_course;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	_getch();
}
void	function32(string user_name)
{
	cout << "\t\t\t";
	textColor(TitleFunc);
	cout << "Import scoreboard of a course (midterm, final, lab, bonus) from a csv file" << endl;
	textColor(NormalT);
	do
	{

		cout << "Do you want to: " << endl;
		cout << "\t1/ Reead file scoreboard.csv and update file courses" << endl;
		cout << "\t2/ Print file scoreboard.csv" << endl
			<< "\t3.../Back" << endl;
		int command = askCommand(3);
		switch (command)
		{
		case 1:
		{
			student* s = NULL;

			int n_s = 0;
			cout << "Please input the directory of the scoreboard you would like to update: ";
			string temp;
			getline(cin, temp, '\n');
			if (importScoreBoard(s, n_s, temp))
			{
				sortAscending(s, n_s);
				course c;
				student* s_course = NULL;
				int n_s_course = 0;
				if (!askingCourseIDOfALecturer(c, user_name))
				{
					textColor(Notice);
					cout << "    There is no any ocurse available right now" << endl;
					textColor(WOInfo);
					cout << "\nPlease press 'Enter' to go back" << endl;
					textColor(NormalT);
					_getch();
					return;
				}
				readCourseIDTXT(c.id, c, s_course, n_s_course, c.class_name);
				sortAscending(s_course, n_s_course);

				for (int i = 0; i < n_s; i++)
				{
					int j = 0;
					for (j = 0; j < n_s_course; j++)
					{
						if (s[i] == s_course[j])
						{
							s_course[j].bonus = s[i].bonus;
							s_course[j].final_point = s[i].final_point;
							s_course[j].lab = s[i].lab;
							s_course[j].midterm = s[i].midterm;
							break;
						}
					}
					if (j >= n_s_course)
					{
						cout << s[i].id << " " << s[i].last_name << endl;
					}
				}
				saveCourseIDTXT(c, s_course, n_s_course, c.class_name);
			}

			else
			{
				cout << "We did not find any file that has that name or the file does not have a vaild format" << endl
					<< "Do you want to continue (Yes/No/?): ";
				if (yesNoAns())
				{
					continue;
				}
				return;
			}

			cout << "updated successfully";
			cout << endl; break;
		}
		case 2:
		{
			student* s = NULL;
			int n_s = 0;
			cout << "input the file csv to check(vd:ctt008.csv): ";
			string temp; cin >> temp;

			if (importScoreBoard(s, n_s, temp))
			{
				sortAscending(s, n_s);
				/*course c;*/
				student* s_course = NULL;
				int n_s_course = 0;
				cout << "No,ID,Last Name,First Name ,Mid,Term,Lap,Final,Bonus" << endl;
				for (size_t i = 0; i < n_s; i++)
				{
					cout << s[i].no << "," << s[i].id << "," << s[i].last_name << "," << s[i].first_name
						<< "," << s[i].midterm << "," << s[i].lab << "," << s[i].final_point << "," << s[i].bonus << endl;
				}
				cout << endl;
			}
			else
			{
				cout << "We did not find any file that has that name or the file does not have a vaild format" << endl
					<< "Do you want to continue (Yes/No/?): ";
				if (yesNoAns())
				{
					continue;
				}
				return;
			}
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back" << endl;
			textColor(NormalT);
			_getch();
			system("cls");
			break;
		}
		case 3: {
			return;
		}
		}
	} while (true);
}
void	function36(string user_name)
{
	cout << "\t\t\t\t\t\t   ";
	textColor(TitleFunc);
	cout << "View check-in result" << endl;
	student* s = NULL;
	int n_s = 0;
	sortAscending(s, n_s);
	course c;
	student* s_course = NULL;
	int n_s_course = 0;
	do
	{
		do
		{
			textColor(NormalT);
			cout << "Enter courses ID ";
			textColor(WOInfo);
			cout << "(CTT008)";
			textColor(NormalT);
			cout << ": ";
			string temp;
			textColor(Input__);
			cin >> temp;
			textColor(NormalT);
			cout << "Enter class name to check ";
			textColor(WOInfo);
			cout << "(18CLC6)";
			textColor(NormalT);
			cout << ": ";
			string temp2;
			textColor(Input__);
			cin >> temp2;
			textColor(NormalT);
			if (!readCourseIDTXT(temp, c, s_course, n_s_course, temp2))
			{
				textColor(Notice);
				cout << "    You enter wrong!!!" << endl;
				textColor(NormalT);
				cout << "Do you want enter again??";
				if (yesNoAns())
					continue;
				else
				{
					textColor(Notice);
					cout << "    Stop showing attendance infomation!" << endl;
					textColor(WOInfo);
					cout << "\nPlease, press 'Enter' to back!" << endl;
					textColor(NormalT);
					_getch();
					return;
				}
			}
			else
				break;
		} while (true);
		sortAscending(s_course, n_s_course);
		int id = stoi(user_name);
		textColor(OInfo);
		cout << "    Student :" << user_name << endl;
		textColor(NormalT);
		for (size_t i = 0; i < n_s_course; i++)
		{
			if (s_course[i].id == id)
			{
				for (size_t j = 0; j < c.n_course_date; j++)
				{
					if (s_course[i].attendance[j] == true)
					{
						cout << "\t-" << setw(2) << c.course_date[j].dd << "/" << setw(2) << c.course_date[j].mm << "/" << c.course_date[j].yyyy;
						textColor(OInfo);
						cout << "\tCourse no. " << j + 1;
						textColor(Notice);
						cout << "\tChecked-in!!!" << endl;
						textColor(NormalT);
					}
					else
					{
						cout << "\t-" << setw(2) << c.course_date[j].dd << "/" << setw(2) << c.course_date[j].mm << "/" << c.course_date[j].yyyy;
						textColor(OInfo);
						cout << "\tCourse no. " << j + 1;
						textColor(4);
						cout << " \tAbsent!!!!!!" << endl;
						textColor(NormalT);
					}
				}
			}
		}
		textColor(Notice);
		cout << "    Show attendance complete!" << endl;
		textColor(NormalT);
		cout << "Do you want to read another attendance infomation?";
		if (!yesNoAns())
		{
			textColor(Notice);
			cout << "    Stop showing attendance infomation!" << endl;
			break;
		}
	} while (true);
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back!!" << endl;
	textColor(NormalT);
	_getch();
}
void	function37(string user_name)
{
	cout << "\t\t\t\t\t\t    ";
	textColor(TitleFunc);
	cout << "View schedules" << endl;
	textColor(NormalT);

	course c;
	student* s_course = NULL;
	int n_s_course = 0;
	int id = stoi(user_name);
	student s;
	academic_year* s_yr = NULL;
	int n_yr = 0;
	findStudentByID(id, s);
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);// function này thế từ bg(tg hệ thống) -> now
	int dd = now.tm_mday,
		mm = now.tm_mon + 1,
		yyyy = now.tm_year + 1900,
		hh = now.tm_hour,
		min = now.tm_min;
	int current_start_year = getCurrentAcademicYear();//vd : tháng 4 là hk 2 -> năm 2018, tháng 12 là hk 1 2019
	int current_semester = getCurrentSemester();
	int vitri_namhoc_trong_mang = 0;
	int vitri_hocky_trong_mang = 0;
	bool daco_vitri_hocky = false;
	for (int i = 0; i < n_yr; i++)
	{
		if (s_yr[i].start == current_start_year)
		{
			vitri_namhoc_trong_mang = i;
			for (int j = 0; j < s_yr[i].n_term; j++)
			{
				if (s_yr[i].terms[j].no == current_semester)
				{
					vitri_hocky_trong_mang = j;
					daco_vitri_hocky = true;
					break;
				}
			}
			if (daco_vitri_hocky)
			{
				break;
			}

		}
	}
	if (!daco_vitri_hocky)
	{
		textColor(Notice);
		cout << "    The currrent semester does not exist in the program's data!" << endl
			<< "    Please wait for your academic staff importing the data before using this function!!" << endl;
		textColor(WOInfo);
		cout << "\nPlease press 'Enter' to go back" << endl;
		textColor(NormalT);
		_getch();
		delete[]s_course;
		delete[]s_yr;
		return;
	}

	viewLecturerGeneralSchedule(false, s_yr[vitri_namhoc_trong_mang].terms[vitri_hocky_trong_mang]);
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	delete[]s_course;
	delete[]s_yr;
	_getch();
}

COORD	GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))

	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
bool	isCourseExistInLecturerTXT_(string class_name, string course_id, string lecturer_acc)
{
	strUpr(class_name);
	strUpr(course_id);

	int n_lecturer;
	ifstream lecturerTXT("data\\lecturer.txt");
	lecturerTXT >> n_lecturer;
	if (n_lecturer == 0)
		return false;
	lecturer *gv = new lecturer[n_lecturer];
	lecturerTXT.close();
	int all_course = 0; // Tất cả khóa học
	readLecturerTXT(gv, n_lecturer);
	for (int i = 0; i < n_lecturer; i++)
	{
		if (gv[i].account == lecturer_acc)
		{
			for (int j = 0; j < gv[i].n_year; j++)
			{
				for (int k = 0; k < gv[i].years[j].n_term; k++)
				{
					all_course += gv[i].years[j].n_term;
					for (int u = 0; u < gv[i].years[j].terms[k].n_course; u++)
					{
						if (gv[i].years[j].terms[k].courses[u].class_name == class_name && gv[i].years[j].terms[k].courses[u].id == course_id)
						{	//Nếu khóa học tồn tại thì nhảy vào đây
							delete[] gv;
							return true;
						}
					}
				}
			}
		}
	}
	delete[] gv;
	if (all_course == 0)
	{
		return  -1;
	}
	return false;
}
template <class COURSE> bool askingCourseIDOfALecturer(COURSE &c, string lecturer_acc)
{
	int	ans = 0;
	do
	{
		textColor(NormalT);
		cout << "Please enter Course ID: ";
		textColor(Input__);
		getline(cin, c.id, '\n');
		strUpr(c.id);
		textColor(NormalT);
		cout << "Please enter class: ";
		textColor(Input__);
		getline(cin, c.class_name, '\n');
		strUpr(c.class_name);
		ans = isCourseExistInLecturerTXT_(c.class_name, c.id, lecturer_acc);
		if (ans == -1)
		{
			return false;
		}
		if (ans == 0)
		{
			textColor(Notice);
			cout << "   This ID was not found." << endl;
			textColor(NormalT);
			cout << "\nDo you want to try again? (Yes/No/?): ";
			if (yesNoAns() == false)
			{
				textColor(NormalT);
				return false;
			}
		}
		else
		{
			textColor(NormalT);
			return true;
		}
	} while (true);
}

void	editCurrentAttendance(course &c, int course_date_j)
{
	//Điểm danh khóa học hiện tại
	// Xem công dụng của tham số đầu vào trong hàm currentlyRunningCourse()

	HANDLE	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int		get_character, detect_key_arrrow;
	student *s = NULL;
	int		n_s = 0;
	string	class_name = "18CLC6";

	readCourseIDTXT(c.id, c, s, n_s, c.class_name);

	textColor(NormalT);
	cout << "\t";
	textColor(TitleBoard);
	cout << setw(18) << left << "   No"
		<< setw(12) << left << "ID"
		<< setw(29) << left << "Lastname"
		<< setw(17) << left << "Firstname"
		<< setw(9) << left << "Class"
		<< setw(11) << left << "Attendance" << endl;

	textColor(NormalT);
	cout << "\t";
	textColor(TitleBoard);
	cout << setfill('-')			// set fill bằng ký tự '-' thay vì ' '
		<< setw(18 + 12 + 29 + 17 + 9 + 11) << "-" << endl
		<< setfill(' ');

	COORD origin; // Lấy tọa độ gốc
	for (int i = 0; i < n_s; i++)
	{
		textColor(NormalT);
		cout << "\t";
		textColor(InBoard);
		cout << "   " << setw(15) << left << i + 1
			<< setw(12) << left << s[i].id
			<< setw(29) << left << s[i].last_name
			<< setw(17) << left << s[i].first_name
			<< setw(9) << left << s[i].class_name
			<< "    ";
		if (s[i].attendance[course_date_j])
			cout << "V";
		else
			cout << "A";
		cout << "      ";

		if (i == 0)
		{
			origin = GetConsoleCursorPosition(hStdout);
			origin.X -= 6;
		}
		cout << endl;
	}
	textColor(NormalT);
	cout << "\t";
	textColor(InBoard);
	cout << left << setw(18 + 12 + 29 + 17 + 9 + 7 + 4) << "CONFIRM (By Pressing 'ENTER' in this line)" << endl;

	bool *attendence = new bool[n_s];
	for (int k = 0; k < n_s; k++)
	{
		attendence[k] = s[k].attendance[course_date_j];
	}
	COORD cur_pos = origin;
	SetConsoleCursorPosition(hStdout, cur_pos);

	while (true)
	{
		get_character = _getch();
		if (get_character && get_character != 224)
		{
			if ((get_character == 'V' || get_character == 'v' || get_character == 'A' || get_character == 'a') && (cur_pos.Y - origin.Y) < n_s)
			{
				if (get_character == 'V' || get_character == 'v')
				{
					textColor(Attendance_Checkin);
					cout << "\bV";
					//wcout << check;
					//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), s__, slen, &slen, NULL);
					//wcout << check;
					attendence[cur_pos.Y - origin.Y] = true;
					textColor(InBoard);
				}
				else
				{
					textColor(Attendance_Absent);
					cout << "\bA";
					attendence[cur_pos.Y - origin.Y] = false;
				}
				if ((cur_pos.Y - origin.Y) < n_s)
				{
					cur_pos.Y++;
					SetConsoleCursorPosition(hStdout, cur_pos);
				}
			}
			if (get_character == BACK_SPACE)
			{
				textColor(InBoard);
				cout << "\b ";
				attendence[cur_pos.Y - origin.Y] = false;
			}
			if (get_character == ENTER)
			{
				if ((cur_pos.Y - origin.Y) == n_s)
				{
					cout << endl;
					break;
				}
			}

		}
		else
		{
			switch (detect_key_arrrow = _getch())
			{
			case KEY_UP:
			{
				if ((cur_pos.Y - origin.Y) > 0)
				{
					cur_pos.Y--;
					SetConsoleCursorPosition(hStdout, cur_pos);
				}
				break;
			}
			case KEY_DOWN:
			{
				if ((cur_pos.Y - origin.Y) <= n_s)
				{
					cur_pos.Y++;
					SetConsoleCursorPosition(hStdout, cur_pos);
				}
				break;

			}
			case KEY_LEFT:
			case KEY_RIGHT:
				break;
			default:
				break;
			}
		}
	}

	bool is_absent = false;
	textColor(NormalT);
	cout << "These student(s) are absent in this course: " << endl;
	for (int i = 0; i < n_s; i++)
	{
		if (attendence[i] == false)
		{
			is_absent = true;
			cout << "\t   " << s[i].last_name << " " << s[i].first_name << endl;
		}
	}
	if (!is_absent)
	{
		cout << "\t<There is no any student absent today>" << endl;
	}
	for (int k = 0; k < n_s; k++)
	{
		s[k].attendance[course_date_j] = attendence[k];
	}
	saveCourseIDTXT(c, s, n_s, c.class_name);
	delete[]s;
}
bool	importAttendanceCSV(student *&s_list, int n_s, course &c)
{
	string temp;
	ifstream fin("AttendanceList" + c.id + " " + c.class_name + ".csv");
	if (fin.fail())
		return false;

	getline(fin, temp, '\n');
	char	catch_err_eof;
	int		catch_err = 0;
	int		i = 0;
	student s;
	while (!fin.eof())
	{
		if (!fin.get(catch_err_eof))
			break;
		//catch_err = fin.tellg();
		if (catch_err_eof == '\n' || catch_err_eof == ' ' || catch_err_eof == '\t' || catch_err_eof == ',' || catch_err < 0)
			break;
		else
			fin.seekg(-1, ios::cur);
		// 6 dòng trên dùng để tránh trường hợp dòng cuối cùng của file chứa kí tự xuống dòng  dẫn đến lỗi file
		getline(fin, temp, ',');
		getline(fin, temp, ',');
		try
		{
			catch_err = stoi(temp);
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
		catch (const std::out_of_range&)
		{
			return false;
		}

		// Phòng trường hợp người dùng thâm độc đổi ID HS hoặc đổi thức tự hàng cột
		for (i = 0; i < n_s; i++)
		{
			if (s_list[i].id == catch_err)
				break;
		}
		if (i >= n_s)
		{
			return false;
		}

		// Lấy dòng họ tên
		getline(fin, temp, ',');

		for (int j = 0; j < c.n_course_date; j++)
		{
			if (j < c.n_course_date - 1)
				getline(fin, temp, ',');
			else
				getline(fin, temp, '\n');
			if (temp.length() > 1)
				return false;
			strUpr(temp);
			if (temp == "V")
			{
				s_list[i].attendance[j] = true;
			}
			else
				s_list[i].attendance[j] = false;
		}
	}
	saveCourseIDTXT(c, s_list, n_s, c.class_name);
	return true;
}
void	function31(string lecturer_account)
{
	lecturer *lecturers = NULL;
	int		 n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	int i = 0;
	if (n_lecturer == 0)
	{
		return;
	}
	for (i = 0; i < n_lecturer; i++)
	{
		if (lecturers[i].account == lecturer_account)
			break;
	}
	if (i >= n_lecturer)
	{
		return;
	}
	time_t	bg = time(0);
	tm		now;
	localtime_s(&now, &bg);
	course c;
	int course_date_j = 0;
	dayhour course_date;
	int j = 0, k = 0, l = 0;
	for (j = 0; j < lecturers[i].n_year; j++)
	{
		if (lecturers[i].years[j].start == getCurrentAcademicYear())
		{
			for (k = 0; k < lecturers[i].years[j].n_term; k++)
			{
				l = currentlyRunningCourse(lecturers[i].years[j].terms[k].courses,
					lecturers[i].years[j].terms[k].n_course, course_date_j,
					course_date);
				if (l != -1)
				{
					break;
				}
			}
			if (k < lecturers[i].years[j].n_term)
				break;
		}
	}
	if (l != -1)
	{
		readCourseTXT_OnlyCourseInfo(lecturers[i].years[j].terms[k].courses[l].id,
			lecturers[i].years[j].terms[k].courses[l].id, c);
		textColor(NormalT);
		cout << "Do you want to: " << endl
			<< "    1. Edit attendance list of current course '" << c.id << "'" << endl
			<< "    2. Input the ID and editing attendance in CSV file" << endl
			<< "    3. ../Back" << endl;
		int command = askCommand(3);
		if (command == 2)
		{
			editCurrentAttendance(c, course_date_j);
		}
		if (command == 2 || command == 3)
		{
			delete[]lecturers;
			return;
		}
	}
	if (!askingCourseIDOfALecturer(c, lecturer_account))
	{
		cout << "There is no any course available now" << endl;
		delete[]lecturers;
		return;
	}

	/*

	cout << "Do you want to: " << endl
		<< "1. Edit student attendance in a specific date" << endl
		<< "2. Export Attendance list and edit in the csv file" << endl
		<< "3. ../Back" << endl;
	int command = askCommand(3);
	*/
	int command = 1;
	student *s = NULL;
	int		n_s = 0;
	readCourseIDTXT(c.id, c, s, n_s, c.class_name);
	if (command == 1)
	{
		date day;
		do
		{
			textColor(NormalT);
			cout << "Please input the date that have '" << c.name << "' course (dd/mm/yyyy): ";
			bool inexist_day = false,
				future = false;
			if (checkDateStrDDMMYYYY(day, '\n') == 1)
			{
				int j;
				for (j = 0; j < c.n_course_date; j++)
				{

					if (!future && c.course_date[j].dd == day.dd
						&& c.course_date[j].mm == day.mm
						&& c.course_date[j].yyyy == day.yyyy)

					{
						course_date_j = j;
						inexist_day = true;
						if (now.tm_year + 1900 <= c.course_date[j].yyyy)
						{
							if (now.tm_year + 1900 < c.course_date[j].yyyy)
							{
								future = true;
								break;
							}
							else
							{
								if (now.tm_mon + 1 <= c.course_date[j].mm)
								{
									if (now.tm_mon + 1 < c.course_date[j].mm)
									{
										future = true;
										break;
									}
									else
									{
										if (now.tm_mday <= c.course_date[j].dd)
										{
											if (now.tm_mday < c.course_date[j].dd)
											{
												future = true;
												break;
											}
											else if (now.tm_mday == c.course_date[j].dd)
											{
												if (now.tm_hour <= c.course_date[j].start_hh)
												{
													future = true;
													break;
												}
												else
												{
													if (now.tm_min <= c.course_date[j].start_min)
													{
														if (now.tm_min < c.course_date[j].start_min)
														{
															future = true;
															break;
														}

													}

												}
											}
										}
									}
								}
							}
						}
						break; // Break vòng 1
					}
				}

				if (j < c.n_course_date && !future)
					break; //break vòng 2
			}
			if (future)
			{
				textColor(Notice);
				cout << "    !This course is not available yet!!! from "
					<< c.course_date[course_date_j].start_hh << ":" << c.course_date[course_date_j].start_min << " to "
					<< c.course_date[course_date_j].end_hh << ":" << c.course_date[course_date_j].end_min << endl;
				textColor(NormalT);
			}
			else
			{
				textColor(Notice);
				cout << "    !Please input the date that have this course!" << endl;
				textColor(NormalT);
			}
		} while (true);
		textColor(Notice);
		cout << "    The date you have inputed is: " << c.course_date[course_date_j].dd << "/" << c.course_date[course_date_j].mm << "/" << c.course_date[course_date_j].yyyy << " "
			<< "and the lesson started from: " << c.course_date[course_date_j].start_hh << ":" << c.course_date[course_date_j].start_min << " to "
			<< c.course_date[course_date_j].end_hh << ":" << c.course_date[course_date_j].end_min << " !!!" << endl;
		textColor(NormalT);
		editCurrentAttendance(c, course_date_j);
	}
	if (command == 2) // !!!Phần này tạm thời không có chạy vì thiếu tính ổn định, người dùng thâm độc có thể dễ dàng tạo bug
	{
		exportAttendanceCSV(s, n_s, c);
		textColor(Notice);
		cout << "    We have exported the file AttendanceList" << c.id + " " << c.class_name << ".csv!!!" << endl
			<< "Please edit the file and after that go back to the programm" << endl;
		do
		{
			textColor(NormalT);
			cout << "Please input 'Yes' or any equivalent anwer to save the Attendance list (Yes/No/?): ";
			if (!yesNoAns())
			{
				textColor(Notice);
				cout << "Are you sure? (Yes/No/?): ";
				if (!yesNoAns())
				{
					textColor(NormalT);
					break;
				}
				else
				{
					textColor(NormalT);
					continue;
				}
			}
			else
				break;
		} while (true);
		importAttendanceCSV(s, n_s, c);
		textColor(Notice);
		cout << "    Saving the attendance list successfully!" << endl;
		textColor(NormalT);
	}
	delete[]lecturers;
	delete[]s;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	_getch();
}

size_t	timeSince1970(int dd, int mm, int yy)	//Tính số giây từ 0:00AM 1st, Jan, 1970
{
	size_t ans = 0;

	for (int i = 1; i <= 12; i++)
	{
		if (i >= mm)
			break;
		switch (mm)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			ans += 31;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			ans += 30;
			break;
		}
		case 2:
		{
			if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
				ans += 29;
			else
				ans += 28;
			break;
		}
		default:
			break;
		}
	}
	ans += dd;

	for (int i = yy - 1; i >= 1970; i--)
	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
		{
			ans += 366;
		}
		else
		{
			ans += 365;
		}
	}

	return (ans + 1) * 24 * 60 * 60;
}

void	resetPassword(string lecturer_acc)
{
	lecturer* lecturers = NULL;
	int		n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	int index = 0;
	for (index = 0; index < n_lecturer; index++)
	{
		if (lecturer_acc == lecturers[index].account)
		{
			break;
		}
	}


	lecturers[index].password = sha256(lecturers[index].account);
	saveLecturerTXT(lecturers, n_lecturer);
	textColor(Notice);
	textColor(NormalT);
	delete[]lecturers;

}
void	changePassword(string lecturer_acc)
{
	lecturer* lecturers = NULL;
	int		n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	int index = 0;
	for (index = 0; index < n_lecturer; index++)
	{
		if (lecturer_acc == lecturers[index].account)
		{
			break;
		}
	}

	textColor(NormalT);
	cout << "Type your new password: ";
	string pass;
	int i = 0;
	int get_pass_character;
	int detect_arrow_key = 0;
	textColor(TitleFunc);
	while (true)
	{
		get_pass_character = _getch();
		if (get_pass_character && get_pass_character != 224)
		{
			if (get_pass_character != '\b' && get_pass_character != '\r')
			{
				cout << '*';
				pass += get_pass_character;
			}
			if (get_pass_character == 8 && pass.length() >= 0)
			{
				if (pass.length() > 0)
				{
					pass.pop_back();
					cout << "\b \b";
				}
				if (pass.length() == 0)
				{
					cout << " \b";
				}
			}
			if (get_pass_character == 13)
			{
				break;
			}
		}
		else
		{
			detect_arrow_key = _getch();
		}
	}
	cout << endl;
	textColor(NormalT);
	cout << "Confirm (Yes/No/?): ";
	if (!yesNoAns())
	{
		cout << "The password will not be changed\nPlease press 'Enter' to go back" << endl;
		return;
	}
	cout << endl;
	lecturers[index].password = sha256(pass);
	saveLecturerTXT(lecturers, n_lecturer);
	textColor(Notice);
	cout << "    Changing password successfully!" << endl;
	textColor(NormalT);
	delete[]lecturers;

}
string	readAdminPassword()
{
	string acc = "admin";
	string file = "data\\" + sha256(acc);
	ifstream fin;
	fin.open(file);
	string old_pass;
	if (fin.is_open())
	{
		fin >> old_pass;
		fin.close();
	}
	else
	{
		old_pass = sha256("cominhxinhdep");
	}
	return old_pass;
}
void	changeAdminPassword()
{
	_mkdir("data");
	cout << "\t\t\t";
	textColor(TitleFunc);
	cout << "CHANGING PASSWORD" << endl;
	textColor(NormalT);
	string acc = "admin";
	string file = "data\\" + sha256(acc);
	ifstream fin;
	fin.open(file);
	string old_pass;
	if (fin.is_open())
	{
		fin >> old_pass;
		fin.close();
	}
	else
	{
		old_pass = sha256("cominhxinhdep");
	}
	int limit = 0;
	while (true)
	{
		cout << "Please type your old password before changing: ";
		textColor(TitleFunc);
		string		pass;
		int i = 0;
		int get_pass_character;
		int detect_arrow_key = 0;
		pass = "";
		while (true)
		{
			get_pass_character = _getch();
			if (get_pass_character && get_pass_character != 224)
			{
				if (get_pass_character != '\b' && get_pass_character != '\r')
				{
					cout << '*';
					pass += get_pass_character;
				}
				if (get_pass_character == 8 && pass.length() >= 0)
				{
					if (pass.length() > 0)
					{
						pass.pop_back();
						cout << "\b \b";
					}
					if (pass.length() == 0)
					{
						cout << " \b";
					}
				}
				if (get_pass_character == 13)
				{
					break;
				}
			}
			else
			{
				detect_arrow_key = _getch();
			}
		}
		//cout << "\nYour password you have inputed is: " << pass << endl;
		string		real_pass = sha256(pass);

		if (!(real_pass == old_pass))
		{
			textColor(Notice);
			limit++;
			if ((limit >= 0) && (limit < 5))
			{
				cout << "\n    Invalid inputed password, please try to input again!" << endl;
				if (limit == 4)
					cout << "*Please try to input the last time! If you are wrong at this time, you need to try at another time!" << endl;
				textColor(NormalT);
				continue;
			}
			if (limit == 5)
			{
				cout << "\n    You have inputed wrong fifth times, please try again at another time!" << endl;
				textColor(NormalT);
				_getch();
				exit(0);
			}
		}
		else
		{
			textColor(NormalT);
			break;
		}
		textColor(NormalT);
	}
	cout << endl;
	cout << "New password: ";
	string		pass;
	int i = 0;
	int get_pass_character;
	int detect_arrow_key = 0;
	textColor(TitleFunc);
	while (true)
	{
		get_pass_character = _getch();
		if (get_pass_character && get_pass_character != 224)
		{
			if (get_pass_character != '\b' && get_pass_character != '\r')
			{
				cout << '*';
				pass += get_pass_character;
			}
			if (get_pass_character == 8 && pass.length() >= 0)
			{
				if (pass.length() > 0)
				{
					pass.pop_back();
					cout << "\b \b";
				}
				if (pass.length() == 0)
				{
					cout << " \b";
				}
			}
			if (get_pass_character == 13)
			{
				break;
			}
		}
		else
		{
			detect_arrow_key = _getch();
		}
	}
	textColor(NormalT);
	cout << endl;
	cout << "Confirm (Yes/No/?): ";
	if (!yesNoAns())
	{
		return;
	}
	cout << endl;
	ofstream fout;
	fout.open(file);
	fout << sha256(pass);
	fout.close();
	textColor(Notice);
	cout << "    Changing password successfully!!!" << endl;
	cout << "  Now you can use your new password!!" << endl;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	_getch();
}
void	changePassword(student &s)
{
	textColor(NormalT);
	cout << "Type your new password: ";
	string pass;
	int i = 0;
	int get_pass_character;
	int detect_arrow_key = 0;
	textColor(TitleFunc);
	while (true)
	{
		get_pass_character = _getch();
		if (get_pass_character && get_pass_character != 224)
		{
			if (get_pass_character != '\b' && get_pass_character != '\r')
			{
				cout << '*';
				pass += get_pass_character;
			}
			if (get_pass_character == 8 && pass.length() >= 0)
			{
				if (pass.length() > 0)
				{
					pass.pop_back();
					cout << "\b \b";
				}
				if (pass.length() == 0)
				{
					cout << " \b";
				}
			}
			if (get_pass_character == 13)
			{
				break;
			}
		}
		else
		{
			detect_arrow_key = _getch();
		}
	}
	cout << endl;
	textColor(NormalT);
	cout << "Confirm (Yes/No/?): ";
	if (!yesNoAns())
	{
		cout << "The password will not be changed\nPlease press 'Enter' to go back" << endl;
		return;
	}
	cout << endl;
	s.password = sha256(pass);
	textColor(Notice);
	cout << "    Changing password successfully!" << endl;
	textColor(NormalT);
}
void	changeName(student &s)
{
	string new_last_name, new_first_name;
	textColor(NormalT);
	cout << "Last name: ";
	textColor(Input__);
	getline(cin, new_last_name, '\n');
	textColor(NormalT);
	cout << "First name: ";
	textColor(Input__);
	getline(cin, new_first_name, '\n');
	// Sửa trong file [class].txt
	student *s_list = NULL;
	int n_list = 0;
	readStudentList(s_list, n_list, s.class_name);
	for (int i = 0; i < n_list; i++)
	{
		if (s_list[i].id == s.id)
		{
			s_list[i].last_name = new_last_name;
			s_list[i].first_name = new_first_name;
			break;
		}
	}
	exportStudentList(s_list, n_list, s.class_name);
	delete[]s_list;
	s_list = NULL;
	// Sửa các file course.txt
	academic_year* s_yr = NULL;
	int n_yr = 0;
	course c;
	loadStudentData(s, s_yr, n_yr, s.class_name, s.id);
	for (int i = 0; i < n_yr; i++)
	{
		for (int j = 0; j < s_yr[i].n_term; j++)
		{
			for (int k = 0; k < s_yr[i].terms[j].n_course; k++)
			{
				readCourseIDTXT(s_yr[i].terms[j].courses[k].id, c, s_list, n_list, s_yr[i].terms[j].courses[k].class_name);
				for (int l = 0; l < n_list; l++)
				{
					if (s_list[l].id == s.id)
					{
						s_list[l].last_name = new_last_name;
						s_list[l].first_name = new_first_name;
						break;
					}
				}
				saveCourseIDTXT(c, s_list, n_list, c.class_name);
				delete[]s_list;
				s_list = NULL;
			}
		}
	}
	s.last_name = new_last_name;
	s.first_name = new_first_name;
	textColor(Notice);
	cout << "    Changing fullname successfully! New fullname is: " << s.first_name << " " << s.last_name << "!!!" << endl;
	textColor(NormalT);
}
void	changeBirthday(student &s)
{
	textColor(NormalT);
	cout << "Date Of Birth:" << endl;
	textColor(Notice);
	cout << "    In case the student's password is by default, if you change the birthday,"
		<< "the student's password might change automatically based on the date of birth" << endl;
	textColor(NormalT);
	cout << "Change it anyway? (Yes/No/?): ";
	if (!yesNoAns())
	{
		textColor(Notice);
		cout << "    Date of birth have no changing, it is keeping the old one!!!" << endl;
		textColor(NormalT);
		return;
	}
	bool change = false;
	if (s.password == dateToPass(s.dob))
		change = true;
	while (true)
	{
		textColor(NormalT);
		cout << "    Day: ";
		getNum(s.dob.dd);
		cout << "    Month: ";
		getNum(s.dob.mm);
		cout << "    Year: ";
		getNum(s.dob.yyyy);
		if (!checkValidDate(s.dob))
		{
			textColor(Notice);
			cout << "    !Invalid date, please try again." << endl;
		}
		else
		{
			textColor(NormalT);
			break;
		}
	}
	if (change == true)
	{
		s.password = dateToPass(s.dob);
	}
	textColor(Notice);
	cout << "    Changing day of birth successfully! New D.o.B is: " << s.dob.dd << "/" << s.dob.mm << "/" << s.dob.yyyy << "!!!" << endl;
	textColor(NormalT);
}
void	changeID(student &s)
{
	int id;
	int old_id = s.id;
	int edit_mode = 0;
	bool exist_id = false;
	do
	{
		textColor(NormalT);
		cout << "Student ID: ";
		getNum(id);
		if (id != s.id) // Nếu ng dùng nhập ko trùng ID cũ
		{
			if (isStudentExist(id)) // Nếu tồn tại ID r 
			{
				exist_id = true;
				textColor(Notice);
				cout << "    The student ID " << id << " existed in the data!!!" << endl << endl;
				textColor(NormalT);
				cout << "    Do you want to: " << endl
					<< "\t1. Edit student to another valid ID" << endl
					<< "\t2. Delete student who have ID: " << id << endl
					<< "\t3. Stop editing ID and keep the old one" << endl;
				edit_mode = askCommand(3);
				cout << endl;
				if (edit_mode == 1)
				{
					textColor(NormalT);
					continue;
				}
				else if (edit_mode == 2)
				{
					student delete_s;
					findStudentByID(id, delete_s);
					textColor(WOInfo);
					cout << "    This is any information of the student who you want to remove:" << endl;
					viewProfileInfo(delete_s.account);
					textColor(Notice);
					cout << "    After checking, do you want to remove this student?"
						<< "\n*Remember that, if you remove this student you can not restore the data of that student!" << endl;
					textColor(NormalT);
					cout << ">> (Yes/No/?): ";
					if (yesNoAns())
					{
						academic_year* student_course = NULL;
						int n_course = 0;
						if (loadStudentData(delete_s, student_course, n_course, delete_s.class_name, delete_s.id))
							removeAStudentNameInAllCourseIDTXT(delete_s, student_course, n_course);
						removeStudentTXT(id, delete_s.class_name);
						removeStudentFromStudentList(id, delete_s.class_name);
						textColor(Notice);
						cout << "    Removing the student who have the ID which you want to change with this student successfully!" << endl;
						delete[]student_course;
						textColor(NormalT);
						break;
					}
					else
					{
						textColor(Notice);
						cout << "    Stop removing the student who have the ID which you want to change with this student. "
							<< "\nAfter that we want to announce that we will keep the old ID of this student!" << endl;
						textColor(NormalT);
						break;
					}
				}
				else
				{
					textColor(Notice);
					cout << "    Changing ID unsuccessfully, stop editing ID and keep the old one!!!" << endl;
					textColor(NormalT);
					break;
				}
			}
			else // Không trùng ID 
			{
				textColor(Notice);
				cout << "    Changing ID successfully!!! New ID of this student is: " << s.id << "!!!" << endl;
				textColor(NormalT);
				break;
			}
		}
		else
		{
			exist_id = true;
			textColor(Notice);
			cout << "    ID which you have inputed is the old one so we should keep it for you!!!" << endl;
			textColor(NormalT);
			break;
		}
	} while (true);
	if (edit_mode == 2 || !exist_id)
	{
		// Sửa tên file [studentID].txt
		string old_name;
		studentTXTPath(s.class_name, old_id, old_name);
		string new_name;
		studentTXTPath(s.class_name, id, new_name);
		rename(old_name.c_str(), new_name.c_str());

		// Sửa trong file [class].txt
		student *s_list = NULL;
		int n_list = 0;
		readStudentList(s_list, n_list, s.class_name);
		for (int i = 0; i < n_list; i++)
		{
			if (s_list[i].id == old_id)
			{
				s_list[i].id = id;
				break;
			}
		}
		exportStudentList(s_list, n_list, s.class_name);
		delete[]s_list;
		s_list = NULL;
		// Sửa các file course.txt
		academic_year* s_yr = NULL;
		int n_yr = 0;
		course c;
		loadStudentData(s, s_yr, n_yr, s.class_name, id);
		for (int i = 0; i < n_yr; i++)
		{
			for (int j = 0; j < s_yr[i].n_term; j++)
			{
				for (int k = 0; k < s_yr[i].terms[j].n_course; k++)
				{
					readCourseIDTXT(s_yr[i].terms[j].courses[k].id, c, s_list, n_list, s_yr[i].terms[j].courses[k].class_name);
					for (int l = 0; l < n_list; l++)
					{
						if (s_list[l].id == old_id)
						{
							s_list[l].id = id;
							break;
						}
					}
					saveCourseIDTXT(c, s_list, n_list, c.class_name);
					delete[]s_list;
					s_list = NULL;
				}
			}
		}
	}
	s.id = id;
	textColor(NormalT);
}
void	changeGender(student &s)
{
	while (true)
	{
		textColor(NormalT);
		cout << "Gender (0: Male, 1: Female, -1: Other): ";
		getNum(s.gender);
		if (-1 <= s.gender && s.gender <= 1)
		{
			string gender_;
			if (s.gender == -1)
				gender_ = "Other";
			if (s.gender == 0)
				gender_ = "Male";
			if (s.gender == 1)
				gender_ = "Female";
			textColor(Notice);
			cout << "    Changing gender successfully! New gender of this student is: " << gender_ << "!!!" << endl;
			textColor(NormalT);
			break;
		}
		textColor(Notice);
		cout << "    !Invalid Input" << endl;
	}
	textColor(NormalT);
}
void	viewProfileInfo(const string& account)
{
	textColor(NormalT);
	cout << "\t\t\t\t\t\t  ";
	textColor(TitleFunc);
	cout << "Student's infomation" << endl;
	textColor(NormalT);
	//Kiểm tra trong sinh viên trước
	ifstream classTXT("data\\class.txt");
	int n_class;
	classTXT >> n_class;
	string* classList = new string[n_class];
	for (int i = 0; i < n_class; i++)
	{
		classTXT >> classList[i];
	}
	classTXT.close();

	string studentPath;
	student s;
	for (int i = 0; i < n_class; i++)
	{
		studentPath = "data\\" + classList[i] + "\\" + account + ".txt";
		ifstream studentTXT(studentPath);
		if (studentTXT.is_open())	//Nếu mở đúng file
		{
			string temp;
			//Bỏ qua dòng đầu
			getline(studentTXT, temp, '\n');
			//Số thứ tự
			getline(studentTXT, temp, ',');
			s.no = stoi(temp);
			//ID
			getline(studentTXT, temp, ',');
			s.id = stoi(temp);
			//Họ tên
			getline(studentTXT, s.last_name, ',');
			getline(studentTXT, s.first_name, ',');
			//Giới tính
			getline(studentTXT, temp, ',');
			s.gender = stoi(temp);
			//Năm sinh
			getline(studentTXT, temp, '-');
			s.dob.yyyy = stoi(temp);
			//Tháng
			getline(studentTXT, temp, '-');
			s.dob.mm = stoi(temp);
			//Ngày
			getline(studentTXT, temp, ',');
			s.dob.dd = stoi(temp);
			//Tài khoản - MK - Lớp
			getline(studentTXT, s.account, ',');
			getline(studentTXT, s.password, ',');
			getline(studentTXT, s.class_name, '\n');
			//Đọc khóa học
			int n_year;
			studentTXT >> n_year;
			studentTXT.seekg(-1, ios::cur);
			academic_year* years = nullptr;
			readSemesterCourses(studentTXT, years, n_year);
			//In ra màn hình
			textColor(SpTitleFunc);
			cout << "Student's Personal Information" << endl;
			textColor(NormalT);
			cout << "\tID: " << s.id << endl;
			cout << "\tName: " << s.last_name << " " << s.first_name << endl;
			cout << "\tClass: " << s.class_name << endl << endl
				<< "\tDate of Birth: " << s.dob.dd << "/" << s.dob.mm << "/" << s.dob.yyyy << endl;
			textColor(SpTitleFunc);
			cout << "Student's Education Information" << endl;
			textColor(NormalT);
			if (n_year == 0) // Đoạn này Huy thêm vô
			{
				textColor(Notice);
				cout << "\t<No Academic Year>" << endl;
				textColor(NormalT);
			}
			for (int j = 0; j < n_year; j++)
			{

				cout << "\t" << years[j].start << "-" << years[j].start + 1 << ":" << endl;
				for (int k = 0; k < years[j].n_term; k++)
				{
					cout << "\t    Term " << years[j].terms[k].no << ":" << endl;
					if (years[j].terms[k].n_course == 0) // Đoạn này H thêm vô
					{
						textColor(Notice);
						cout << "\t    <No Course>" << endl;
						textColor(NormalT);
					}
					for (int q = 0; q < years[j].terms[k].n_course; q++)
					{
						cout << "\t\t-" << years[j].terms[k].courses[q].id << "-" << years[j].terms[k].courses[q].class_name << endl;
					}
				}
			}

			studentTXT.close();
			return;
		}
		else	//Không đúng thì thôi
		{
			studentTXT.close();
		}
	}

	//Nếu không phải sv thì qua gv
	lecturer* l = nullptr;
	int n_lecturer;
	readLecturerTXT(l, n_lecturer);
	for (int i = 0; i < n_lecturer; i++)
	{
		if (l[i].account == account)
		{
			printLecturerInfo(l[i]);
			return;
		}
	}
}
void	courseDateGenerator(course &c)		//Hàm tạo ngày tháng đi học cho course_date
{
	// time_t : For historical reasons, it is generally implemented as an integral value 
	// representing the number of seconds elapsed since 00:00 hours, Jan 1, 1970 UTC (i.e., a unix timestamp). 
	// Although libraries may implement this type using alternative time representations.
	time_t start = timeSince1970(c.start_date.dd, c.start_date.mm, c.start_date.yyyy); //time_t là kiểu dữ liệu ghi số giây. Có sẵn trong <time.h>
	time_t end = timeSince1970(c.end_date.dd, c.end_date.mm, c.end_date.yyyy) - 86400; //end thừa một ngày

	tm			dateInfo;	//tm là kiểu struct lưu trữ các giá trị thời gian (ngày,tháng,năm,...). Có sẵn trong <time.h>
	dayhour		date;
	int			n = 0;
	c.n_course_date = 0;
	while (start <= end)
	{
		localtime_s(&dateInfo, &start);	//chuyển đổi từ time_t sang tm
		if (c.dow[dateInfo.tm_wday] == true)	//Kiểm tra xem có tiết hay không
		{
			date.dd = dateInfo.tm_mday;		//Sử dụng giá trị ngày tháng trong KDL tm để gán giá trị cho course_date
			date.mm = dateInfo.tm_mon + 1;
			date.yyyy = dateInfo.tm_year + 1900;
			date.start_hh = c.start_hour[dateInfo.tm_wday].hh;
			date.start_min = c.start_hour[dateInfo.tm_wday].mm;
			date.end_hh = c.end_hour[dateInfo.tm_wday].hh;
			date.end_min = c.end_hour[dateInfo.tm_wday].mm;
			push_back(c.course_date, c.n_course_date, date);
		}
		start = start + 86400;		//86400s = 1 ngày. Sang ngày tiếp theo để tiếp tục kiểm tra và lưu dữ liệu
	}
}

////////////////////////////////////////////////////

// Khánh Sơn region

void	clrscr()
{
	//	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	//	HANDLE	hConsoleOut;
	//	COORD	Home = { 0,0 };
	//	DWORD	dummy;
	//
	//	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	//	//SetConsoleTextAttribute(hStdout, 15);
	//	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	//	csbiInfo.dwCursorPosition.X = 0;
	//	csbiInfo.dwCursorPosition.Y = 0;
	//	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
	//}
	system("cls");
}
void	gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void	gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void	ToMau(int x, int y, string a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoxy(x, y);
	textColor(color);
	cout << a;
	textColor(7);
}
void	XoaManHinh()
{
	/*HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);*/
	system("cls");
}

// Menu thần thánh

bool is_loe_thay_login = false;
bool is_loe_thay_admin = false;
bool is_loe_thay_student = false;
bool is_loe_thay_lecturer = false;
bool is_loe_thay_class = true;
bool is_loe_thay_course = true;
bool is_loe_thay_attendance = true;
bool is_loe_thay_scoreboard = true;

void adminScoreboardMenu(string user_name) //
{
	do
	{
		if (!::is_loe_thay_scoreboard)
		{
			//system("color 20");
			int i = 80;
			int j = 15;
			int z = 30;
			while (1)
			{
				clrscr();
				i -= j;
				gotoXY(i, 0);
				textColor(Notice);
				cout << "				**********************" << endl;
				gotoXY(i, 1);
				cout << "				*     SCOREBOARD     *" << endl;
				gotoXY(i, 2);
				cout << "				**********************" << endl;
				textColor(NormalT);
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				textColor(WOInfo);
				cout << "				**********************" << endl;
				cout << "				*     SCOREBOARD     *" << endl;
				cout << "				**********************" << endl;
				i -= j;
				gotoXY(i, 3);
				cout << ">>>> 1/SEARCH AND VIEW SCOREBOARD OF A COURSE" << endl;
				textColor(NormalT);
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				textColor(Notice);
				clrscr();
				cout << "				**********************" << endl;
				cout << "				*     SCOREBOARD     *" << endl;
				cout << "				**********************" << endl;
				cout << ">>>> 1/SEARCH AND VIEW SCOREBOARD OF A COURSE" << endl;
				i -= j;
				gotoXY(i, 4);
				cout << ">>>> 2/EXPORT A SCORBOARD TO A CSV FILE" << endl;
				textColor(NormalT);
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				textColor(OInfo);
				clrscr();
				cout << "				**********************" << endl;
				cout << "				*     SCOREBOARD     *" << endl;
				cout << "				**********************" << endl;
				cout << ">>>> 1/SEARCH AND VIEW SCOREBOARD OF A COURSE" << endl;
				cout << ">>>> 2/EXPORT A SCORBOARD TO A CSV FILE" << endl;
				i -= j;
				gotoXY(i, 5);
				cout << ">>>> 3/BACK" << endl;
				gotoXY(i, 6);
				cout << ">>>> 4/LOGOUT" << endl;
				gotoXY(i, 7);
				cout << ">>>> 5/EXIT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			::is_loe_thay_scoreboard = true;
		}
		else
		{
			textColor(TitleFunc);
			cout << "				**********************" << endl;
			cout << "				*     SCOREBOARD     *" << endl;
			cout << "				**********************" << endl;
			textColor(NormalT);
			cout << ">>>> 1/SEARCH AND VIEW SCOREBOARD OF A COURSE" << endl;
			cout << ">>>> 2/EXPORT A SCORBOARD TO A CSV FILE" << endl;
			cout << ">>>> 3/BACK" << endl;
			//cout << ">>>> 4/LOGOUT" << endl;
			cout << ">>>> 4/EXIT" << endl;
		}
		int command = askCommand(4);

		switch (command)
		{
		case 1:
		{
			function24();
			break;
		}
		case 2:
		{
			function25();
			break;
		}
		case 3:
		{
			system("cls");
			break;
		}
		/*case 4:
		{
			system("cls");
			loginMenu();
			break;
		}*/
		case 4:
		{
			textColor(Notice);
			cout << "\tDo you want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 3 || command == 4) break;
		system("cls");
	} while (true);
}
void adminClassMenu(string user_name)
{
	do
	{
		if (!::is_loe_thay_class)
		{
			//system("color 10");
			int i = 80;
			int j = 15;
			int z = 30;
			while (1)
			{
				clrscr();
				i -= j;
				gotoXY(i, 0);
				cout << "				************************ " << endl;
				gotoXY(i, 1);
				cout << "				*         CLASS        *" << endl;
				gotoXY(i, 2);
				cout << "				************************ " << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				i -= j;
				gotoXY(i, 3);
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				i -= j;
				gotoXY(i, 4);
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				i -= j;
				gotoXY(i, 5);
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				i -= j;
				gotoXY(i, 6);
				cout << ">>>> 4/REMOVE A STUDENT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				cout << ">>>> 4/REMOVE A STUDENT" << endl;
				i -= j;
				gotoXY(i, 7);
				cout << ">>>> 5/CHANGE STUDENTS FROM CLASS A TO CLASS B" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				cout << ">>>> 4/REMOVE A STUDENT" << endl;
				cout << ">>>> 5/CHANGE STUDENTS FROM CLASS A TO CLASS B" << endl;
				i -= j;
				gotoXY(i, 8);
				cout << ">>>> 6/VIEW LIST OF CLASSES" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				cout << ">>>> 4/REMOVE A STUDENT" << endl;
				cout << ">>>> 5/CHANGE STUDENTS FROM CLASS A TO CLASS B" << endl;
				cout << ">>>> 6/VIEW LIST OF CLASSES" << endl;
				i -= j;
				gotoXY(i, 9);
				cout << ">>>> 7/VIEW LIST OF STUDENTS IN A CLASS" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************ " << endl;
				cout << "				*         CLASS        *" << endl;
				cout << "				************************ " << endl;
				cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
				cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
				cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
				cout << ">>>> 4/REMOVE A STUDENT" << endl;
				cout << ">>>> 5/CHANGE STUDENTS FROM CLASS A TO CLASS B" << endl;
				cout << ">>>> 6/VIEW LIST OF CLASSES" << endl;
				cout << ">>>> 7/VIEW LIST OF STUDENTS IN A CLASS" << endl;
				i -= j;
				gotoXY(i, 10);
				cout << ">>>> 8/BACK" << endl;
				gotoXY(i, 11);
				cout << ">>>> 9/LOGOUT" << endl;
				gotoXY(i, 12);
				cout << ">>>> 10/EXIT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			::is_loe_thay_class = true;
		}
		else
		{
			cout << "				************************ " << endl;
			cout << "				*         CLASS        *" << endl;
			cout << "				************************ " << endl;
			cout << ">>>> 1/IMPORT STUDENTS OF A CLASS FROM A CSV FILE" << endl;
			cout << ">>>> 2/MANUALLY ADD A NEW STUDENT TO A CLASS" << endl;
			cout << ">>>> 3/EDIT AN EXISTING STUDENT" << endl;
			cout << ">>>> 4/REMOVE A STUDENT" << endl;
			cout << ">>>> 5/CHANGE STUDENTS FROM CLASS A TO CLASS B" << endl;
			cout << ">>>> 6/VIEW LIST OF CLASSES" << endl;
			cout << ">>>> 7/VIEW LIST OF STUDENTS IN A CLASS" << endl;
			cout << ">>>> 8/BACK" << endl;
			//cout << ">>>> 9/LOGOUT" << endl;
			cout << ">>>> 9/EXIT" << endl;
		}

		int command = askCommand(9);
		switch (command)
		{
		case 1:
		{
			function06();
			break;
		}
		case 2:
		{
			function07();
			textColor(WOInfo);
			cout << "Please press 'Enter' to go back!!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 3:
		{
			function08();
			break;
		}
		case 4:
		{
			function09();
			textColor(WOInfo);
			cout << "Please press 'Enter' to go back!!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 5:
		{
			function10();
			textColor(WOInfo);
			cout << "Please press 'Enter' to go back!!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 6:
		{
			function11();
			//_getch();
			break;
		}
		case 7:
		{
			function12();
			//_getch();
			break;
		}
		case 8:
		{
			system("cls");
			//adminMenu(user_name);
			break;
		}
		/*case 9:
		{
			system("cls");
			loginMenu();
			break;
		}*/
		case 9:
		{
			textColor(Notice);
			cout << "\tDo you really want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 10 || command == 9 || command == 8)
			break;
		clrscr();
	} while (true);
}
void adminAttendanceMenu(string user_name)
{
	do
	{
		if (!::is_loe_thay_attendance)
		{
			//system("color 30");
			int i = 80;
			int j = 15;
			int z = 30;
			while (1)
			{
				clrscr();
				i -= j;
				gotoXY(i, 0);
				cout << "				************************* " << endl;
				gotoXY(i, 1);
				cout << "				*    ATTENDANCE LIST    *" << endl;
				gotoXY(i, 2);
				cout << "				************************* " << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************* " << endl;
				cout << "				*    ATTENDANCE LIST    *" << endl;
				cout << "				************************* " << endl;
				i -= j;
				gotoXY(i, 3);
				cout << ">>>> 1/SEARCH AND VIEW ATTENDANCE LIST OF A COURSE" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************* " << endl;
				cout << "				*    ATTENDANCE LIST    *" << endl;
				cout << "				************************* " << endl;
				cout << ">>>> 1/SEARCH AND VIEW ATTENDANCE LIST OF A COURSE" << endl;

				i -= j;
				gotoXY(i, 4);
				cout << ">>>> 2/EXPORT A ATTENDANCE LIST TO A CSV FILE" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				************************* " << endl;
				cout << "				*    ATTENDANCE LIST    *" << endl;
				cout << "				************************* " << endl;
				cout << ">>>> 1/SEARCH AND VIEW ATTENDANCE LIST OF A COURSE" << endl;
				cout << ">>>> 2/EXPORT A ATTENDANCE LIST TO A CSV FILE" << endl;
				i -= j;
				gotoXY(i, 5);
				cout << ">>>> 3/BACK" << endl;
				cout << ">>>> 4/LOGOUT" << endl;
				cout << ">>>> 5/EXIT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			::is_loe_thay_attendance = true;
		}
		else
		{
			cout << "				************************* " << endl;
			cout << "				*    ATTENDANCE LIST    *" << endl;
			cout << "				************************* " << endl;
			cout << ">>>> 1/SEARCH AND VIEW ATTENDANCE LIST OF A COURSE" << endl;
			cout << ">>>> 2/EXPORT A ATTENDANCE LIST TO A CSV FILE" << endl;
			cout << ">>>> 3/BACK" << endl;
			//cout << ">>>> 4/LOGOUT" << endl;
			cout << ">>>> 4/EXIT" << endl;
		}
		int command = askCommand(4);

		switch (command)
		{
		case 1:
		{
			function22_26();
			break;
		}
		case 2:
		{

			function27();
			break;
		}
		case 3:
		{
			system("cls");
			//adminClassMenu(user_name);
			break;
		}
		/*case 4:
		{
			system("cls");
			loginMenu();
			break;
		}*/
		case 4:
		{
			system("cls");
			textColor(Notice);
			cout << "\tDo you want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 3 || command == 5) break;
		clrscr();
	} while (true);
}
void adminCourseMenu(string user_name)
{
	do
	{
		if (!::is_loe_thay_course)
		{
			//system("color 40");
			int i = 80;
			int j = 15;
			int z = 30;
			while (1)
			{
				clrscr();
				i -= j;
				gotoXY(i, 0);
				cout << "				*************************** " << endl;
				gotoXY(i, 1);
				cout << "				*          COURSES        *" << endl;
				gotoXY(i, 2);
				cout << "				*************************** " << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				i -= j;
				gotoXY(i, 3);
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				i -= j;
				gotoXY(i, 4);
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				i -= j;
				gotoXY(i, 5);
				cout << ">>>> 3)Manually add a new course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				i -= j;
				gotoXY(i, 6);
				cout << ">>>> 4)Edit an existing course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				i -= j;
				gotoXY(i, 7);
				cout << ">>>> 5)Remove a course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				i -= j;
				gotoXY(i, 8);
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				i -= j;
				gotoXY(i, 9);
				cout << ">>>> 7)Add a specific student to a course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				cout << ">>>> 7)Add a specific student to a course." << endl;
				i -= j;
				gotoXY(i, 10);
				cout << ">>>> 8)View list of courses in the current semester." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				cout << ">>>> 7)Add a specific student to a course." << endl;
				cout << ">>>> 8)View list of courses in the current semester." << endl;
				i -= j;
				gotoXY(i, 11);
				cout << ">>>> 9)View list of students of a course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				cout << ">>>> 7)Add a specific student to a course." << endl;
				cout << ">>>> 8)View list of courses in the current semester." << endl;
				cout << ">>>> 9)View list of students of a course." << endl;
				i -= j;
				gotoXY(i, 12);
				cout << ">>>> 10)View attendance list of a course." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1)Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2)From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3)Manually add a new course." << endl;
				cout << ">>>> 4)Edit an existing course." << endl;
				cout << ">>>> 5)Remove a course." << endl;
				cout << ">>>> 6)Remove a specific student from a course." << endl;
				cout << ">>>> 7)Add a specific student to a course." << endl;
				cout << ">>>> 8)View list of courses in the current semester." << endl;
				cout << ">>>> 9)View list of students of a course." << endl;
				cout << ">>>> 10)View attendance list of a course." << endl;
				i -= j;
				gotoXY(i, 13);
				cout << ">>>> 11)Create / update / delete / view all lecturers." << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			i = 80;
			while (1)
			{
				clrscr();
				cout << "				*************************** " << endl;
				cout << "				*          COURSES        *" << endl;
				cout << "				*************************** " << endl;
				cout << ">>>> 1/  Create / update / delete / view academic years (2018-2019), and semesters(Fall)." << endl;
				cout << ">>>> 2/  From a semester, import courses such as CTT008, CTT010 from a csv file." << endl;
				cout << ">>>> 3/  Manually add a new course." << endl;
				cout << ">>>> 4/  Edit an existing course." << endl;
				cout << ">>>> 5/  Remove a course." << endl;
				cout << ">>>> 6/  Remove a specific student from a course." << endl;
				cout << ">>>> 7/  Add a specific student to a course." << endl;
				cout << ">>>> 8/  View list of courses in the current semester." << endl;
				cout << ">>>> 9/  View list of students of a course." << endl;
				cout << ">>>> 10/ View attendance list of a course." << endl;
				cout << ">>>> 11/ Create / update / delete / view all lecturers." << endl;
				cout << ">>>> 12/ BACK" << endl;
				cout << ">>>> 13/ LOGOUT" << endl;
				cout << ">>>> 14/ EXIT" << endl;
				if (i <= 0) break;
				Sleep(z);
			}
			::is_loe_thay_course = true;
		}
		else
		{
			cout << "				*************************** " << endl;
			cout << "				*          COURSES        *" << endl;
			cout << "				*************************** " << endl;
			cout << ">>>> 1/  Create / update / delete / view academic years, and semesters." << endl;
			cout << ">>>> 2/  Import courses from a csv file." << endl;
			cout << ">>>> 3/  Manually add a new course." << endl;
			cout << ">>>> 4/  Edit an existing course." << endl;
			cout << ">>>> 5/  Remove a course." << endl;
			cout << ">>>> 6/  Remove a specific student from a course." << endl;
			cout << ">>>> 7/  Add a specific student to a course." << endl;
			cout << ">>>> 8/  View list of courses in the current semester." << endl;
			cout << ">>>> 9/  View list of students of a course." << endl;
			cout << ">>>> 10/ View attendance list of a course." << endl;
			cout << ">>>> 11/ Create / update / delete / view all lecturers." << endl;
			cout << ">>>> 12/ BACK" << endl;
			cout << ">>>> 13/ EXIT" << endl;
		}
		int command = askCommand(13);

		switch (command)
		{
		case 1:
		{
			system("cls");
			function13();
			break;
		}
		case 2:
		{
			function14();
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 3:
		{
			function15();
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 4:
		{
			function16();
			break;
		}
		case 5:
		{
			function17();
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 6:
		{
			function18();
			break;
		}
		case 7:
		{
			function19();
			break;
		}
		case 8:
		{
			function20();
			break;
		}
		case 9:
		{
			function21();
			break;
		}
		case 10:
		{
			function22_26();
			break;
		}
		case 11:
		{
			function23();
			break;
		}
		case 12:
		{
			system("cls");
			//adminMenu(user_name);
			break;
		}
		/*case 13:
		{
			system("cls");
			loginMenu();
			break;
		}*/
		case 13:
		{
			system("cls");
			textColor(Notice);
			cout << "\tDo you want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 12 || command == 13) break;
		system("cls");
	} while (true);
}
void lecturerMenu(string user_name)
{
	do
	{
		if (!::is_loe_thay_lecturer)
		{
			//system("color 80");
			int z = 30, mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				Sleep(z);
				mau++;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				Sleep(z);
				mau++;
				if (m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				Sleep(z);
				mau++;
				if (m == 2) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name << endl;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name << endl;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				textColor(mau);
				gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				textColor(mau);
				gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
				textColor(mau + 1);
				gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				textColor(mau);
				gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
				textColor(mau + 1);
				gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
				textColor(mau + 2);
				gotoXY(10, 14); cout << "<<<>>> 9/VIEW A SCOREBOARD";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				textColor(mau);
				gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
				textColor(mau + 1);
				gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
				textColor(mau + 2);
				gotoXY(10, 14); cout << "<<<>>> 9/VIEW A SCOREBOARD";
				textColor(mau + 3);
				gotoXY(10, 15); cout << "<<<>>> 10/BACK";
				gotoXY(10, 16); cout << "<<<>>> 11/LOGOUT";
				gotoXY(10, 17); cout << "<<<>>> 12/EXIT" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<        LECTURER       >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
				textColor(mau + 3);
				gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
				textColor(mau);
				gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
				gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
				gotoXY(10, 14); cout << "<<<>>> 9/VIEW A SCOREBOARD";
				gotoXY(10, 15); cout << "<<<>>> 10/BACK";
				gotoXY(10, 16); cout << "<<<>>> 11/LOGOUT";
				gotoXY(10, 17); cout << "<<<>>> 12/EXIT" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			clrscr();
			textColor(OInfo);
			gotoXY(47, 0); cout << "*************************";
			gotoXY(47, 1); cout << "<        LECTURER       >";
			gotoXY(47, 2); cout << "*************************";
			gotoXY(10, 4); cout << "WELCOME " << user_name;
			gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
			gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
			gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
			gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
			gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
			gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
			gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
			gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
			gotoXY(10, 14); cout << "<<<>>> 9/VIEW A SCOREBOARD";
			gotoXY(10, 15); cout << "<<<>>> 10/BACK";
			gotoXY(10, 16); cout << "<<<>>> 11/LOGOUT";
			gotoXY(10, 17); cout << "<<<>>> 12/EXIT" << endl;
			::is_loe_thay_lecturer = true;
		}
		else
		{
			textColor(OInfo);
			gotoXY(47, 0); cout << "*************************";
			gotoXY(47, 1); cout << "<        LECTURER       >";
			gotoXY(47, 2); cout << "*************************";
			gotoXY(47, 4); cout << "WELCOME " << user_name;
			gotoXY(10, 4); cout << "WELCOME " << user_name;
			gotoXY(10, 6); cout << "<<<>>> 1/VIEW MY PROFILE INFORMATION";
			gotoXY(10, 7); cout << "<<<>>> 2/CHANGE MY PASSWORD";
			gotoXY(10, 8); cout << "<<<>>> 3/VIEW LIST OF COURSES IN THE CURRENT SEMESTER";
			gotoXY(10, 9); cout << "<<<>>> 4/VIEW LIST OF STUDENTS OF A COURSE";
			gotoXY(10, 10); cout << "<<<>>> 5/VIEW ATTENDANCE LIST OF A COURSE";
			gotoXY(10, 11); cout << "<<<>>> 6/EDIT AN ATTENDANCE";
			gotoXY(10, 12); cout << "<<<>>> 7/IMPORT SCOREBOARD OF A COURSE (MIDTERM, FINAL, LAB, BONUS) FROM A CSV FILE";
			gotoXY(10, 13); cout << "<<<>>> 8/EDIT GRADE OF A STUDENT";
			gotoXY(10, 14); cout << "<<<>>> 9/VIEW A SCOREBOARD";
			gotoXY(10, 15); cout << "<<<>>> 10/BACK";
			gotoXY(10, 16); cout << "<<<>>> 11/LOGOUT";
			gotoXY(10, 17); cout << "<<<>>> 12/EXIT" << endl;
		}
		textColor(NormalT);
		cout << ">>>> Command: ";
		int command = askCommand(12);
		switch (command)
		{
		case 1:
		{
			viewProfileInfo(user_name);
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 2:
		{
			changePassword(user_name);
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			function28(user_name);
			cout << "Please press any key to go back" << endl;
			_getch();
			break;
		}
		case 4:
		{
			system("cls");
			function29(user_name);
			break;
		}
		case 5:
		{
			system("cls");
			function30(user_name);
			break;
		}
		case 6:
		{
			system("cls");
			function31(user_name);
			break;
		}
		case 7:
		{
			system("cls");
			function32(user_name);
			break;
		}
		case 8:
		{
			function33(user_name);
			break;
		}
		case 9:
		{
			system("cls");
			function34(user_name);
			break;
		}
		case 10:
		{
			system("cls");
			break;
		}
		case 11:
		{
			system("cls");
			break;
		}
		case 12:
		{
			textColor(Notice);
			cout << "\tDo you really want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 10 || command == 11)
			break;
		system("cls");
	} while (true);

}
void adminMenu(string user_name)
{
	int command = 0;
	do
	{
		if (!::is_loe_thay_admin)
		{
			//system("color 90");
			int z = 80, mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				Sleep(z);
				mau++;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				Sleep(z);
				mau++;
				if (m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/COURSE";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/COURSE";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/SCOREBOARD";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(47, 0); cout << "*************************";
				gotoXY(47, 1); cout << "<         ADMIN         >";
				gotoXY(47, 2); cout << "*************************";
				textColor(mau + 1);
				gotoXY(10, 4); cout << "WELCOME " << user_name;
				textColor(mau + 2);
				gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
				textColor(mau + 3);
				gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
				textColor(mau);
				gotoXY(10, 8); cout << "<<<>>> 3/COURSE";
				textColor(mau + 1);
				gotoXY(10, 9); cout << "<<<>>> 4/SCOREBOARD";
				textColor(mau + 2);
				gotoXY(10, 10); cout << "<<<>>> 5/ATTENDANCE LIST";
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;

			clrscr();
			textColor(OInfo);
			gotoXY(47, 0); cout << "*************************";
			gotoXY(47, 1); cout << "<         ADMIN         >";
			gotoXY(47, 2); cout << "*************************";
			gotoXY(10, 4); cout << "WELCOME " << user_name;
			gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
			gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
			gotoXY(10, 8); cout << "<<<>>> 3/COURSE";
			gotoXY(10, 9); cout << "<<<>>> 4/SCOREBOARD";
			gotoXY(10, 10); cout << "<<<>>> 5/ATTENDANCE LIST";
			gotoXY(10, 11);
			cout << "<<<>>> 6/BACK" << endl
				<< setw(10) << " " << "<<<>>> 7/LOGOUT" << endl
				<< setw(10) << " " << "<<<>>> 8/EXIT" << endl;
			::is_loe_thay_admin = true;
		}
		else
		{
			clrscr();
			textColor(OInfo);
			gotoXY(47, 0); cout << "*************************";
			gotoXY(47, 1); cout << "<         ADMIN         >";
			gotoXY(47, 2); cout << "*************************";
			gotoXY(10, 4); cout << "WELCOME " << user_name;
			gotoXY(10, 6); cout << "<<<>>> 1/CHANGE PASSWORD";
			gotoXY(10, 7); cout << "<<<>>> 2/CLASS";
			gotoXY(10, 8); cout << "<<<>>> 3/COURSE";
			gotoXY(10, 9); cout << "<<<>>> 4/SCOREBOARD";
			gotoXY(10, 10); cout << "<<<>>> 5/ATTENDANCE LIST";
			gotoXY(10, 11);
			cout << "<<<>>> 6/BACK" << endl
				<< setw(10) << " " << "<<<>>> 7/LOGOUT" << endl
				<< setw(10) << " " << "<<<>>> 8/EXIT" << endl;
		}
		textColor(NormalT);
		cout << ">>>> Command: ";
		int command = askCommand(8);
		system("cls");
		switch (command)
		{
		case 1:
		{
			system("cls");
			changeAdminPassword();
			break;
		}
		case 2:
		{
			system("cls");
			adminClassMenu(user_name);
			break;
		}
		case 3:
		{
			system("cls");
			adminCourseMenu(user_name);
			break;
		}
		case 4:
		{
			system("cls");
			adminScoreboardMenu(user_name);
			break;
		}
		case 5:
		{
			system("cls");
			adminAttendanceMenu(user_name);
			break;
		}
		case 6:
		{
			system("cls");
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!!";
			textColor(NormalT);
			_getch();
			break;
		}
		case 7:
		{
			system("cls");
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!!";
			textColor(NormalT);
			_getch();
			break;
		}
		case 8:
		{
			is_loe_thay_login = false;
			is_loe_thay_lecturer = false;
			textColor(NormalT);
			system("cls");
			loginMenu();
			break;
		}
		}
		if (command == 6 || command == 7)
			break;
		system("cls");
	} while (true);
	if (command == 9)
	{
		textColor(Notice);
		cout << "\tDo you really want to exit? (Yes/No/?): ";
		if (yesNoAns())
			exitOurProgram();
		return;
	}
}
void thankYou(int mau)
{
	textColor(mau);
	cout << " 0000000000 0000   0000        000         000    0000 000  0000 0000    0000    000000    00000     0000   00    00" << endl
		<< "     00      00     00        00 00        0000    00   00  00     00    00    000    000   000       00    00    00" << endl
		<< "     00      00     00       00   00       00 00   00   00 00        00 00    000      000  000       00    00    00" << endl
		<< "     00      000000000      000000000      00  00  00   0000          000    000        000 000       00    00    00" << endl
		<< "     00      00     00     00       00     00   00 00   00 000        000     000      000  000       00    00    00" << endl
		<< "     00      00     00    00         00    00    0000   00   000      000      000    000    000     00" << endl
		<< "    0000    0000   0000 0000         0000 0000    000  000    000    00000       000000        000000       00    00" << endl << endl;
	Sleep(100);
}
void exitOurProgram()
{
	for (int m = 1; m < 5; m++)
	{
		clrscr();
		if (m % 2 == 0)
		{
			thankYou(14);
			thankYou(12);
			thankYou(14);
			thankYou(12);
		}
		else
		{
			thankYou(12);
			thankYou(14);
			thankYou(12);
			thankYou(14);
		}
	}
	clrscr();
	for (int m = 1; m < 11; m++)
	{
		gotoXY(0, 11);
		if (m % 2 == 0)
			thankYou(12);
		else
			thankYou(14);
	}
	clrscr();
	gotoXY(5, 9);
	textColor(14);
	cout << "Thanks for your using! Have a nice day, my customer!" << endl << endl
		<< setw(5) << " " << "To do this software, we spent more than 720 hours from the Tet holiday to the very-end deadline date" << endl
		<< setw(5) << " " << "of the project.All the members of group 09 acknowledge that this project is the first program " << endl
		<< setw(5) << " " << "that the group has to carry out completely under the the guidance of the lecturers from creating the idea" << endl
		<< setw(5) << " " << "to realizing that concept and building the program perfectly as much as possible." << endl << endl
		<< setw(5) << " " << "In the process of using this program, there might be some bugs that unexpectedly ocurred," << endl
		<< setw(5) << " " << "we are very sorry users for that and we look forward you to reporting back to us for the program" << endl
		<< setw(5) << " " << "to be more completed in the future." << endl
		<< setw(5) << " " << ">>> After all, we still hope you to have a good experience with our program, customer." << endl << endl
		<< setw(5) << " " << "Group 9 sincerely thanks!";
	gotoXY(0, 21);
	textColor(WOInfo);
	cout << "Please press 'Enter' to continue to exit!";
	_getch();
	clrscr();
	gotoXY(5, 10);
	textColor(14);
	cout << "Thanks for teachers' guidance!" << endl << endl
		<< setw(5) << " " << "Sincerly thanks to Mr.Ho Tuan Thanh, Mr.Truong Phuoc Loc and Mrs.Nguyen Hai Minh for everything they taught!!" << endl << endl;
	Sleep(200);
	textColor(13);
	gotoXY(5, 10);
	cout << "Thanks for teachers' guidance!" << endl << endl
		<< setw(5) << " " << "Sincerly thanks to Mr.Ho Tuan Thanh, Mr.Truong Phuoc Loc and Mrs.Nguyen Hai Minh for everything they taught!!" << endl << endl;
	Sleep(200);
	textColor(WOInfo);
	cout << setw(80) << " " << "Ho Chi Minh, 2019/04/08" << endl
		<< setw(80) << " " << "        Group 09" << endl
		<< setw(80) << " " << "      Do Quoc Huy" << endl
		<< setw(80) << " " << "    Dang Khanh Son" << endl
		<< setw(80) << " " << "   Dinh Hoang Duong" << endl
		<< setw(80) << " " << " Bui Nguyen Minh Chau" << endl;
	Sleep(1500);
	textColor(12);
	gotoXY(5, 10);
	cout << "Thanks for teachers' guidance!" << endl << endl
		<< setw(5) << " " << "Sincerly thanks to Mr.Ho Tuan Thanh, Mr.Truong Phuoc Loc and Mrs.Nguyen Hai Minh for everything they taught!!" << endl << endl;
	Sleep(2500);
	exit(0);
}
void loginMenu()
{
	do
	{
		if (!::is_loe_thay_login)
		{
			::is_loe_thay_login = true;
			//system("color 75");
			int z = 80, mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				gotoXY(49, 0);
				textColor(mau); cout << "<<<<<  GROUP 9  >>>>>";
				mau++;
				Sleep(z - 70);
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
				gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
				mau++;
				Sleep(z - 70);
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
				gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
				textColor(mau + 1);
				gotoXY(49, 3); cout << "000000000000000000000";
				gotoXY(49, 4); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 5); cout << "0       LOGIN       0";
				gotoXY(49, 6); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 7); cout << "000000000000000000000";
				mau++;
				Sleep(z);
				if (m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
				gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
				textColor(mau + 1);
				gotoXY(49, 3); cout << "000000000000000000000";
				gotoXY(49, 4); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 5); cout << "0       LOGIN       0";
				gotoXY(49, 6); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 7); cout << "000000000000000000000";
				textColor(mau + 2);
				gotoXY(40, 9); cout << "1111111111111";
				gotoXY(40, 10); cout << "1           1";
				gotoXY(40, 11); cout << "1  1/LOGIN  1";
				gotoXY(40, 12); cout << "1           1";
				gotoXY(40, 13); cout << "1111111111111";
				mau++;
				Sleep(z);
				if (m == 2) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
				gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
				textColor(mau + 1);
				gotoXY(49, 3); cout << "000000000000000000000";
				gotoXY(49, 4); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 5); cout << "0       LOGIN       0";
				gotoXY(49, 6); cout << "0" << setw(19) << " " << "0";
				gotoXY(49, 7); cout << "000000000000000000000";
				textColor(mau + 2);
				gotoXY(40, 9); cout << "1111111111111";
				gotoXY(40, 10); cout << "1           1";
				gotoXY(40, 11); cout << "1  1/LOGIN  1";
				gotoXY(40, 12); cout << "1           1";
				gotoXY(40, 13); cout << "1111111111111";
				textColor(mau + 3);
				gotoXY(65, 9); cout << "222222222222";
				gotoXY(65, 10); cout << "2          2";
				gotoXY(65, 11); cout << "2  2/EXIT  2";
				gotoXY(65, 12); cout << "2          2";
				gotoXY(65, 13); cout << "222222222222";
				mau++;
				Sleep(z);
				if (m == 1 || m == 3) mau = 10;
			}
			clrscr();
			textColor(OInfo);
			gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
			gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
			gotoXY(49, 3); cout << "000000000000000000000";
			gotoXY(49, 4); cout << "0" << setw(19) << " " << "0";
			gotoXY(49, 5); cout << "0       LOGIN       0";
			gotoXY(49, 6); cout << "0" << setw(19) << " " << "0";
			gotoXY(49, 7); cout << "000000000000000000000";
			gotoXY(40, 9); cout << "1111111111111";
			gotoXY(40, 10); cout << "1           1";
			gotoXY(40, 11); cout << "1  1/LOGIN  1";
			gotoXY(40, 12); cout << "1           1";
			gotoXY(40, 13); cout << "1111111111111";
			gotoXY(65, 9); cout << "222222222222";
			gotoXY(65, 10); cout << "2          2";
			gotoXY(65, 11); cout << "2  2/EXIT  2";
			gotoXY(65, 12); cout << "2          2";
			gotoXY(65, 13); cout << "222222222222";
		}
		else
		{
			clrscr();
			textColor(OInfo);
			gotoXY(49, 0); cout << "<<<<<  GROUP 9  >>>>>";
			gotoXY(49, 1); cout << "<<<<<   MENU    >>>>>";
			gotoXY(49, 3); cout << "000000000000000000000";
			gotoXY(49, 4); cout << "0" << setw(19) << " " << "0";
			gotoXY(49, 5); cout << "0       LOGIN       0";
			gotoXY(49, 6); cout << "0" << setw(19) << " " << "0";
			gotoXY(49, 7); cout << "000000000000000000000";
			gotoXY(40, 9); cout << "1111111111111";
			gotoXY(40, 10); cout << "1           1";
			gotoXY(40, 11); cout << "1  1/LOGIN  1";
			gotoXY(40, 12); cout << "1           1";
			gotoXY(40, 13); cout << "1111111111111";
			gotoXY(65, 9); cout << "222222222222";
			gotoXY(65, 10); cout << "2          2";
			gotoXY(65, 11); cout << "2  2/EXIT  2";
			gotoXY(65, 12); cout << "2          2";
			gotoXY(65, 13); cout << "222222222222";
		}
		textColor(NormalT);
		cout << "\n>>>>Command: ";
		int command = askCommand(2);
		if (command == 2)
			exitOurProgram();
		string user_name;
		system("cls");
		int log = function01(user_name);
		switch (log)
		{
		case 1:
		{
			studentMenu(user_name);
			break;
		}
		case 10:
		{
			lecturerMenu(user_name);
			break;
		}
		case 100:
		{
			adminMenu(user_name);
			break;
		}
		}
		system("cls");
	} while (true);
}
void studentMenu(string user_name)
{
	int id = stoi(user_name);
	do
	{
		if (!::is_loe_thay_student)
		{
			::is_loe_thay_student = true;
			int z = 80, mau = 10;
			//system("color 10");
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>";
				Sleep(z);
				mau++;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(10, 4);
				textColor(mau + 1); cout << "WELCOME " << user_name;
				Sleep(z);
				mau++;
				if (m == 4) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				Sleep(z);
				mau++;
				if (m == 2) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				textColor(mau); cout << setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				textColor(mau); cout << setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl;
				textColor(mau + 1); cout << setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				textColor(mau); cout << setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl;
				textColor(mau + 1); cout << setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 5/VIEW SCHEDULES" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			mau = 10;
			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				textColor(mau); cout << setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl;
				textColor(mau + 1); cout << setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 5/VIEW SCHEDULES" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 6/VIEW MY SCORES" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}

			for (int m = 0; m < 5; m++)
			{
				clrscr();
				textColor(mau);
				textColor(mau);
				gotoXY(51, 0); cout << "<<<<<<<<<>>>>>>>>>";
				gotoXY(51, 1); cout << "<     STUDENT    >";
				gotoXY(51, 2); cout << "<<<<<<<<<>>>>>>>>>" << endl << endl;
				textColor(mau + 1); cout << setw(10) << " " << "WELCOME " << user_name << endl << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl;
				textColor(mau); cout << setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl;
				textColor(mau + 1); cout << setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl;
				textColor(mau + 2); cout << setw(10) << " " << "<<<>>> 5/VIEW SCHEDULES" << endl;
				textColor(mau + 3); cout << setw(10) << " " << "<<<>>> 6/VIEW MY SCORES" << endl;
				textColor(mau);
				cout << setw(10) << " " << "<<<>>> 7/BACK" << endl
					<< setw(10) << " " << "<<<>>> 8/LOGOUT" << endl
					<< setw(10) << " " << "<<<>>> 9/EXIT" << endl;
				Sleep(z);
				mau++;
				if (m == 1 || m == 3) mau = 10;
			}
			clrscr();
			textColor(OInfo);
			cout << setw(51) << " " << "<<<<<<<<<>>>>>>>>>" << endl
				<< setw(51) << " " << "<     STUDENT    >" << endl
				<< setw(51) << " " << "<<<<<<<<<>>>>>>>>>" << endl << endl
				<< setw(10) << " " << "WELCOME " << user_name << endl << endl
				<< setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl
				<< setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl
				<< setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl
				<< setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl
				<< setw(10) << " " << "<<<>>> 5/VIEW SCHEDULES" << endl
				<< setw(10) << " " << "<<<>>> 6/VIEW MY SCORES" << endl
				<< setw(10) << " " << "<<<>>> 7/BACK" << endl
				<< setw(10) << " " << "<<<>>> 8/LOGOUT" << endl
				<< setw(10) << " " << "<<<>>> 9/EXIT" << endl;
			textColor(NormalT);
		}
		else
		{
			clrscr();
			textColor(OInfo);
			cout << setw(51) << " " << "<<<<<<<<<>>>>>>>>>" << endl
				<< setw(51) << " " << "<     STUDENT    >" << endl
				<< setw(51) << " " << "<<<<<<<<<>>>>>>>>>" << endl << endl
				<< setw(10) << " " << "WELCOME " << user_name << endl << endl
				<< setw(10) << " " << "<<<>>> 1/VIEW MY PROFILE INFORMATION" << endl
				<< setw(10) << " " << "<<<>>> 2/CHANGE PASSWORD" << endl
				<< setw(10) << " " << "<<<>>> 3/CHECK-IN" << endl
				<< setw(10) << " " << "<<<>>> 4/VIEW CHECK-IN RESULT" << endl
				<< setw(10) << " " << "<<<>>> 5/VIEW SCHEDULES" << endl
				<< setw(10) << " " << "<<<>>> 6/VIEW MY SCORES" << endl
				<< setw(10) << " " << "<<<>>> 7/BACK" << endl
				<< setw(10) << " " << "<<<>>> 8/LOGOUT" << endl
				<< setw(10) << " " << "<<<>>> 9/EXIT" << endl;
		}
		textColor(NormalT);
		cout << "\n\t  >>> Command: ";
		int command = askCommand(9);

		switch (command)
		{
		case 1:
		{
			textColor(NormalT);
			system("cls");
			viewProfileInfo("s" + user_name);
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 2:
		{
			textColor(NormalT);
			system("cls");
			int id = stoi(user_name);
			student s;
			academic_year *s_year = NULL;
			int n_s = 0;
			findStudentByID(id, s);
			loadStudentData(s, s_year, n_s, s.class_name, id);
			changePassword(s);
			saveStudent(s, s_year, n_s);
			delete[] s_year;
			textColor(WOInfo);
			cout << "\nPlease press 'Enter' to go back!!" << endl;
			textColor(NormalT);
			_getch();
			break;
		}
		case 3:
		{
			textColor(NormalT);
			system("cls");
			function35(user_name);
			break;
		}
		case 4:
		{
			textColor(NormalT);
			system("cls");
			function36(user_name);
			break;
		}
		case 5:
		{
			textColor(NormalT);
			system("cls");
			function37(user_name);
			break;
		}
		case 6:
		{
			textColor(NormalT);
			system("cls");
			function38(user_name);
			break;
		}
		case 7:
		{
			textColor(NormalT);
			system("cls");
			loginMenu();
			break;
		}
		case 8:
		{
			is_loe_thay_login = false;
			is_loe_thay_student = false;
			textColor(NormalT);
			system("cls");
			loginMenu();
			break;
		}
		case 9:
		{
			textColor(Notice);
			cout << "\tDo you really want to exit? (Yes/No/?): ";
			if (yesNoAns())
				exitOurProgram();
			break;
		}
		}
		if (command == 9 || command == 8)
			break;
		system("cls");
	} while (true);
}

bool importScoreBoard(student*& s_list, int& n_s, string path)
{
	ifstream fin;
	fin.open(path);

	if (fin.fail())
		return false;
	string temp;
	// lấy dòng đầu tiên ra, không đọc dòng đó
	getline(fin, temp, '\n');

	int i = 0;
	char		catch_err_eof;
	int			catch_err;
	student s;
	while (!fin.eof())
	{
		fin.get(catch_err_eof);
		catch_err = fin.tellg();
		if (catch_err_eof == '\n' || catch_err_eof == ' ' || catch_err_eof == '\t' || catch_err_eof == ',' || catch_err < 0)
			break;
		else
			fin.seekg(-1, ios::cur);
		try
		{
			getline(fin, temp, ',');
			s.no = stoi(temp);
			getline(fin, temp, ',');
			s.id = stoi(temp);
			getline(fin, s.last_name, ',');
			getline(fin, s.first_name, ',');
			getline(fin, temp, ',');
			s.midterm = stod(temp);
			getline(fin, temp, ',');
			s.lab = stod(temp);
			getline(fin, temp, ',');
			s.final_point = stod(temp);
			getline(fin, temp, '\n');
			s.bonus = stod(temp);
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
		catch (const std::out_of_range&)
		{
			return false;
		}

		push_back(s_list, n_s, s);
	}
	fin.close();
	return true;
}
///////////////////////////////////////////////////
bool isOverlappingTime(dayhour*& new_course_date, int n_new_course_date, academic_year*& years, int n_yr, int start_year, int sem, string _id = "", string _class = "");

// Stein

//Xử lý họ tên của giáo viên
string nameProcesser_StringOutput(string full_name)
{
	//Input là char *
	transform(full_name.begin(), full_name.end(), full_name.begin(), ::tolower);
	string yourName = full_name;
	string codeName;
	codeName = yourName[0];

	size_t n = yourName.find(" ", 0);
	if (n == string::npos)
	{
		return yourName;
	}
	char *last_word = new char;
	//char* last_word = NULL;
	while (n != string::npos)
	{
		last_word = &yourName[n + 1];
		codeName = codeName + yourName[n + 1];
		n = yourName.find(" ", n + 1);
	}
	codeName.replace(codeName.length() - 1, codeName.length(), last_word);
	//delete last_word; không xóa vì trigger breakpoint
	return codeName;
}
//Input là courseID và class_name. Biến c để chút nữa lưu dữ liệu
void readCourseTXT_OnlyCourseInfo(string courseID, string class_name, course &c)
{
	string coursePath;
	courseIDTXTPath(class_name, courseID, coursePath);
	ifstream courseTXT(coursePath);
	courseTXT >> c.id;
	courseTXT.ignore();
	getline(courseTXT, c.name);
	courseTXT >> c.class_name;
	courseTXT >> c.lecturer;
	courseTXT >> c.start_date.yyyy;
	courseTXT >> c.start_date.mm;
	courseTXT >> c.start_date.dd;
	courseTXT >> c.end_date.yyyy;
	courseTXT >> c.end_date.mm;
	courseTXT >> c.end_date.dd;

	for (int i = 0; i < 7; i++)
	{
		courseTXT >> c.dow[i];
	}
	for (int i = 0; i < 7; i++)
	{
		if (c.dow[i] == 1)
		{
			courseTXT >> c.start_hour[i].hh;
			courseTXT >> c.start_hour[i].mm;
			courseTXT >> c.end_hour[i].hh;
			courseTXT >> c.end_hour[i].mm;
		}
	}//Ngày nào không có giờ học thì mặc định giờ bắt đầu và kết thúc là 0:00
	courseTXT >> c.room;
	courseTXT.close();
}
bool courseTangleChecker(const course &c)
{
	//Kiểm tra xem giờ học có trùng nhau hay không
	string classPath;
	classTXTPath(c.class_name, classPath);
	ifstream classTXT(classPath);
	int n;	student s;

	char temp[30] = { '\0' };
	//Read the brief info of 1 student
	classTXT.getline(temp, 5, '\n');
	n = atoi(temp);
	classTXT.getline(temp, 5, ',');
	s.no = atoi(temp);

	classTXT.getline(temp, 10, ',');
	s.id = atoi(temp);

	getline(classTXT, s.last_name);
	getline(classTXT, s.first_name);
	classTXT.close();
	//Use it to load more student's data
	academic_year *currentYear = new academic_year[6];
	int n_course;
	loadStudentData(s, currentYear, n_course, c.class_name, s.id);
	//Indentified input course's term
	int course_term = monthToSemesterInt(c.start_date.mm);

	for (int i = 0; i < n_course; i++)
	{
		if (currentYear[i].start == c.start_date.yyyy)
		{
			for (int j = 0; j < currentYear[i].n_term; j++)
			{
				if (currentYear[i].terms[j].no == course_term)
				{
					for (int k = 0; k < currentYear[i].terms[j].n_course; k++)
					{
						course existedCourse;
						readCourseTXT_OnlyCourseInfo(currentYear[i].terms[j].courses[k].id, currentYear[i].terms[j].courses[k].class_name, existedCourse);

						if (existedCourse.id == c.id  && existedCourse.class_name == c.class_name)
						{	//Câu if này dùng cho hàm courseEditing. Nếu lịch học trùng với chính nó thì không tính
							continue;
						}
						else {
							for (int p = 0; p < 7; p++)
							{
								if (existedCourse.dow[p] == c.dow[p])
								{
									if ((existedCourse.start_hour[p].hh >= c.start_hour[p].hh && existedCourse.start_hour[p].hh < c.end_hour[p].hh))
									{
										return true;
									}
									else if ((existedCourse.end_hour[p].hh <= c.end_hour[p].hh &&existedCourse.end_hour[p].hh > c.start_hour[p].hh))
									{
										return true;
									}
									else if ((existedCourse.start_hour[p].hh < c.start_hour[p].hh && existedCourse.end_hour[p].hh > c.end_hour[p].hh))
									{
										return true;
									}
								}
							}
						}
					}
					return false;
				}
			}
			return false;
		}

	}
	return false;
}
void nameProcesser_CharOutput(char full_name[])
{
	//	Input là char *
	string s = nameProcesser_StringOutput(full_name);
	char *c;
	c = &s[0];
	strcpy_s(full_name, 50, c);
}
//Kiểm tra ngày tháng input. Nhập sai false, đúng là true
bool dateInputChecking(int dd, int mm, int yy)
{
	switch (mm)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if (dd < 1 || dd > 31)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
	{

		if (dd < 1 || dd>30)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}
	case 2:
	{
		if (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0))
		{
			if (dd < 1 || dd > 29)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if (dd < 1 || dd > 28)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	default:
		return false;
	}
}
//Kiểm tra thời gian input
bool timeInputChecking(hour start, hour end)
{
	if ((start.hh * 60 + start.mm) < (end.hh * 60 + end.mm))
	{
		if (start.hh < 24 && start.hh >= 0 && end.hh < 24 && end.hh >= 0)
		{
			if (start.mm < 60 && start.mm >= 0 && end.mm < 60 && end.mm >= 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
//Kiểm tra lớp học có chưa
bool isClassExisted(string &class_name)
{
	strUpr(class_name);
	ifstream classTXT("data\\class.txt");
	int n_class;
	classTXT >> n_class;
	string temp;
	for (int i = 0; i < n_class; i++)
	{
		classTXT >> temp;
		if (class_name == temp)
		{
			return true;
		}
	}
	return false;
}
//Kiểm tra khóa học tồn tại hay chưa
bool isCourseExistInClass(const string &class_name, const string &id)
{
	string path;
	courseIDTXTPath(class_name, id, path);
	ifstream courseTXT;
	courseTXT.open(path);
	if (courseTXT.is_open())
	{
		courseTXT.close();
		return true;
	}
	else
	{
		courseTXT.close();
		return false;
	}
}
//Hàm nhập dữ liệu thủ công
bool courseInformationInput(course &c)
{
	//Trả về true nếu nhập thành công và ngược lại
	string id;
	string lecturer_name;

	//Phần nhập của người dùng
	cout << "Course ID: ";
	getline(cin, c.id);
	//transform(c.id.begin(), c.id.end(), c.id.begin(), ::toupper);
	strUpr(c.id);
	cout << "Course name: ";
	getline(cin, c.name);
	cout << "Class: ";
	getline(cin, c.class_name);
	strUpr(c.class_name);
	transform(c.class_name.begin(), c.class_name.end(), c.class_name.begin(), ::toupper);
	cout << endl;

	//Kiểm tra lớp học nhập vào
	while (isClassExisted(c.class_name) == false)
	{
		cout << "Class doesn't exist" << endl;
		cout << "\t1. Re-enter class name" << endl;
		cout << "\t2. Go out and initialize a class" << endl;
		cout << "\tI wanna: ";
		int ans = 0;
		getNum(ans);
		while (ans != 1 && ans != 2)
		{
			cout << "\tInvalid Command" << endl;
			cout << "\tPlease input again: ";
			getNum(ans);
			break;
		}
		if (ans == 1)
		{
			cout << "\tClass name:";
			getline(cin, c.class_name, '\n');
			strUpr(c.class_name);
		}
		else
		{
			return false;
		}
	}
	//Kiểm tra khóa học tồn tại chưa
	while (isCourseExistInClass(c.class_name, c.id) == true)
	{
		cout << "This course ID has already existed" << endl;
		cout << "Would you like to: " << endl;
		cout << "\t1. Re-enter course ID" << endl;
		cout << "\t2. Go out" << endl;
		int ans = 0;
		getNum(ans);
		while (ans != 1 && ans != 2)
		{
			cout << "\tInvalid Command" << endl;
			cout << "\tPlease input again: ";
			getNum(ans);
			break;
		}
		if (ans == 1)
		{
			cout << "\tCourse ID: ";
			getline(cin, c.id);
		}
		else
		{
			return false;
		}
	}

	string classPath;
	classTXTPath(c.class_name, classPath);
	ifstream classTXT(classPath);
	cout << "The lecturer's account: ";
	getline(cin, c.lecturer, '\n');
	///getline(cin, lecturer_name);
	//lecturer_name = nameProcesser_StringOutput(lecturer_name);
	//c.lecturer = lecturer_name;

	do
	{
		cout << "Start date" << endl;
		cout << "\tDay: ";
		getNum(c.start_date.dd);
		cout << "\tMonth: ";
		getNum(c.start_date.mm);
		cout << "\tYear: ";
		getNum(c.start_date.yyyy);

		if (dateInputChecking(c.start_date.dd, c.start_date.mm, c.start_date.yyyy))
			break;
		cout << "Invalid date, please try again" << endl;

	} while (true);

	do
	{
		cout << "End date" << endl;
		cout << "\tDay: ";
		getNum(c.end_date.dd);
		cout << "\tMonth: ";
		getNum(c.end_date.mm);
		cout << "\tYear: ";
		getNum(c.end_date.yyyy);

		if (c.end_date.yyyy >= c.start_date.yyyy)
		{
			break;
		}
		cout << "Invalid date, please try again" << endl;

	} while (true);

	while (c.end_date.yyyy == c.start_date.yyyy && c.end_date.mm < c.start_date.mm)
	{
		cout << "Invalid end month, please try again. End month: ";
		getNum(c.end_date.mm);
	}

	while (c.end_date.yyyy == c.start_date.yyyy && c.end_date.mm == c.start_date.mm && c.end_date.dd < c.start_date.dd)
	{
		cout << "Invalid end day, please try again. End day: ";
		getNum(c.end_date.dd);
	}

	// ======================= Đoạn này Huy sửa giao diện chọn ngày
	int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);
	cout << "Academic Year: " << start_year_ << "-" << start_year_ + 1 << endl;
	cout << "Semester :" << monthToSemesterString(c.start_date.mm) << endl << endl;
	int sem_ = monthToSemesterInt(c.start_date.mm);

	// Nếu giảng viên tồn tại thì đưa TKB giảng viên ra để dễ chọn ngày không trùng giờ học
	lecturer l_;
	l_.account = c.lecturer;
	int year_i_ = -1, sem_j_ = -1;
	if (isLecturerExist(l_))
	{
		for (int i = 0; i < l_.n_year; i++)
		{
			if (l_.years[i].start == start_year_)
			{
				year_i_ = i;
				for (int j = 0; j < l_.years[i].n_term; j++)
				{
					if (l_.years[i].terms[j].no == sem_)
					{
						sem_j_ = j;
						cout << "Lecturer's Schedule: " << endl;
						viewLecturerGeneralSchedule(true, l_.years[i].terms[j]);
						break;
					}
				}
			}
		}
	}
	cout << endl;
	char date_of_week_[][10] = { "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday", "Sunday" };
	cout << "Please choose date(s) that have this course: " << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << "\t" << i + 1 << ". " << date_of_week_[i];
		cout << endl;
	}
	cout << "You can choose many commands at once: ";
	int *choose = NULL;
	int n_selected = askManyCommands(1, 7, choose);
	for (int i = 0; i < n_selected; i++)
	{
		c.dow[choose[i] - 1] = true;
	}
	hour strict_start_hour_of_first_course = { 6, 0 },
		strict_end_hour_of_last_course = { 21, 30 };

	// Nhập ngày giờ
	do
	{
		cout << "Input start - end hour for " << n_selected << " day(s):" << endl;
		for (int i = 0; i < 7; i++)
		{
			if (c.dow[i])
			{
				do
				{
					cout << date_of_week_[i] << endl;
					cout << "\tStart hour: ";
					getNum(c.start_hour[i].hh);
					cout << "\tStart minute: ";
					getNum(c.start_hour[i].mm);
					cout << "\tEnd hour: ";
					getNum(c.end_hour[i].hh);
					cout << "\tEnd minute: ";
					getNum(c.end_hour[i].mm);
					if (timeInputChecking(c.start_hour[i], c.end_hour[i]) &&
						!(c.start_hour[i] < strict_start_hour_of_first_course ||
							c.end_hour[i] > strict_end_hour_of_last_course))
					{
						break;
					}
					cout << "Incorect time-set. Please try again." << endl;

				} while (true);
			}
		}
		if (c.n_course_date > 0)
		{
			delete[]c.course_date;
			c.course_date = NULL;
			c.n_course_date = 0;
		}
		courseDateGenerator(c);
		if (year_i_ >= 0 && sem_j_ >= 0) // Nếu gv có dạy vào hk đã chọn
		{
			// Kiểm ta giờ học có bị trùng hay không
			if (isOverlappingTime(c.course_date, c.n_course_date, l_.years, l_.n_year, start_year_, sem_))
			{
				cout << "The time-set you inputted was overlapping lecturer's Schedule" << endl
					<< "\tDo you want to:" << endl
					<< "\t1. Re-Enter another time-set" << endl
					<< "\t2. Stop adding new course" << endl;
				if (askCommand(2) == 2)
				{
					delete[]choose;
					return false;
				}
				else
					continue;
			}

		}
		if (!courseTangleChecker(c)) // Hàm kiểm tra giờ học học sinh có bị trùng hay không
		{
			break;
		}
		else
		{
			cout << "This course time may entangle with student's schedule. Do you want to add this new course (Yes/No/?): " << endl;
			if (yesNoAns())
			{
				break;
			}
		}
	} while (true);

	// ======================= Hết đoạn Huy sửa giao diện chọn ngày

	cout << "Room: ";
	getline(cin, c.room);
	strUpr(c.room);

	//	Tạo course_date
	courseDateGenerator(c);
	//	Tạo n_student
	classTXT >> c.n_student;
	classTXT.close();
	delete[]choose;
	return true;
}
bool	editSomeDataOfACourse(course& c, student*& s, int& n_s, int*& commands, int n_command)
{
	//Trả về true nếu nhập thành công và ngược lại
	string id;
	string lecturer_name;
	string old_class = c.class_name;
	string old_id = c.id;
	bool is_delete_attendance = false;
	for (int i = 0; i < n_command; i++)
	{
		switch (commands[i])
		{
		case 1: // id - class
		{
			//Phần nhập của người dùng
			cout << "Course ID: ";
			getline(cin, c.id);
			strUpr(c.id);
			cout << "Class: ";
			string old_class = c.class_name;
			getline(cin, c.class_name);
			strUpr(c.class_name);

			cout << endl;

			//Kiểm tra lớp học nhập vào
			while (isClassExisted(c.class_name) == false)
			{
				cout << "Class doesn't exist" << endl;
				cout << "\t1. Re-enter class name" << endl;
				cout << "\t2. Go out and initialize a class" << endl;
				cout << "\tI wanna: ";
				int ans = 0;
				getNum(ans);
				while (ans != 1 && ans != 2)
				{
					cout << "\tInvalid Command" << endl;
					cout << "\tPlease input again: ";
					getNum(ans);
					break;
				}
				if (ans == 1)
				{
					cout << "\tClass name:";
					getline(cin, c.class_name, '\n');
					strUpr(c.class_name);
				}
				else
				{
					return false;
				}

				//Kiểm tra khóa học tồn tại chưa
				while (isCourseExistInClass(c.class_name, c.id) == true)
				{
					cout << "This course ID has already existed" << endl;
					cout << "Would you like to: " << endl;
					cout << "\t1. Re-enter course ID" << endl;
					cout << "\t2. Go out" << endl;
					int ans = 0;
					getNum(ans);
					while (ans != 1 && ans != 2)
					{
						cout << "\tInvalid Command" << endl;
						cout << "\tPlease input again: ";
						getNum(ans);
						break;
					}
					if (ans == 1)
					{
						cout << "\tCourse ID: ";
						getline(cin, c.id);
					}
					else
					{
						return false;
					}
				}

			}
			if (c.class_name != old_class)
			{
				cout << "You are about to change the class of this course, it means that all the students data will be removed \n"
					<< "And the students of class " << c.class_name << " will be automatically moved to this course" << endl;
				cout << "Please confirm (Yes/No/?): ";
				if (!yesNoAns())
				{
					return false;
				}
				readStudentList(s, n_s, c.class_name);
			}
			break;
		}
		case 2:
		{
			cout << "Course name: ";
			getline(cin, c.name, '\n');
			break;
		}
		case 3:
		{
			cout << "The lecturer's account: ";
			getline(cin, c.lecturer, '\n');
			break;
		}
		case 4: // start date
		{
			do
			{
				cout << "Start date" << endl;
				cout << "\tDay: ";
				getNum(c.start_date.dd);
				cout << "\tMonth: ";
				getNum(c.start_date.mm);
				cout << "\tYear: ";
				getNum(c.start_date.yyyy);

				if (dateInputChecking(c.start_date.dd, c.start_date.mm, c.start_date.yyyy))
					break;
				cout << "Invalid date, please try again" << endl;

			} while (true);

			do
			{
				cout << "End date" << endl;
				cout << "\tDay: ";
				getNum(c.end_date.dd);
				cout << "\tMonth: ";
				getNum(c.end_date.mm);
				cout << "\tYear: ";
				getNum(c.end_date.yyyy);

				if (c.end_date.yyyy >= c.start_date.yyyy)
				{
					break;
				}
				cout << "Invalid date, please try again" << endl;

			} while (true);

			while (c.end_date.yyyy == c.start_date.yyyy && c.end_date.mm < c.start_date.mm)
			{
				cout << "Invalid end month, please try again. End month: ";
				getNum(c.end_date.mm);
			}

			while (c.end_date.yyyy == c.start_date.yyyy && c.end_date.mm == c.start_date.mm && c.end_date.dd < c.start_date.dd)
			{
				cout << "Invalid end day, please try again. End day: ";
				getNum(c.end_date.dd);
			}

			// ======================= Đoạn này Huy sửa giao diện chọn ngày
			int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);
			cout << "Academic Year: " << start_year_ << "-" << start_year_ + 1 << endl;
			cout << "Semester :" << monthToSemesterString(c.start_date.mm) << endl << endl;
			int sem_ = monthToSemesterInt(c.start_date.mm);

			// Nếu giảng viên tồn tại thì đưa TKB giảng viên ra để dễ chọn ngày không trùng giờ học
			lecturer l_;
			l_.account = c.lecturer;
			int year_i_ = -1, sem_j_ = -1;
			if (isLecturerExist(l_))
			{
				for (int i = 0; i < l_.n_year; i++)
				{
					if (l_.years[i].start == start_year_)
					{
						year_i_ = i;
						for (int j = 0; j < l_.years[i].n_term; j++)
						{
							if (l_.years[i].terms[j].no == sem_)
							{
								sem_j_ = j;
								cout << "Lecturer's Schedule: " << endl;
								viewLecturerGeneralSchedule(true, l_.years[i].terms[j]);
								break;
							}
						}
					}
				}
			}
			cout << endl;
			char date_of_week_[][10] = { "Sunday", "Monday", "Tuesday", "Wednesday",
				"Thursday", "Friday", "Saturday", "Sunday" };
			cout << "Please choose date(s) that have this course: " << endl;
			for (int i = 0; i < 7; i++)
			{
				cout << "\t" << i + 1 << ". " << date_of_week_[i];
				cout << endl;
			}
			cout << "You can choose many commands at once: ";
			int* choose = NULL;
			int n_selected = askManyCommands(1, 7, choose);
			for (int i = 0; i < n_selected; i++)
			{
				c.dow[choose[i] - 1] = true;
			}
			hour strict_start_hour_of_first_course = { 6, 0 },
				strict_end_hour_of_last_course = { 21, 30 };

			// Nhập ngày giờ
			do
			{
				cout << "Input start - end hour for " << n_selected << " day(s):" << endl;
				for (int i = 0; i < 7; i++)
				{
					if (c.dow[i])
					{
						do
						{
							cout << date_of_week_[i] << endl;
							cout << "\tStart hour: ";
							getNum(c.start_hour[i].hh);
							cout << "\tStart minute: ";
							getNum(c.start_hour[i].mm);
							cout << "\tEnd hour: ";
							getNum(c.end_hour[i].hh);
							cout << "\tEnd minute: ";
							getNum(c.end_hour[i].mm);
							if (timeInputChecking(c.start_hour[i], c.end_hour[i]) &&
								!(c.start_hour[i] < strict_start_hour_of_first_course ||
									c.end_hour[i] > strict_end_hour_of_last_course))
							{
								break;
							}
							cout << "Incorect time-set. Please try again." << endl;

						} while (true);
					}
				}
				if (c.n_course_date > 0)
				{
					delete[]c.course_date;
					c.course_date = NULL;
					c.n_course_date = 0;
				}
				courseDateGenerator(c);
				if (year_i_ >= 0 && sem_j_ >= 0) // Nếu gv có dạy vào hk đã chọn
				{
					// Kiểm ta giờ học có bị trùng hay không
					if (isOverlappingTime(c.course_date, c.n_course_date, l_.years, l_.n_year, start_year_, sem_, old_id, old_class))
					{
						cout << "The time-set you inputted was overlapping lecturer's Schedule" << endl
							<< "\tDo you want to:" << endl
							<< "\t1. Re-Enter another time-set" << endl
							<< "\t2. Stop adding new course" << endl;
						if (askCommand(2) == 2)
						{
							delete[]choose;
							return false;
						}
						else
							continue;
					}

				}
				if (!courseTangleChecker(c)) // Hàm kiểm tra giờ học học sinh có bị trùng hay không
				{
					break;
				}
				else
				{
					cout << "This course time may entangle with student's schedule. Do you want to add this new course (Yes/No/?): " << endl;
					if (yesNoAns())
					{
						break;
					}
				}
			} while (true);

			is_delete_attendance = true;
			break;
		}
		case 5:
		{
			cout << "Room: ";
			getline(cin, c.room);
			strUpr(c.room);
		}

		}
	}
	courseDateGenerator(c);
	if (is_delete_attendance)
	{
		for (int i = 0; i < n_s; i++)
		{
			s[i].n_date = c.n_course_date;
			delete s[i].attendance;
			s[i].attendance = NULL;
		}
	}
	textColor(Notice);
	cout << "    Saving new data successfully" << endl;
	textColor(WOInfo);
	cout << "\nPlease press 'Enter' to go back" << endl;
	textColor(NormalT);
	_getch();
	return true;
}
//Sắp xếp thứ tự mảng acadeic_year 
void sortAscendingAcademicYears_Cyan(academic_year a[], int n)
{
	academic_year temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].start > a[j].start)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}
//Sắp xếp thứ tự học kỳ
void sortAscendingTerms_Cyan(academic_year &y)
{
	term temp;
	for (int i = 0; i < y.n_term; i++)
	{
		for (int j = i + 1; j < y.n_term; j++)
		{
			if (y.terms[i].no > y.terms[j].no)
			{
				temp = y.terms[i];
				y.terms[i] = y.terms[j];
				y.terms[j] = y.terms[i];
			}
		}
	}
}

//Kiểm tra sự tồn tại của [c.id].txt 

//Nếu người dùng muốn ghi đè thì True không thì False
void saveOneNewCourseToSemesterTXT(const course &c)
{
	//Giải thích
	/*
		Kiểm tra năm học của course:
			Nếu chưa có thì tạo rồi ghi lại file
			Nêu đã có:
				Kiểm tra học kỳ:
					Nếu chưa có thì tạo rồi thêm vào mảng
					Nếu đã có thì thêm course id và class mới vào
	*/
	int course_term = monthToSemesterInt(c.start_date.mm);
	academic_year *year = NULL;
	int n;
	readSemesterTXT(year, n);

	// ========= Dòng này Huy thêm vào

	// Nếu theo như cách cũ thì HK 2 năm bắt đầu khóa học là 2019 thì năm học sẽ là 2019-2020
	// Sửa thành HK 2 năm bắt đầu khóa học là 2019 thì nă học sẽ là 2018-2019

	// Các dòng mà Huy đã thêm vào:
	// 	int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);
	//  if (year[i].start == start_year_)
	//	year[i + 1].start = start_year_;
	//	year[i + 1].end = start_year_ + 1;

	int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);

	//Thông tin tất cả khóa học được lưu vào mảng year[] và cập nhật thông tin mới vào file semester.txt
	for (int i = 0; i < n; i++)
	{
		//if (year[i].start == c.start_date.yyyy)
		if (year[i].start == start_year_)
		{
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].no == course_term)
				{
					for (int k = 0; k < year[i].terms[j].n_course; k++)
					{
						if (year[i].terms[j].courses[k] == c)
						{
							return;
						}
						else
						{
							if (k == year[i].terms[j].n_course - 1)
							{
								moreSize(year[i].terms[j].courses, year[i].terms[j].n_course);
								year[i].terms[j].courses[k + 1].id = c.id;
								year[i].terms[j].courses[k + 1].class_name = c.class_name;

								saveSemesterTXT(year, n);

								return;
							}
						}
					}
				}
				else
				{
					if (j == year[i].n_term - 1)
					{
						moreSize(year[i].terms, year[i].n_term);
						year[i].terms[j + 1].no = course_term;
						year[i].terms[j + 1].n_course = 1;
						year[i].terms[j + 1].courses = new courseID[1];
						year[i].terms[j + 1].courses[0].id = c.id;
						year[i].terms[j + 1].courses[0].class_name = c.class_name;

						//Sắp xếp lại học kỳ cho đúng thứ tự
						for (int k = 0; k < year[i].n_term - 1; k++)
						{
							for (int q = k + 1; q < year[i].n_term; q++)
							{
								if (year[i].terms[k].no > year[i].terms[q].no)
								{
									term temp;
									temp.courses = new courseID[year[i].terms[k].n_course];
									temp = year[i].terms[k];
									year[i].terms[k] = year[i].terms[q];
									year[i].terms[q] = temp;
								}
							}
						}
						saveSemesterTXT(year, n);
						return;
					}
				}
			}
		}
		else
		{
			if (i == n - 1)
			{
				moreSize(year, n);
				// year[i + 1].start = c.start_date.yyyy;
				year[i + 1].start = start_year_;
				//year[i + 1].end = c.start_date.yyyy + 1;
				year[i + 1].end = start_year_ + 1;
				year[i + 1].n_term = 1;
				year[i + 1].terms = new term[1];
				year[i + 1].terms[0].no = course_term;
				year[i + 1].terms[0].n_course = 1;
				year[i + 1].terms[0].courses = new courseID[1];
				year[i + 1].terms[0].courses[0].class_name = c.class_name;
				year[i + 1].terms[0].courses[0].id = c.id;

				//Sắp xếp lại năm học cho đúng thứ tự
				sortAscending(year, n);
				saveSemesterTXT(year, n);

				return;
			}
		}
	}
}
void saveOneNewCourseToStudentTXT(const course &c)
{
	student *s = NULL;
	academic_year *year = NULL;
	int n, n_course;
	//Kiểm ra học kỳ của course c
	int course_term = monthToSemesterInt(c.start_date.mm);

	//Lưu danh sách sinh viên vào mảng s
	readStudentList(s, n, c.class_name);

	for (int i = 0; i < n; i++)
	{
		//Lấy thông tin hiện tại cho mảng year
		loadStudentData(s[i], year, n_course, s[i].class_name, s[i].id);
		//Cập nhật khóa học mới vào mảng year
		addCourseToStructAcademicYear(c, year, n_course, c.start_date.yyyy, c.start_date.yyyy + 1, course_term);
		//Lưu lại
		saveStudent(s[i], year, n_course);
	}
	delete[]s;
	delete[]year;
}
void saveOneNewCourseToLecturerTXT(const course &c)
{
	//Kiểm ra học kỳ của course c
	int course_term = monthToSemesterInt(c.start_date.mm);

	//Kiểm tra sự tồn tại của giảng viên trong lecturer.txt
	lecturer newBee;
	newBee.account = c.lecturer;
	newBee.name = c.lecturer;
	int ans = isLecturerExist(newBee);

	// =============== nhũng dòng này Huy đã thêm vào:
	// 	int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);
	// 	addCourseToStructAcademicYear(c, newBee.years, newBee.n_year, start_year_, start_year_+ 1, course_term);
	//  addCourseToLecturerTXT(newBee, c, start_year_, start_year_ + 1, course_term);

	int start_year_ = monthToAcademicYear(c.start_date.mm, c.start_date.yyyy);

	if (ans == 0)//Giảng viên không tồn tại
	{
		newBee.n_year = 0;
		newBee.password = newBee.name;
		newBee.password = sha256(newBee.password);
		//addCourseToStructAcademicYear(c, newBee.years, newBee.n_year, c.start_date.yyyy, c.start_date.yyyy + 1, course_term);
		addCourseToStructAcademicYear(c, newBee.years, newBee.n_year, start_year_, start_year_ + 1, course_term);

		lecturer *gv = NULL; int n_gv;
		readLecturerTXT(gv, n_gv);//Lưu thông tin của những giảng viên hiện hữu vào mảng gv

		push_back(gv, n_gv, newBee);

		saveLecturerTXT(gv, n_gv);
		delete[]gv;
	}
	else if (ans == 1)//Giảng viên hiện diện sẵn rồi
	{
		// addCourseToLecturerTXT(newBee, c, c.start_date.yyyy, c.start_date.yyyy + 1, course_term);
		addCourseToLecturerTXT(newBee, c, start_year_, start_year_ + 1, course_term);
	}
	else if (ans == -1)//Không có lecturer.txt nào cả
	{
		cout << "Can't find lecturer.txt" << endl;
	}
}
void function15()
{
	cout << "\t\t\t\t\t\t";
	textColor(TitleFunc);
	cout << "Manually add a course" << endl;
	textColor(NormalT);
	course c;
	if (courseInformationInput(c) == true)
	{
		saveOneNewCourseToSemesterTXT(c);

		int n;
		student *s = NULL;
		readStudentList(s, n, c.class_name);

		saveCourseIDTXT(c, s, n, c.class_name);

		saveOneNewCourseToStudentTXT(c);

		saveOneNewCourseToLecturerTXT(c);

		cout << "Add successfully !!" << endl;
	}
	else
	{
		cout << "Fail to add a new course" << endl;
	}
}

/////////////////////////////////

// Stein
void printLecturerInfo(const lecturer& l)
{
	textColor(Notice);
	cout << l.name << endl;
	textColor(NormalT);

	if (l.n_year == 0) // Đoạn này Huy thêm vô
	{
		textColor(Notice);
		cout << " <No Academic Year>" << endl;
		textColor(NormalT);
		return;
	}
	for (int j = 0; j < l.n_year; j++)
	{

		cout << " " << l.years[j].start << "-" << l.years[j].start + 1 << ":" << endl;
		for (int k = 0; k < l.years[j].n_term; k++)
		{
			cout << "\tTerm " << l.years[j].terms[k].no << ":" << endl;
			if (l.years[j].terms[k].n_course == 0) // Đoạn này H thêm vô
			{
				textColor(Notice);
				cout << "\t <No Course>" << endl;
				textColor(NormalT);
			}
			for (int q = 0; q < l.years[j].terms[k].n_course; q++)
			{
				cout << "\t- " << l.years[j].terms[k].courses[q].id << "-" << l.years[j].terms[k].courses[q].class_name << endl;
			}
		}
	}
}
void viewLecturerList()
{
	lecturer* l = NULL;
	int n_lecturer;
	readLecturerTXT(l, n_lecturer);
	if (n_lecturer == 0)
	{
		cout << "    There is no any lecturer to view" << endl;
	}
	for (int i = 0; i < n_lecturer; i++)
	{
		cout << i + 1 << "/    ";
		printLecturerInfo(l[i]);
	}
}
void addOneNewLecturer()
{
	do // Huy thêm do..while vào
	{
		int ans = 0;
		cout << "Please input new lecturer's fullname: ";
		string lecturerName;
		getline(cin, lecturerName, '\n');
		lecturerName = nameProcesser_StringOutput(lecturerName);

		lecturer newBee;
		newBee.account = newBee.name = lecturerName;
		newBee.password = sha256(newBee.account);

		int check = isLecturerExist(newBee);
		if (check == 1)	//Giảng viên đã tồn tại
		{
			textColor(Notice);
			cout << "Lecturer has been already existed or someone has the same account name !!" << endl;
			textColor(NormalT);
			printLecturerInfo(newBee);
			cout << "\t1/ I'll add some numbers or symbols into my name to distinguish between Lecturer '" << newBee.account << "' and the new lecturer" << endl;
			cout << "\t2/ I changed my mind. Let me go back" << endl;
			/*cin >> ans;
			while (ans != 1 && ans != 2)
			{
				cout << "Please choose your options correctly!" << endl;
				cout << "1/ I'll add some numbers or symbols into my name to distinguish" << endl;
				cout << "2/ I changed my mind. Let me go back" << endl;
				cin >> ans;
			}*/
			ans = askCommand(2); //
			if (ans == 1)
			{
				//cin.ignore(); //
				//addOneNewLecturer(); //
				continue;
			}
			else if (ans == 2)
			{
				return;
			}
		}
		else
		{
			int n_lecturer;
			lecturer* l = nullptr;
			readLecturerTXT(l, n_lecturer);

			lecturer* temp = new lecturer[n_lecturer + 1];
			for (int i = 0; i < n_lecturer; i++)
			{
				temp[i] = l[i];
			}
			n_lecturer++;
			temp[n_lecturer - 1].years = NULL;
			temp[n_lecturer - 1] = newBee;
			saveLecturerTXT(temp, n_lecturer);
			cout << "Add one new lecturer successfully!!" << endl;
			delete[]l; //
			delete[]temp; //
			return;
		}
	} while (true);
}
void updateOneLecturer()
{
	cout << "Please input Lecturer's fullname whom you would like to update information: ";
	string lecturerName;
	getline(cin, lecturerName, '\n');
	lecturerName = nameProcesser_StringOutput(lecturerName);

	lecturer newBee;
	newBee.account = newBee.name = lecturerName;
	newBee.password = sha256(newBee.account);

	int check = isLecturerExist(newBee);

	if (check == 1)	//Giảng viên tồn tại
	{
		cout << "Please update the new name of lecturer account '" << newBee.account << "': ";
		getline(cin, newBee.name, '\n');

		lecturer* l = nullptr;
		int n_lecturer;
		readLecturerTXT(l, n_lecturer);

		for (int i = 0; i < n_lecturer; i++)
		{
			if (l[i].account == newBee.account)
			{
				l[i].name = newBee.name;
				saveLecturerTXT(l, n_lecturer);

				cout << "Update successfully!" << endl;
				break;
			}
		}
		delete[]l; //
	}
	else
	{
		textColor(Notice);
		cout << "This lecturer doesn't exist" << endl;
		textColor(NormalT);
		cout << "\t1/ Let me re-enter the name" << endl;
		cout << "\t2/ Get out" << endl;
		int ans;
		//cin >> ans;//
		getNum(ans); //
		while (ans != 1 && ans != 2)
		{
			cout << "\tDon't know what to do. Please re-enter your option" << endl;
			cout << "\t1/ Let me re-enter the name" << endl;
			cout << "\t2/ Get out" << endl;
			cin >> ans;
		}
		if (ans == 1)
		{
			//cin.ignore();
			updateOneLecturer();
		}
		else if (ans == 2)
		{
			return;
		}
	}
}
void removeOneLecturer()
{
	cout << "Remove A lecturer account" << endl;
	textColor(Notice);
	cout << "Please Notice that you have to remove all of the lecturer's course before deleting him/her account!!! " << endl;
	textColor(NormalT);
	cout << "Please input Lecturer's name whom you woudld like to remove: ";
	string lecturerName;
	getline(cin, lecturerName, '\n');
	lecturerName = nameProcesser_StringOutput(lecturerName);

	lecturer newBee;
	newBee.account = newBee.name = lecturerName;
	newBee.password = sha256(newBee.account);

	int check = isLecturerExist(newBee);	//Kiểm tra giảng viên
	if (check == 1)	//Giảng viên tồn tại
	{
		int isTeaching = 0;
		for (int i = 0; i < newBee.n_year; i++)	//Kiểm tra liệu giảng viên có đang dạy lớp nào không?
		{
			for (int j = 0; j < newBee.years[i].n_term; j++)
			{
				if (newBee.years[i].terms[j].n_course != 0)
				{
					isTeaching++;
				}
			}
		}

		if (isTeaching == 0)	//Hiện không dạy lớp nào.
		{
			lecturer* temp = NULL;
			int n_lecturer;
			readLecturerTXT(temp, n_lecturer);
			//Loại giảng viên khỏi mảng
			lecturer* l = new lecturer[n_lecturer];
			int i = 0;
			for (int j = 0; j < n_lecturer; j++)
			{
				if (temp[j].account != newBee.account)
				{
					l[i] = temp[j];
					i++;
				}
			}
			n_lecturer--;	//Giảm số lượng giảng viên

			saveLecturerTXT(l, n_lecturer);	//Ghi đè thông tin mới
			cout << "Remove successfully!" << endl;
			delete[]l; //
		}
		else	//Có đứng lớp
		{
			cout << "Currently, lecturer is having " << isTeaching << " class(es)" << endl;
			printLecturerInfo(newBee);
			textColor(Notice);
			cout << "You have to remove course(s) first" << endl;
			textColor(NormalT);
		}
	}
	else	//Giảng viên không tồn tại
	{
		cout << "This lecturer doesn't exist" << endl;
		cout << "1/ Let me re-enter the name" << endl;
		cout << "2/ Get out" << endl;
		int ans = askCommand(2); //
		while (ans != 1 && ans != 2)
		{
			cout << "Don't know what to do. Please re-enter your option" << endl;
			cout << "\t1/ Let me re-enter the name" << endl;
			cout << "\t2/ Get out" << endl;
			ans = askCommand(2); //
		}
		if (ans == 1)
		{
			//cin.ignore();
			removeOneLecturer();
		}
		else if (ans == 2)
		{
			return;
		}
	}
}
void function23()
{
	cout << "\t\t\t\t\t\t\t";
	textColor(TitleFunc);
	cout << "Edit Lecturer" << endl;
	textColor(NormalT);
	do // Huy thêm do_while vào để thay thế đoạn đệ quy vì đệ quy không tốt cho sức khỏe :v
	{
		cout << "    1/ View Lecturers List" << endl;
		cout << "    2/ Update Lecturer" << endl;
		cout << "    3/ Add One New Lecturer" << endl;
		cout << "    4/ Remove One Lecturer" << endl;
		cout << "    5/ Go Out" << endl;
		cout << "\t    Choose: ";
		int option = askCommand(5);
		/*cin >> option;
		while (option > 5 || option < 1)
		{
			cout << "Please re-enter the option" << endl;
			cout << "1/ View Lecturers List" << endl;
			cout << "2/ Update Lecturer" << endl;
			cout << "3/ Add One New Lecturer" << endl;
			cout << "4/ Remove One Lecturer" << endl;
			cout << "5/ Go Out" << endl;
			cout << "Choose: ";
			cin >> option;
		}*/
		if (option == 1)
		{
			viewLecturerList();
			//function23();
		}
		else if (option == 2)
		{
			//cin.ignore(); // [Huy]: Hàm askCommand đã xử lý vụ ignore r 
			updateOneLecturer();
			//function23();
		}
		else if (option == 3)
		{
			//cin.ignore();
			addOneNewLecturer();
			//function23();
		}
		else if (option == 4)
		{
			//cin.ignore();
			removeOneLecturer();
			//function23();
		}
		else if (option == 5)
		{
			return;
		}
		cout << endl;
	} while (true);

}

/////////////////////////////////

bool isCourseExistInLecturerTXT(string class_name, string course_id)
{
	strUpr(class_name);
	strUpr(course_id);

	int n_lecturer;
	ifstream lecturerTXT("data\\lecturer.txt");
	lecturerTXT >> n_lecturer;
	lecturer* gv = new lecturer[n_lecturer];
	lecturerTXT.close();

	readLecturerTXT(gv, n_lecturer);
	for (int i = 0; i < n_lecturer; i++)
	{
		for (int j = 0; j < gv[i].n_year; j++)
		{
			for (int k = 0; k < gv[i].years[j].n_term; k++)
			{
				for (int u = 0; u < gv[i].years[j].terms[k].n_course; u++)
				{
					if (gv[i].years[j].terms[k].courses[u].class_name == class_name && gv[i].years[j].terms[k].courses[u].id == course_id)
					{	//Nếu khóa học tồn tại thì nhảy vào đây
						delete[] gv;
						gv = NULL;
						return true;
					}
				}
			}
		}
	}
	delete[] gv;
	gv = NULL;
	return false;
}
bool isCourseExistInClass_Ver2(string class_name, string course_id)
{
	strUpr(class_name);
	strUpr(course_id);

	string path;
	courseIDTXTPath(class_name, course_id, path);
	ifstream courseTXT(path);

	if (courseTXT.is_open() == true)
	{
		courseTXT.close();
		return true;
	}
	else
	{
		courseTXT.close();
		return false;
	}
}
void removeCourseFromSemesterTXT(string class_name, string course_id)
{
	strUpr(class_name);
	strUpr(course_id);
	//Xóa 1 khóa học khỏi file semester.txt
	if (isCourseExistInSemesterTXT(course_id, class_name) == false)
	{
		return;
	}
	else
	{	//Đọc thông tin khóa học
		course c;
		readCourseTXT_OnlyCourseInfo(course_id, class_name, c);

		int n_year;
		ifstream fin("data\\semester.txt");
		fin >> n_year;
		fin.close();
		academic_year* year = new academic_year[n_year];	//Note: Tý nữa nhớ xóa

		readSemesterTXT(year, n_year);		//Thông tin tất cả khóa học được lưu vào mảng year 

		int course_term = monthToSemesterInt(c.start_date.mm);

		//Xóa khóa học khỏi mảng
		for (int q = 0; q < n_year; q++)
		{
			for (int i = 0; i < year[q].n_term; i++)
			{
				for (int j = 0; j < year[q].terms[i].n_course; j++)
				{
					if (year[q].terms[i].courses[j].class_name == class_name && year[q].terms[i].courses[j].id == course_id)
					{
						year[q].terms[i].n_course--;
						for (int k = j; k < year[q].terms[i].n_course; k++)
						{
							year[q].terms[i].courses[k] = year[q].terms[i].courses[k + 1];
						}
						break;
					}
				}
			}
		}
		//Ghi đè thông tin mới
		saveSemesterTXT(year, n_year);

		delete[]year;
		year = NULL;
	}
}
void removeCourseFromLecturerTXT(string class_name, string course_id)
{
	strUpr(class_name);
	strUpr(course_id);
	//Xóa 1 khóa học khỏi file lecturer.txt
	if (isCourseExistInLecturerTXT(class_name, course_id) == false)
		return;
	else
	{	//Đọc thông tin khóa học
		course c;
		readCourseTXT_OnlyCourseInfo(course_id, class_name, c);
		int course_term = monthToSemesterInt(c.start_date.mm);
		//Đọc thông tin file lecturer.txt vào mảng
		ifstream fin;
		fin.open("data\\lecturer.txt");
		int n;
		fin >> n;
		fin.close();
		lecturer* gv = new lecturer[n];
		readLecturerTXT(gv, n);
		//Xóa khóa học khỏi mảng
		for (int i = 0; i < n; i++)
		{
			if (gv[i].name == c.lecturer)
			{
				for (int j = 0; j < gv[i].n_year; j++)
				{
					for (int k = 0; k < gv[i].years[j].n_term; k++)
					{
						for (int u = 0; u < gv[i].years[j].terms[k].n_course; u++)
						{
							//gv[i].years[j].terms[k].n_course--;
							if (c == gv[i].years[j].terms[k].courses[u])
							{
								gv[i].years[j].terms[k].n_course--;
								for (int v = u; v < gv[i].years[j].terms[k].n_course - 1; v++)
								{
									gv[i].years[j].terms[k].courses[v] = gv[i].years[j].terms[k].courses[v + 1];
								}
								break;
							}
						}
					}
				}
			}
		}
		//Ghi đè thông tin mới
		saveLecturerTXT(gv, n);

		delete[]gv;
		gv = NULL;
	}
}
void removeCourseFromStudentTXT(string class_name, string course_id)
{
	strUpr(class_name);
	strUpr(course_id);
	//Xóa 1 khóa học khỏi file [Course_id].txt và tất cả file s[MSSV].txt 
	if (isCourseExistInClass_Ver2(class_name, course_id) == false)		//Lưu ý dòng này
		return;
	else
	{	//Đọc thông tin khóa học
		course c;
		readCourseTXT_OnlyCourseInfo(course_id, class_name, c);
		int course_term = monthToSemesterInt(c.start_date.mm);
		//Đọc thông tin sinh viên
		string classPath;
		classTXTPath(class_name, classPath);
		ifstream classTXT(classPath);
		int n_student;
		classTXT >> n_student;
		classTXT.close();

		student* s = new student[n_student];
		readStudentList(s, n_student, class_name);
		//Lấy thông tin khóa học của sinh viên
		academic_year* year = NULL;
		int n_course;	//Dùng cho load và saveStudentData
		for (int h = 0; h < n_student; h++)
		{
			loadStudentData(s[h], year, n_course, s[h].class_name, s[h].id);
			for (int i = 0; i < n_course; i++)
			{
				for (int j = 0; j < year[i].n_term; j++)
				{
					for (int k = 0; k < year[i].terms[j].n_course; k++)
					{
						if (class_name == year[i].terms[j].courses[k].class_name && course_id == year[i].terms[j].courses[k].id)
						{
							year[i].terms[j].n_course--;
							for (int u = k; u < year[i].terms[j].n_course; u++)
							{
								year[i].terms[j].courses[u] = year[i].terms[j].courses[u + 1];
							}
							break;
						}
					}
				}
			}
			saveStudent(s[h], year, n_course);
			delete[]year;
			year = NULL;
		}
		//Xóa khỏi mảng

		//Ghi đè thông tin mới lên s[MSSV].txt
		/*for (int i = 0; i < n_student; i++)
		{
			saveStudent(s[i], year, n_course);
		}*/
		//Xóa file [Course_id].txt
		string coursePath;
		courseIDTXTPath(class_name, course_id, coursePath);
		remove(coursePath.c_str());

		delete[]s;
		s = NULL;
		delete[]year;
		year = NULL;

	}
}
void function17()
{
	cout << "\t\t\t\t\t\t    ";
	textColor(TitleFunc);
	cout << "Remove a course" << endl;
	textColor(NormalT);
	course c;
	if (askingCourseID(c))
	{
		readCourseTXT_OnlyCourseInfo(c.id, c.class_name, c);
		cout << "This is the course's information of which you would like to delete:" << endl;
		viewAllCourseInformation(c);
		cout << "Do you want to remove this (Yes/No/?) :";
		if (yesNoAns())
		{
			removeCourseFromSemesterTXT(c.class_name, c.id);
			removeCourseFromLecturerTXT(c.class_name, c.id);
			removeCourseFromStudentTXT(c.class_name, c.id);
			cout << "Removing course sucessfully" << endl;
			return;
		}

	}
	cout << "Stop removing course" << endl;

}

/////////////////////////////////

void saveCourseIDTXT_Ver2(course& c)
{
	int n;
	string classPath;
	classTXTPath(c.class_name, classPath);
	ifstream classTXT(classPath);
	classTXT >> n;
	classTXT.close();

	student* s = new student[n];
	readStudentList(s, n, c.class_name);

	saveCourseIDTXT(c, s, n, c.class_name);

	delete[]s;
	s = NULL;
}
bool isCourseExistInSemesterTXT(string course_id, string class_id)
{
	//Input: Mã khóa học và tên lớp. Vd: CTT008 - 18CLC6
	strUpr(course_id);	//Làm  bước này cho chắc kèo
	strUpr(class_id);

	int n = 0;
	ifstream semesterTXT("data\\semester.txt");
	semesterTXT >> n;
	semesterTXT.close();
	if (n == 0)
	{
		return false;
	}
	academic_year* year = new academic_year[n];

	readSemesterTXT(year, n);		//Thông tin tất cả khóa học được lưu vào mảng year[] 
	for (int i = 0; i < n; i++)		//Duyệt mảng
	{
		for (int j = 0; j < year[i].n_term; j++)
		{
			for (int k = 0; k < year[i].terms[j].n_course; k++)
			{
				if (year[i].terms[j].courses[k].id == course_id && year[i].terms[j].courses[k].class_name == class_id)
				{	//Nếu khóa học tồn tại thì nhảy vào đây
					delete[]year;
					year = NULL;
					return true;
				}
			}
		}
	}
	delete[]year;
	return false;		//Duyệt qua toàn bộ khóa học mà không có cái nào trùng thì tức là không tồn tại
}
void courseEditing(string course_id, string class_id, course& c)
{
	strUpr(course_id);
	strUpr(class_id);

	//Lấy thông tin course cũ
	course old_course;
	student* s = NULL;
	int n_s = 0;
	readCourseTXT_OnlyCourseInfo(course_id, class_id, old_course);
	readCourseIDTXT(course_id, c, s, n_s, class_id);
	courseDateGenerator(old_course);
	cout << "Here is the information of the old course: " << endl;
	viewAllCourseInformation(c);
	//==================================
	cout << "Do you want to:" << endl
		<< "\t1. Edit some information of the old course" << endl
		<< "\t2. Edit ALL information of the old course" << endl
		<< "\t3. ../Back" << endl;
	int choose = askCommand(3);
	switch (choose)
	{
	case 1:
	{
		cout << "Which information would you like to edit: " << endl
			<< "\t1. Course ID and class name" << endl
			<< "\t2. Course Name" << endl
			<< "\t3. Lecturer Account" << endl
			<< "\t4. Date that have this course" << endl
			<< "\t5. Room" << endl
			<< "\t6. ../Back" << endl;
		cout << "\t!If you chosing command 1 or 4, we will remove student's data in that course" << endl
			<< "\tYou can choose many command at once! ";
		int* commands = NULL;
		int n_command = askManyCommands(1, 6, commands);
		if (commands[n_command - 1] == 6)
		{
			delete[]commands;
			return;
		}
		if (!editSomeDataOfACourse(c, s, n_s, commands, n_command))
		{
			cout << "Failed to edit course's information" << endl;
			cout << "Press Any key to go back" << endl;
			_getch();
			delete[]s;
			return;
		}
		break;
	}
	case 2:
	{
		//Nhập thông tin mới
		cout << "***NEW INFORMATION***\n";
		int* commands = new int[5]{ 1, 2, 3, 4, 5 };
		int n_command = 5;
		if (!editSomeDataOfACourse(c, s, n_s, commands, n_command))
		{
			cout << "Failed to edit course's information" << endl;
			cout << "Press Any key to go back" << endl;
			_getch();
			delete[]s;
			return;
		}
		break;
	}
	case 3:
	{
		return;
	}
	default:
	{
		break;
	}
	}

	//Xóa thông tin cũ
	removeCourseFromSemesterTXT(old_course.class_name, old_course.id);
	removeCourseFromLecturerTXT(old_course.class_name, old_course.id);
	removeCourseFromStudentTXT(old_course.class_name, old_course.id);
	//Thêm thông tin mới
	saveOneNewCourseToSemesterTXT(c);
	saveOneNewCourseToLecturerTXT(c);
	saveOneNewCourseToStudentTXT(c);
	//saveCourseIDTXT_Ver2(c);
	saveCourseIDTXT(c, s, n_s, c.class_name);
}
void function16()
{
	textColor(TitleBoard);
	cout << "COURSE EDITING\n";
	textColor(NormalT);

	course c;
	if (askingCourseID(c) == false)
	{
		return;
	}
	courseEditing(c.id, c.class_name, c);

}

///////////////////////////////////////////////////

//================================================

//	!!!DANGER ZONE!!!

//	FUNCTION 13

//	These functions may not be defined in moodle.h

void updateAcademicYear();
void saveSemesterCourses_new(ofstream &fout, academic_year* &year, int temp, int a, int n)
{
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (temp == year[i].start)
		{
			year[i].start = a;
			year[i].end = a + 1;
			fout << year[i].start << " " << year[i].end << endl;
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				fout << j + 1 << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
		else
		{
			fout << year[i].start << " " << year[i].end << endl;
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				fout << j + 1 << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
	}
}
bool isSemesterExist(int start_yr)
{
	academic_year	*existed_year = NULL;
	int				n_existed = 0;
	readSemesterTXT(existed_year, n_existed);
	for (int i = 0; i < n_existed; i++)
	{
		if (existed_year[i].start == start_yr)
			return true;
	}
	return false;
	delete[]existed_year;
}
void createAcdemicYear()
{
	// đây là 1 hàm tạo năm học học kì ghi vào file semester
	do
	{
		academic_year year;
		int cur_year = getCurrentAcademicYear();
		do
		{
			textColor(NormalT);
			cout << "    Enter the academic start year: ";
			getNum(year.start);
			if (year.start >= 2006 && year.start <= cur_year + 6)
				break;
			textColor(Notice);
			cout << "    Please choose the year that >2006 and <=" << cur_year + 6 << "!!!" << endl;
			textColor(NormalT);
		} while (true);
		year.end = year.start + 1;
		textColor(WOInfo);
		cout << "    >> The academic year you would like to create is: " << year.start << "-" << year.end << "!!!" << endl;
		textColor(NormalT);
		// Kiểm Tra năm học đã tồn tại hay chưa
		if (isSemesterExist(year.start))
		{
			textColor(Notice);
			cout << "    Academic year have existed in the data!!!" << endl;
			textColor(NormalT);
			cout << "    Do you want to:" << endl
				<< "\t1. Update that academic year" << endl
				<< "\t2.../Back" << endl;
			int ans = askCommand(2);
			if (ans == 2)
				break;
			else
				updateAcademicYear();
		}
		else
		{
			cout << "Please choose semester you would like to add: " << endl
				<< "    1. Fall (September-December)" << endl
				<< "    2. Spring (January-April)" << endl
				<< "    3. Summer (May-August)" << endl;
			textColor(Notice);
			cout << "!You can choose many commands at once: ";
			int *command = NULL;

			int n_command = askManyCommands(1, 3, command);
			year.n_term = n_command;
			year.terms = new term[n_command];
			for (int j = 0; j < year.n_term; j++)
			{
				year.terms[j].n_course = 0;
				year.terms[j].no = command[j];
			}
			academic_year	*year_list = NULL;
			int				n_list = 0;
			// Đọc semester.txt để lấy dữ liệu cũ
			readSemesterTXT(year_list, n_list);
			// Gộp 2 mảng lại
			push_back(year_list, n_list, year);
			sortAscending(year_list, n_list);
			saveSemesterTXT(year_list, n_list);
			delete[]year_list;
			delete[]command;
		}
		textColor(NormalT);
		cout << "Do you want to create antother year (Yes/No/?): ";
		if (!yesNoAns())
			break;
		cout << endl;
	} while (true);

}
void readLecturer(ifstream &fin, lecturer *&lecturers, int &n)
{
	fin >> n;
	fin.ignore();
	lecturers = new lecturer[n];
	for (int i = 0; i < n; i++)
	{
		getline(fin, lecturers[i].account, '\n');
		getline(fin, lecturers[i].name, '\n');
		getline(fin, lecturers[i].password, '\n');
		readSemesterCourses(fin, lecturers[i].years, lecturers[i].n_year);
	}
}
void addSemester(academic_year *&yr, int n_yr)
{
	int selected_year = 0;
	readSemesterTXT(yr, n_yr);
	if (n_yr >= 1)
	{
		do
		{
			if (n_yr > 1)
			{
				textColor(NormalT);
				cout << "    Please choose the year you want to add semester: " << endl;
				for (int i = 0; i < n_yr; i++)
				{
					cout << "\t" << i + 1 << ". " << yr[i].start << "-" << yr[i].end;
					if (yr[i].n_term == 3)
					{
						textColor(Notice);
						cout << "\t<Full semester>";
						textColor(NormalT);
					}
					cout << endl;
				}
				selected_year = askCommand(n_yr) - 1;
				if (yr[selected_year].n_term < 3)
					break;
				textColor(Notice);
				cout << "    Please choose the year that doesn't have 3 semester" << endl;
				textColor(NormalT);
			}
			if (n_yr == 1)
			{
				if (yr[0].n_term == 3)
				{
					cout << "    The year " << yr[0].start << "-" << yr[0].start + 1 << " has 3 semester" << endl
						<< "    So it doesn't need to be added more semester" << endl;
					return;
				}
			}

		} while (true);
	}
	else
	{
		cout << "    There is no any Academic year available right now" << endl;
	}
	bool available_sem[3] = { false };
	for (int j = 0; j < yr[selected_year].n_term; j++)
	{
		available_sem[yr[selected_year].terms[j].no - 1] = true;
	}
	textColor(Notice);
	cout << "    Please choose semester you would like to add:" << endl;
	textColor(NormalT);
	for (int i = 0; i < 3; i++)
	{
		if (available_sem[i] != true)
			cout << "\t    " << i + 1 << ". Semester " << i + 1 << endl;
	}
	int created_sem;
	do
	{
		created_sem = askCommand(3);
		if (!available_sem[created_sem - 1])
			break;
		textColor(Notice);
		cout << "    !Invalid command";
		textColor(NormalT);
	} while (true);
	term t;
	t.no = created_sem;
	push_back(yr[selected_year].terms, yr[selected_year].n_term, t);
	saveSemesterTXT(yr, n_yr);
	textColor(Notice);
	cout << "    Semester " << created_sem << ": ";
	if (created_sem == 1)
		cout << "Fall";
	else if (created_sem == 2)
		cout << "Spring";
	else
		cout << "Summer";
	cout << " was created!!!" << endl;
	textColor(NormalT);
}
void removeASemesterInSemesterTXT(academic_year *&year, int &n, int start_year, int term_no)
{
	ofstream fout;
	_mkdir("\\data");
	fout.open("data\\semester.txt");
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (year[i].start != start_year)
		{
			fout << year[i].start << " " << year[i].end << endl;
			if (year[i].n_term == 0)
			{
				fout << 0 << endl;
				continue;
			}
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].n_course == 0)
				{
					fout << year[i].terms[j].no << " " << 0 << endl;
					continue;
				}
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
		else
		{
			if (year[i].n_term == 0)
			{
				continue;
			}
			else if (year[i].n_term == 1)
			{
				fout << year[i].start << " " << year[i].end << endl;
				fout << 0 << endl;
			}
			else
			{
				fout << year[i].start << " " << year[i].end << endl;
				fout << year[i].n_term - 1 << endl;
				for (int j = 0; j < year[i].n_term; j++)
				{
					if (year[i].terms[j].no != term_no)
					{
						if (year[i].terms[j].n_course == 0)
						{
							fout << year[i].terms[j].no << " " << 0 << endl;
							continue;
						}
						fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
						for (int k = 0; k < year[i].terms[j].n_course; k++)
						{
							fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
							if (k < year[i].terms[j].n_course - 1)
								fout << " ";
							else
								fout << endl;
						}
					}
				}
			}
		}
	}
	fout.close();

}
void removeAnAcademicYearInSemesterTXT(academic_year *&year, int &n, int start_year)
{
	ofstream fout;
	_mkdir("\\data");
	fout.open("data\\semester.txt");
	fout << n - 1 << endl;
	if (n - 1 == 0)
		return;
	for (int i = 0; i < n; i++)
	{
		if (year[i].start != start_year)
		{

			fout << year[i].start << " " << year[i].end << endl;
			if (year[i].n_term == 0)
			{
				fout << 0 << endl;
				continue;
			}
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].n_course == 0)
				{
					fout << year[i].terms[j].no << " " << 0 << endl;
					continue;
				}
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
	}
	fout.close();
}
void removeASemesterInStructAcademicYear(ofstream &fout, academic_year *&year, int &n, int start_year, int term_no)
{
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (year[i].start != start_year)
		{
			fout << year[i].start << " " << year[i].end << endl;
			if (year[i].n_term == 0)
			{
				fout << 0 << endl;
				continue;
			}
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].n_course == 0)
				{
					fout << year[i].terms[j].no << " " << 0 << endl;
					continue;
				}
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
		else
		{
			if (year[i].n_term == 0)
			{
				continue;
			}
			else if (year[i].n_term == 1)
			{
				fout << year[i].start << " " << year[i].end << endl;
				fout << 0 << endl;
			}
			else
			{
				fout << year[i].start << " " << year[i].end << endl;
				fout << year[i].n_term - 1 << endl;
				for (int j = 0; j < year[i].n_term; j++)
				{
					if (year[i].terms[j].no != term_no)
					{
						if (year[i].terms[j].n_course == 0)
						{
							fout << year[i].terms[j].no << " " << 0 << endl;
							continue;
						}
						fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
						for (int k = 0; k < year[i].terms[j].n_course; k++)
						{
							fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
							if (k < year[i].terms[j].n_course - 1)
								fout << " ";
							else
								fout << endl;
						}
					}
				}
			}
		}
	}
}
void removeAYearInStructAcademicYear(ofstream &fout, academic_year *&year, int &n, int start_year)
{
	fout << n - 1 << endl;
	for (int i = 0; i < n; i++)
	{
		if (year[i].start != start_year)
		{
			fout << year[i].start << " " << year[i].end << endl;
			if (year[i].n_term == 0)
			{
				fout << 0 << endl;
				continue;
			}
			fout << year[i].n_term << endl;
			for (int j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].n_course == 0)
				{
					fout << year[i].terms[j].no << " " << 0 << endl;
					continue;
				}
				fout << year[i].terms[j].no << " " << year[i].terms[j].n_course << " ";
				for (int k = 0; k < year[i].terms[j].n_course; k++)
				{
					fout << year[i].terms[j].courses[k].id << " " << year[i].terms[j].courses[k].class_name;
					if (k < year[i].terms[j].n_course - 1)
						fout << " ";
					else
						fout << endl;
				}
			}
		}
	}
}
void deleteASemesterInLecturerTXT(int start_year, int term_no)
{
	// Hàm dùng trong function13()
	// Xóa HK trong file lecturer.txt
	lecturer *lecturers = NULL;
	int n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	ofstream fout;
	fout.open("data\\lecturer.txt");
	fout << n_lecturer << endl;
	for (int i = 0; i < n_lecturer; i++)
	{
		fout << lecturers[i].account << endl;
		fout << lecturers[i].name << endl;
		fout << lecturers[i].password << endl;
		removeASemesterInStructAcademicYear(fout, lecturers[i].years, lecturers[i].n_year, start_year, term_no);
	}
	fout.close();
}
void deleteAYearInLecturerTXT(int start_year)
{
	lecturer *lecturers = NULL;
	int n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	ofstream fout;
	fout.open("data\\lecturer.txt");
	fout << n_lecturer << endl;
	for (int i = 0; i < n_lecturer; i++)
	{
		fout << lecturers[i].account << endl;
		fout << lecturers[i].name << endl;
		fout << lecturers[i].password << endl;
		int j = 0;
		for (j = 0; j < lecturers[i].n_year; j++)
		{
			if (lecturers[i].years[j].start == start_year)
				break;
		}
		if (j >= 0)
			saveSemesterCourses(fout, lecturers[i].years, lecturers[i].n_year);
		else
			removeAYearInStructAcademicYear(fout, lecturers[i].years, lecturers[i].n_year, start_year);
	}
	fout.close();
}
void deleteASemesterCourse(academic_year *&yr, int n_yr, int selected_year_index, int deleted_semester_index)
{
	// Delete các file [courseID].txt
	for (int k = 0; k < yr[selected_year_index].terms[deleted_semester_index].n_course; k++)
	{
		string path;
		course	c;
		student *s = NULL;
		int		n_s = 0;
		courseIDTXTPath(yr[selected_year_index].terms[deleted_semester_index].courses[k].class_name, yr[selected_year_index].terms[deleted_semester_index].courses[k].id, path);
		readCourseIDTXT(yr[selected_year_index].terms[deleted_semester_index].courses[k].id, c, s, n_s, yr[selected_year_index].terms[deleted_semester_index].courses[k].class_name);
		for (int l = 0; l < n_s; l++)
		{
			string path2;
			academic_year	*s_yr = NULL;
			int				n_yr = 0;
			loadStudentData(s[l], s_yr, n_yr, s[l].class_name, s[l].id);
			removeACourseInStudentIDTXT(s[l], s_yr, n_yr, c);
			delete[]s_yr;
		}
		remove(path.c_str());
		delete[]s;
	}
	deleteASemesterInLecturerTXT(yr[selected_year_index].start, yr[selected_year_index].terms[deleted_semester_index].no);
	academic_year *all_year = NULL;
	int				n_all = 0;
	readSemesterTXT(yr, n_all);
	removeASemesterInSemesterTXT(yr, n_all, yr[selected_year_index].start, yr[selected_year_index].terms[deleted_semester_index].no);
	delete[] all_year;
}
void deleteAllSemesterCourse(academic_year *&yr, int n_yr, int selected_year_index)
{
	// Delete các file [courseID].txt
	for (int i = 0; i < yr[selected_year_index].n_term; i++)
	{
		for (int k = 0; k < yr[selected_year_index].terms[i].n_course; k++)
		{
			string path;
			course	c;
			student *s = NULL;
			int		n_s = 0;
			courseIDTXTPath(yr[selected_year_index].terms[i].courses[k].class_name, yr[selected_year_index].terms[i].courses[k].id, path);
			readCourseIDTXT(yr[selected_year_index].terms[i].courses[k].id, c, s, n_s, yr[selected_year_index].terms[i].courses[k].class_name);
			for (int l = 0; l < n_s; l++)
			{
				string path2;
				academic_year	*s_yr = NULL;
				int				n_yr = 0;
				loadStudentData(s[l], s_yr, n_yr, s[l].class_name, s[l].id);
				removeACourseInStudentIDTXT(s[l], s_yr, n_yr, c);
				delete[]s_yr;
			}
			remove(path.c_str());
			delete[]s;
		}
	}
}
void deleteSemester(academic_year* &yr, int n_yr)
{
	int selected_year = 0;
	readSemesterTXT(yr, n_yr);
	if (n_yr > 1)
	{
		do
		{
			cout << "    Please choose the year you want to delete semester: " << endl;
			for (int i = 0; i < n_yr; i++)
			{
				cout << "\t" << i + 1 << ". " << yr[i].start << "-" << yr[i].end;
				textColor(WOInfo);
				if (yr[i].n_term == 0)
					cout << "\t<No semester>";
				else
					cout << "\t<" << yr[i].n_term << " semester(s)>";
				textColor(NormalT);
				cout << endl;
			}
			cout << "\t" << n_yr + 1 << ".../Back " << endl;
			int temp_variable_ = askCommand(n_yr + 1);
			if (temp_variable_ == n_yr + 1)
			{
				return;
			}
			selected_year = temp_variable_ - 1;
			if (yr[selected_year].n_term > 0)
				break;
			cout << "    Please choose the year that have at least 1 semester!" << endl;
		} while (true);
	}
	bool available_sem[3] = { false };
	if (yr[selected_year].n_term == 0)
	{
		textColor(Notice);
		cout << "    There is no semester in that year!" << endl;
		textColor(NormalT);
		return;
	}
	for (int j = 0; j < yr[selected_year].n_term; j++)
	{
		available_sem[yr[selected_year].terms[j].no - 1] = true;
	}
	textColor(NormalT);
	cout << "    Please choose semester you would like to delete:" << endl;
	for (int i = 0; i < 3; i++)
	{
		if (available_sem[i])
			cout << "\t" << i + 1 << ". Semester " << i + 1 << endl;
	}
	int deleted_sem;
	do
	{
		deleted_sem = askCommand(3);
		if (available_sem[deleted_sem - 1])
		{
			break;
		}
		textColor(Notice);
		cout << "    !Invalid command";
		textColor(NormalT);
	} while (true);
	int k = 0;
	for (k = 0; k < yr[selected_year].n_term; k++)
	{
		if (yr[selected_year].terms[k].no == deleted_sem)
			break;
	}
	if (yr[selected_year].terms[k].n_course == 0)
	{
		for (int i = k; i < yr[selected_year].n_term - 1; i++)
		{
			yr[selected_year].terms[i] = yr[selected_year].terms[i + 1];
		}
		yr[selected_year].n_term--;
		saveSemesterTXT(yr, n_yr);
	}
	else
	{
		textColor(Notice);
		cout << "    The semester you would like to delete contains courses' data!!! "
			<< "If you delete the semester, its data WILL BE LOST." << endl;
		textColor(NormalT);
		cout << "    Delete it anyway? (Yes/No/?): ";
		if (!yesNoAns())
			return;
		deleteASemesterCourse(yr, n_yr, selected_year, k);
	}
}
void updateAcdemicYearStartYear()
{
	academic_year	*year = NULL;
	int				n_yr = 0;

	int temp;
	int cur_year = getCurrentAcademicYear();
	do
	{
		textColor(NormalT);
		cout << "    Enter start year of the academic which need to be updated: ";
		getNum(temp);
		if (temp >= 2006 && temp <= cur_year + 6)
			break;
		textColor(Notice);
		cout << "    Please choose the year that >2006 and <=" << cur_year + 6 << "(Remember that it must be existed in the program's data)!" << endl;
		textColor(NormalT);
	} while (true);
	if (!isSemesterExist(temp))
	{
		textColor(Notice);
		cout << "    Academic year does not exist in the data!!!!" << endl;
		textColor(NormalT);
		cout << "    Do you want to:" << endl
			<< "\t1.Create new academic year" << endl
			<< "\t2.../Back" << endl;
		int ans = askCommand(2);
		if (ans == 2)
			return;
		else
		{
			createAcdemicYear();
			return;
		}
	}
	int start_year_new;
	do
	{
		do
		{
			textColor(NormalT);
			cout << "    Enter new start year of this academic to update: ";
			getNum(start_year_new);
			if (start_year_new >= 2006 && start_year_new <= getCurrentAcademicYear() + 6)
			{
				break;
			}
			textColor(Notice);
			cout << "    Please input the year that >= 2006 and <=" << getCurrentAcademicYear() + 6 << "!!!" << endl;
			textColor(NormalT);
		} while (true);
		if (!isSemesterExist(start_year_new))
			break;
		textColor(Notice);
		cout << "    !The year " << start_year_new << "-" << start_year_new + 1 << "have already existed in the data!!!" << endl
			<< "Please choose ANOTHER year which is not existed!!!!" << endl;
	} while (true);

	//thay đổi file semester
	readSemesterTXT(year, n_yr);

	int i_change = 0;
	bool have_course = false;
	for (int i = 0; i < n_yr; i++)
	{
		if (year[i].start == temp)
		{
			year[i].start = start_year_new;
			year[i].end = year[i].start + 1;
			i_change = i;
			int j = 0;
			for (j = 0; j < year[i].n_term; j++)
			{
				if (year[i].terms[j].n_course > 0)
				{
					have_course = true;
					break;
				}
			}
			if (j < year[i].n_term)
				break;
		}
	}
	if (have_course)
	{
		int		cur_yr = getCurrentAcademicYear();
		if (start_year_new == cur_yr)
		{
			textColor(Notice);
			cout << "    Some infomation will be changed to match the new academic year which you would like to update!!! "
				<< "\n    Example: *The course's start year which is existed*" << endl;
		}
		else if (start_year_new > cur_yr)
		{
			textColor(Notice);
			cout << "    You are chaging this start year to another one which is not started." << endl
				<< "    Remember that the program will remove some course(s)'s data in that year!!!" << endl
				<< "    Such as: students' attendace, students' grade and some function like check-in attendace or importing grade, etc." << endl
				<< "    *Those functions are unusable until the start year coming!!!" << endl;
		}
		else
		{
			textColor(Notice);
			cout << "    You are chaging this start year to another one which was started in the past.\n"
				<< "    It means that some functions will be unusable."
				<< "\n    (Such as: Check-in currently attendance of a course)!!!" << endl;
		}
		textColor(NormalT);
		cout << "    Do you want to continue anyway? ***This command might take a while!*** (Yes/No/?): ";
		if (!yesNoAns())
		{
			textColor(NormalT);
			return;
		}
	}
	//   
	saveSemesterTXT(year, n_yr);

	// Thay đổi course.txt, [student_id].txt
	course			c;
	student			*s = NULL;
	academic_year	*y_student = NULL;
	int				n_student = 0;
	int				n_s_yr = 0;
	for (int j = 0; j < year[i_change].n_term; j++)
	{
		for (int k = 0; k < year[i_change].terms[j].n_course; k++)
		{
			readCourseIDTXT(year[i_change].terms[j].courses[k].id, c, s, n_student, year[i_change].terms[j].courses[k].class_name);
			c.start_date.yyyy = changeStartYearOfACourseToMatchWithNewAcademicYear(c.start_date.mm, start_year_new);
			c.end_date.yyyy = changeStartYearOfACourseToMatchWithNewAcademicYear(c.end_date.mm, start_year_new);
			saveCourseIDTXT(c, s, n_student, year[i_change].terms[j].courses[k].class_name);
			for (int l = 0; l < n_student; l++)
			{
				loadStudentData(s[l], y_student, n_s_yr, s[l].class_name, s[l].id);
				for (int m = 0; m < n_s_yr; m++)
				{
					if (y_student[m].start == temp)
					{
						y_student[m].start = start_year_new;
						y_student[m].end = y_student[m].start + 1;
						break;
					}
				}
				saveStudent(s[l], y_student, n_s_yr);
			}
		}
	}
	lecturer		*lecturers = NULL;
	int				n_lecturer = 0;
	//thay đổi file lecturer
	ifstream filein("data\\lecturer.txt");
	readLecturer(filein, lecturers, n_lecturer);
	ofstream fo("data\\lecturer.txt");
	fo << n_lecturer << endl;
	for (int i = 0; i < n_lecturer; i++)
	{
		fo << lecturers[i].account << endl;
		fo << lecturers[i].name << endl;
		fo << lecturers[i].password << endl;
		saveSemesterCourses_new(fo, lecturers[i].years, temp, start_year_new, lecturers[i].n_year);
	}
	delete[]year;
	delete[]s;
	delete[]lecturers;
	delete[]y_student;
}
void updateSemester()
{
	do
	{
		cout << "\t1. Create new semester " << endl
			<< "\t2. Delete semester" << endl
			<< "\t3../Back" << endl;
		int ans = askCommand(3);
		if (ans == 3)
			break;
		academic_year	*yr = NULL;
		int				n_yr = 0;
		switch (ans)
		{
		case 1:
		{
			addSemester(yr, n_yr);
			break;
		}
		case 2:
		{
			deleteSemester(yr, n_yr);
			break;
		}
		default:
			break;
		}
		delete[]yr;
	} while (true);
}
void updateAcademicYear()
{
	//này là sửa file semester
	//kêu user nhập năm bắt đầu cần thay đổi
	//hỏi user có cần thay đổi số lượng học kì
	//hỏi user có cần thay đổi số lượng khóa học
	//hỏi user cần thay đổi khóa học nào

	// sửa trong file semester kéo theo file courses 
	// file courses ko có học kì
	// sửa năm và học kì thì trong file semester
	// sửa tên, năm dạy thì trong courses
	// lecturer, semester, courses, student cần sửa
	do
	{
		textColor(NormalT);
		cout << "    Do you want to:" << endl
			<< "\t1. Update academic year's start-end year" << endl
			<< "\t2. Add/Remove Semester of an academic year" << endl
			<< "\t3. ../Back" << endl;
		int command = askCommand(3);
		switch (command)
		{
		case 1:
		{
			updateAcdemicYearStartYear();
			break;
		}
		case 2:
		{
			updateSemester();
			break;
		}
		case 3:
			return;
		default:
			break;
		}

		cout << endl;
	} while (true);
}
void deleteAcademicYear()
{
	do
	{
		textColor(NormalT);
		academic_year *all_year = NULL;
		int n_all = 0;
		readSemesterTXT(all_year, n_all);
		if (n_all == 0)
		{
			textColor(Notice);
			cout << "   There is no any academic year to delete!!!" << endl;
			textColor(NormalT);
			return;
		}
		cout << "    Please choose Academic year which you would like to delete: " << endl;
		for (int i = 0; i < n_all; i++)
		{
			cout << "\t" << i + 1 << ". " << all_year[i].start << "-" << all_year[i].start + 1 << endl;
		}
		cout << "\t" << n_all + 1 << "../Back" << endl;
		int index = askCommand(n_all + 1);
		if (index == n_all + 1)
		{
			delete[]all_year;
			return;
		}
		textColor(Notice);
		deleteAllSemesterCourse(all_year, n_all, index - 1);
		cout << "    Deleting all semester of course successfully!" << endl;
		deleteAYearInLecturerTXT(all_year[index - 1].start);
		removeAnAcademicYearInSemesterTXT(all_year, n_all, all_year[index - 1].start);
		delete[]all_year;
		cout << "    Do you want to delete another year? (Yes/No/?): ";
		if (!yesNoAns())
			break;
	} while (true);
}
void viewAcademicYear()
{
	academic_year *all_yr = NULL;
	int n_yr = NULL;
	if (!readSemesterTXT(all_yr, n_yr))
	{
		textColor(Notice);
		cout << "    There is no any academic year existed in the data" << endl;
		textColor(NormalT);
		return;
	}
	do
	{
		textColor(NormalT);
		for (int i = 0; i < n_yr; i++)
		{
			cout << "\t" << i + 1 << ". " << all_yr[i].start << " - " << all_yr[i].start + 1;
			textColor(WOInfo);
			cout << "\t<" << all_yr[i].n_term << " Semester(s)>" << endl;
			textColor(NormalT);
		}
		cout << "\t" << n_yr + 1 << ".../Back" << endl;
		int command = askCommand(n_yr + 1);
		if (command == n_yr + 1)
		{
			delete[] all_yr;
			return;
		}
		for (int j = 0; j < all_yr[command - 1].n_term; j++)
		{
			textColor(NormalT);
			cout << "\t" << j + 1 << ". Semester ";
			switch (all_yr[command - 1].terms[j].no)
			{
			case 1:
				cout << "1 (Autumn)";
				break;
			case 2:
				cout << "2 (Spring)";
				break;
			case 3:
				cout << "3 (Summer)";
				break;
			default:
				break;
			}
			textColor(Notice);
			cout << "\t<" << all_yr[command - 1].terms[j].n_course << " Course(s)>" << endl;
		}
		textColor(WOInfo);
		cout << "\nPlease press 'Enter' to go back" << endl;
		textColor(NormalT);
		_getch();
	} while (true);
}
void function13()
{
	// hỏi user muốn làm gì, create, update, delete 
	// nếu create(lúc này đã create rồi) mà năm bắt đầu đã tồn tại thì hỏi là người user mún chèn cuối file hay update toàn bộ
	// nếu delete thì hỏi người dùng user mún xóa năm học (xóa toàn bộ)
	// nếu chỉ xóa học kì thì phải nhập năm học cần xóa
	do
	{
		cout << "\t\t\t";
		textColor(TitleFunc);
		cout << "Create, update, delete, view academic years (2018-2019), and semesters (Fall)" << endl;
		textColor(NormalT);
		cout << "Do you want to:" << endl
			<< "    1/ Create Academic year" << endl
			<< "    2/ Update Academic year" << endl
			<< "    3/ Delete Academic year" << endl
			<< "    4/ View Academic year" << endl
			<< "    5/ ...Back" << endl;
		int command = askCommand(5);
		switch (command)
		{
		case 1:
		{
			//tạo năm học
			createAcdemicYear();
			break;
		}
		case 2:
		{
			updateAcademicYear();
			break;
		}
		case 3:
		{
			deleteAcademicYear();
			break;
		}
		case 4:
		{
			viewAcademicYear();
			break;
		}

		case 5:
			return;
		}
		system("cls");
	} while (true);
	textColor(NormalT);
}

// ============================

// Another Danger Zone
template <class T> void	moreNSize(T* &arr, int &n, int size_to_add_more)
{
	// size_to_add_more là số phần tử muốn thêm vào mảng
	// !!!size_to_add_more >= 1
	if (arr == NULL)
	{
		arr = new T[size_to_add_more];
		n = size_to_add_more;
	}
	else
	{
		T* new_arr = new T[(n + size_to_add_more)];
		for (int i = 0; i < n; i++)
		{
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
		n += size_to_add_more;
	}
}
class CourseCSVError
{
public:
	CourseCSVError();
	~CourseCSVError();
	bool error;
	int i; // Ngưng import tại vị trí nào
	string line; // Dòng nào bị lỗiz
	bool invalid_directory; // return
	bool invalid_date_formatting; // return
	bool invalid_dow_formatting; // return
	bool invalid_hour_formatting; // return
	bool used_room; // return
	bool overlapping_lecturer_time; // not_importing
	int  n_overlapping_lecturer_time;	 // not_importing
	string *opverlapping_lecturer = NULL;
	int* index_overlapping_lecturer = NULL;
	//bool overlapping_student_time;
	bool existed_course;
	int  n_existed_course = 0;
	//int  n_overlapping_student_time = 0;
	bool invalid_course_time; // return
	bool invalid_course_year; // return
	//bool existed_course_but_new_data ;
	//int n_existed_course_but_new_data ;
};
CourseCSVError::CourseCSVError()
{
	error = false;
	i = 0;
	invalid_directory = false; // return
	invalid_date_formatting = false; // return
	invalid_dow_formatting = false; // return
	invalid_hour_formatting = false; // return
	used_room = false; // return
	overlapping_lecturer_time = false; // not_importing
	n_overlapping_lecturer_time = 0;	 // not_importing
	opverlapping_lecturer = NULL;
	int* index_overlapping_lecturer = NULL;
	//overlapping_student_time	= false;
	existed_course = false;
	n_existed_course = 0;
	//n_overlapping_student_time = 0;
	invalid_course_time = false; // return
	invalid_course_year = false; // return
	//existed_course_but_new_data = false;
	//n_existed_course_but_new_data = 0;
}
CourseCSVError::~CourseCSVError()
{
	delete[] opverlapping_lecturer;
}
//class TheRoom3
//{
//public:
//	TheRoom3();
//	~TheRoom3();
//	string room;
//	courseID *courses;
//	int n_course;
//};
//TheRoom3::TheRoom3()
//{
//	courses = NULL;
//	n_course = 0;
//}
//TheRoom3::~TheRoom3()
//{
//	delete[]courses;
//}
//bool readRoomTXT(TheRoom3 *&rooms, int &n_room)
//{
//	ifstream fin;
//	fin.open("\\data\\room.txt");
//	if (fin.fail())
//		return false;
//	fin >> n_room;
//	for (int i = 0; i < n_room; i++)
//	{
//		fin >> rooms[i].n_course;
//		fin.ignore;
//		for (int j = 0; j < rooms[i].n_course; j++)
//		{
//			getline(fin, rooms[i].courses[j].id);
//			getline(fin, rooms[i].courses[j].class_name);
//		}
//	}
//	return true;
//}
//void saveRoomTXT(TheRoom3 *&rooms, int n_room)
//{
//	_mkdir("data");
//	ofstream fout;
//	fout.open("room.txt");
//	fout << n_room << endl;
//	for (int i = 0; i < n_room; i++)
//	{
//		fout << rooms[i].room << endl;
//		for (int j = 0; j < rooms[i].n_course; j++)
//		{
//			fout << rooms[i].courses[j].id << " " << rooms[i].courses[j].class_name << endl;;
//		}
//	}
//}
bool	lecturerAcountGenerator_new(lecturer &l, const course &c, int start_yr, int term_no)
{
	// Tạo tài khoản lecturer tự động, dùng trong import semester.txt
	// Hàm này không lưu ngay tài khoản vào file lecturer.txt
	lecturer*		lecturers = NULL;
	int				n_lecturer = 0;
	readLecturerTXT(lecturers, n_lecturer);
	if (isLecturerExist(l) == 1)
	{
		delete[]lecturers;
		return false;
	}
	l.password = sha256(l.account);
	if (l.name.length() == 0)
		l.name = l.account;
	moreSize(l.years, l.n_year);
	moreSize(l.years[0].terms, l.years[0].n_term);
	l.years[0].start = start_yr;
	l.years[0].end = start_yr + 1;
	l.years[0].terms[0].no = term_no;
	moreSize(l.years[0].terms[0].courses, l.years[0].terms[0].n_course);
	l.years[0].terms[0].courses[0].id = c.id;
	l.years[0].terms[0].courses[0].class_name = c.class_name;
	delete[]lecturers;
	return true;
}
bool	hourRangeOverlap(const dayhour &d1, const dayhour &d2)
{
	// Kiểm tra khung giờ của hai biến dayhour có chồng-chéo nhau hay không
	// Giả sử hay ngày có dd mm yyyy giống nhau

	// Nếu 2 khoảng giờ bị chồng chéo
	/*	A = (StartA, EndA)
		B = (StartB, EndB)

									(----DateRange A------)	 (True if StartA >= EndB)
		(-- - Date Range B---- - )


		(----DateRange A---- - )                             (True if EndA <= StartB)
									(-- - Date Range B----)

		Overlap if: (StartA < EndB)  and  (EndA > StartB)
									*/

	hour startA = { d1.start_hh, d1.start_min },
		startB = { d2.start_hh, d2.start_min },
		endA = { d1.end_hh, d1.end_min },
		endB = { d2.end_hh, d2.end_min };
	if (startA < endB && endA > startB)
		return true;
	return false;
}
int		askAcademicYearAndSemester(int &sem)
{
	// Đọc file semester.txt, đọc các năm học
	// Hỏi người dùng nhập một trong số các học kỳ đã có
	// Trả về năm học bắt đầu mà người dùng chọn
	// Nếu không chọn -> trả về 0
	// Nếu không có năm học đã tạo -> trả về -1

	academic_year	*all_year = NULL;
	int				n_all = 0;
	if (!readSemesterTXT(all_year, n_all))
		return -1;
	if (n_all == 0)
	{
		return -1;
	}
	for (int i = 0; i < n_all; i++)
	{
		cout << "\t" << i + 1 << ". " << all_year[i].start << "-" << all_year[i].start + 1 << endl;
	}
	cout << "\t" << n_all + 1 << ". None of the above" << endl;
	int command = askCommand(n_all + 1);
	int start = all_year[command - 1].start;
	if (command != n_all + 1)
	{
		do
		{
			for (int j = 0; j < all_year[command - 1].n_term; j++)
			{
				textColor(NormalT);
				cout << "\t    " << j + 1 << ". Semester ";
				switch (all_year[command - 1].terms[j].no)
				{
				case 1:
					cout << "1 (Autumn)";
					break;
				case 2:
					cout << "2 (Spring)";
					break;
				case 3:
					cout << "3 (Summer)";
					break;
				default:
					break;
				}
				textColor(Notice);
				cout << "\t<" << all_year[command - 1].terms[j].n_course << " Course(s)>" << endl;
			}
			cout << "\t    4. None of the above" << endl;
			int index = askCommand(4);
			if (index == 4)
			{
				sem = 0;
				start = 0;
				return -1;
			}
			else if (index > all_year[command - 1].n_term)
			{
				cout << "\tInvalid command" << endl;
			}
			else
			{
				sem = all_year[command - 1].terms[index - 1].no;
				break;
			}
		} while (true);

	}
	else
	{
		return -1;
	}

	delete[]all_year;
	if (command == n_all + 1)
		return 0;
	return start;
}
bool	isOverlappingTime(dayhour *&new_course_date, int n_new_course_date, academic_year *&years, int n_yr, int start_year, int sem, string _id, string _class) //
{
	// Trả về số ngày giờ bị chồng-chéo nhau
	// Một mảng chứa tất cả ngày làm việc
	dayhour *all_day_hour = new dayhour[n_new_course_date];
	int n_day_hour = n_new_course_date;
	for (int i = 0; i < n_new_course_date; i++)
	{
		all_day_hour[i] = new_course_date[i];
	}
	for (int i = 0; i < n_yr; i++)
	{
		if (years[i].start == start_year)
		{
			for (int j = 0; j < years[i].n_term; j++)
			{
				if (years[i].terms[j].no == sem)
				{
					for (int k = 0; k < years[i].terms[j].n_course; k++)
					{
						// Không so sánh khóa học chính nó
						if (_id != "" && _class != "" &&
							years[i].terms[j].courses[k].id == _id, years[i].terms[j].courses[k].class_name == _class)
						{
							continue;
						}
						course c;
						readCourseTXT_OnlyCourseInfo(years[i].terms[j].courses[k].id,
							years[i].terms[j].courses[k].class_name, c);
						courseDateGenerator(c);
						moreNSize(all_day_hour, n_day_hour, c.n_course_date);
						// Copy các ngày vô một mảng lớn
						int index = 0;
						for (int l = n_day_hour - c.n_course_date; l < n_day_hour; l++)
						{
							all_day_hour[l] = c.course_date[index++];
						}
					}
					break;
				}
			}
			break;
		}
	}
	// Tìm các giờ học bị trùng
	int overlapping_time = 0;
	for (int i = 0; i < n_day_hour - 1; i++)
	{
		for (int j = i + 1; j < n_day_hour; j++)
		{
			if (all_day_hour[i].dd == all_day_hour[j].dd &&
				all_day_hour[i].mm == all_day_hour[j].mm &&
				all_day_hour[i].yyyy == all_day_hour[j].yyyy)
			{
				if (hourRangeOverlap(all_day_hour[i], all_day_hour[j]))
				{
					return true;
					delete[]all_day_hour;
				}
			}

		}
	}
	delete[]all_day_hour;
	return false;
}
bool	isMatchingCourseData(const course &c)
{
	// Kiểm tra data khóa học có trùng với c không
	// Nếu mà data đọc ra từ file trùng y chang (trừ điểm danh và danh sách lớp)
	// -> Trả về true

	course c_read;
	readCourseTXT_OnlyCourseInfo(c.id, c.class_name, c_read);
	if (c_read.lecturer == c.lecturer &&
		c_read.name == c.lecturer &&
		c_read.room == c.room &&
		c_read.start_date == c.start_date &&
		c_read.end_date == c.end_date)
	{
		for (int i = 0; i < 7; i++)
		{
			if (c_read.dow[i] != c.dow[i] ||
				c_read.start_hour[i] != c.start_hour[i] ||
				c_read.end_hour[i] != c.end_hour[i])
				return false;
		}
		return true;
	}
	return false;
}
void	checkingSemesterCSV(
	course *&courses, int &n_course,
	int *&existed_course,
	//int *&existed_but_new_data,
	string *&existed_room, int &n_existed_room,
	lecturer *&old_l, int &n_old_l,
	lecturer *&new_l, int &n_new_l,
	string path, int start_year, int sem, CourseCSVError &error)
{
	ifstream fin;
	fin.open(path);

	// Các giá trị hợp lệ
	hour strict_start_hour_of_first_course = { 6, 0 },
		//strict_end_hour_of_first_course = { 6, 30 },
		//strict_start_hour_of_last_course = { 20, 30 },
		strict_end_hour_of_last_course = { 21, 30 };
	int valid_year = semesterToAcademicYear(sem, start_year);

	if (fin.fail())
	{
		error.error = true;
		error.invalid_directory = true;
		error.i = -1;
		return;
	}

	string	temp;

	// lấy dòng đầu tiên ra, không đọc dòng đó
	getline(fin, temp, '\n');
	char		catch_eof_err;
	streampos	pos, get_current_line = ios::beg;
	int i = 0;
	while (!fin.eof())
	{
		lecturer		l;
		course			c;
		student*		s = NULL;
		int				n_student = 0;

		if (!fin.get(catch_eof_err))
		{
			delete[]s;
			error.i = i;
			return;
		}
		pos = fin.tellg();
		if (catch_eof_err == '\n' || catch_eof_err == ' ' ||
			catch_eof_err == '\t' || catch_eof_err == ',' || pos < 0)
			break;
		else
			fin.seekg(-1, ios::cur);

		getline(fin, temp, ',');
		getline(fin, c.id, ',');
		strUpr(c.id);
		getline(fin, c.name, ',');
		getline(fin, c.class_name, ',');
		strUpr(c.class_name);

		getline(fin, c.lecturer, ',');
		l.account = c.lecturer;

		if (!importDate(fin, c.start_date, ','))
		{
			error.error = true;
			error.invalid_date_formatting = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}

		if (!importDate(fin, c.end_date, ','))
		{
			error.error = true;
			error.invalid_date_formatting = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}
		// Kiểm tra năm có hợp lệ hay không
		if (c.start_date.yyyy != valid_year || c.end_date.yyyy != valid_year)
		{
			error.error = true;
			error.invalid_course_year = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}
		// Kiểm tra tháng có hợp lệ hay không
		if (sem == 2)
		{
			if (c.start_date.mm > 4)//|| c.end_date.mm < 4)
			{
				error.error = true;
				error.invalid_course_time = true;
				error.i = i;
				fin.seekg(get_current_line);
				getline(fin, error.line, '\n');
				delete[]s;
				return;
			}
		}
		else if (sem == 3)
		{
			if (c.start_date.mm < 5 //|| c.start_date.mm > 8 ||
				//c.end_date.mm < 5 
				|| c.end_date.mm >8)
			{
				error.error = true;
				error.invalid_course_time = true;
				error.i = i;
				fin.seekg(get_current_line);
				getline(fin, error.line, '\n');
				delete[]s;
				return;
			}
		}
		else
		{
			if (c.start_date.mm < 8) //|| c.end_date.mm < 8)
			{
				error.error = true;
				error.invalid_course_time = true;
				error.i = i;
				fin.seekg(get_current_line);
				getline(fin, error.line, '\n');
				delete[]s;
				return;
			}
		}
		getline(fin, temp, ',');

		// Kiểm tra tuần, tháng năm có đúng định dạng hay chưa
		if (!readDOWInSemesterTXT(c.dow, temp.c_str()))
		{
			error.error = true;
			error.invalid_dow_formatting = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}
		getline(fin, temp, ',');

		if (!readHourInSemesterCSV(c.dow, c.start_hour, temp.c_str()))
		{
			error.error = true;
			error.invalid_hour_formatting = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}
		getline(fin, temp, ',');
		if (!readHourInSemesterCSV(c.dow, c.end_hour, temp.c_str()))
		{
			error.error = true;
			error.invalid_hour_formatting = true;
			error.i = i;
			fin.seekg(get_current_line);
			getline(fin, error.line, '\n');
			delete[]s;
			return;
		}

		// Kiểm tra khóa học có giờ học không hợp lệ hay không
		for (int j = 0; j < 7; j++)
		{
			if (c.dow[j])
			{
				hour start_h = { c.start_hour[j].hh , c.start_hour[j].mm },
					end_h = { c.end_hour[j].hh , c.end_hour[j].mm };
				if (start_h < strict_start_hour_of_first_course ||
					//start_h > strict_start_hour_of_last_course ||
					//end_h < strict_end_hour_of_first_course ||
					end_h > strict_end_hour_of_last_course)
				{
					error.error = true;
					error.invalid_course_time = true;
					error.i = i;
					fin.seekg(get_current_line);
					getline(fin, error.line, '\n');
					delete[]s;
					return;
				}
			}
		}

		//bool matching_course = false;
		bool is_existed = false;
		//bool is_existed_but_new_data = false;

		if (isCourseInSemesterTXTExist(c))
		{
			error.error = true;
			error.existed_course = true;
			//if (!isMatchingCourseData(c))
			//{
			//	is_existed_but_new_data = true;
			//	error.existed_course_but_new_data = true;
			//	//error.n_existed_course_but_new_data++; 
			//}
			//else
			//{
			//	is_existed = true;
			//	//error.n_existed_course++;
			//}
			is_existed = true;

			//matching_course = true;
		}

		// Tạm thời chưa xử lí trường hợp trùng phòng
		getline(fin, c.room, '\n');
		strUpr(c.room);

		courseDateGenerator(c);

		if (!lecturerAcountGenerator_new(l, c, start_year, sem))
		{
			// Nếu gv đã tồn tại và data không bị trùng
			// Kiểm tra giờ làm việc của gv có trùng hay không
			if (!is_existed)
			{
				if (isOverlappingTime(c.course_date, c.n_course_date, l.years, l.n_year, start_year, sem))
				{
					error.error = true;
					error.overlapping_lecturer_time = true;
					push_back(error.index_overlapping_lecturer, error.n_overlapping_lecturer_time, i);
				}
			}
			push_back(old_l, n_old_l, l);
		}
		else
		{
			int j = 0;
			for (j; j < n_new_l; j++)
			{
				if (new_l[j].account == l.account)
				{
					addCourseToStructAcademicYear(c, new_l[j].years, new_l[j].n_year, start_year, start_year + 1, sem);
					break;
				}
			}
			if (j >= n_new_l)
				push_back(new_l, n_new_l, l);
		}
		push_back(courses, n_course, c);
		if (is_existed)
		{
			textColor(7);
			push_back(existed_course, error.n_existed_course, i);
		}
		cout << "\t\t    " << i + 1 << "\t" << setw(8) << left << c.id << "\t" << setw(52) << left << c.name << "\t" << c.class_name << endl;
		textColor(NormalT);
		//else if (is_existed_but_new_data)
		//{
		//	push_back(existed_but_new_data, error.n_existed_course_but_new_data, i);
		//}
		i++;
		l.name = "";
		delete[]s;
		get_current_line = fin.tellg();
	}
	cout << endl;
	error.i = i;
	fin.close();
}
void	function14()
{
	// 14. Import semester.txt
	cout << "\t\t\t\t\t     ";
	textColor(TitleFunc);
	cout << "Import Courses from CSV file" << endl;
	do
	{
		textColor(NormalT);
		cout << "   Please choose to do something with 2 command: " << endl
			<< "\t1. Import CSV file if the CSV file is the same directory as the program file" << endl
			<< "\t2. Input the directory to the CSV file" << endl;
		textColor(Notice);
		cout << "   !The CSV file MUST be in this Format: No,Course ID,Course Name,Class,"
			<< "Lecturer Account, Start Date, End Date, Day of Week, Start Time, End Time, Room" << endl
			<< "\t3. ../Back" << endl;
		textColor(NormalT);
		int		confirm = askCommand(3);
		if (confirm == 3)
		{
			return;
		}
		string	path;
		int		sem = 0;
		int		start_yr = askAcademicYearAndSemester(sem);
		if (start_yr <= 0) // Nếu không có năm học hoặc người dùng không muốn chọn các năm học
		{
			cout << "\t\t    Please go to Course Menu to add new Academic Year" << endl;
			return;
		}
		textColor(NormalT);
		if (confirm == 1)
		{
			cout << "   Input the name of the CSV file";
			textColor(OInfo);
			cout << " (eg: Semester2_6.csv) : ";
		}
		else
		{
			cout << "   Input the directory to the CSV file ";
			textColor(OInfo);
			cout << "(eg: D:\\data\\Semester2_6.csv): ";
		}
		textColor(Input__);
		getline(cin, path, '\n');
		textColor(NormalT);

		course *courses = NULL;	int n_course = 0;
		int *existed_course = NULL;
		//int *existed_but_new_data = NULL;
		string *existed_room = NULL; int n_existed_room = 0;
		lecturer *new_l = NULL; int n_new_l = 0;
		lecturer *old_l = NULL; int n_old_l = 0;

		cout << "\t\t    Please wait while we check the file " << endl;
		CourseCSVError error;
		checkingSemesterCSV(courses, n_course,
			existed_course, //existed_but_new_data,
			existed_room, n_existed_room,
			old_l, n_old_l, new_l, n_new_l,
			path, start_yr, sem, error); // chuwa check room

		if (error.error)
		{
			cout << endl;
			if (error.i <= n_course && n_course > 0)
			{
				cout << "\t\t    Error when importing " << error.i + 1 << "(th) course" << endl;
			}
			if (error.line.length() > 0)
			{
				cout << "\t\t    This line might cause the error:" << endl;
				cout << error.line << endl;
			}
			// Thông báo lỗi
			if (error.invalid_directory)
			{
				cout << "\t\t    Invalid directory" << endl;
			}
			if (error.invalid_date_formatting)
			{
				cout << "\t\t    Invalid date formatting" << endl;
			}
			if (error.invalid_course_time)
			{
				cout << "\t\t    Invalid course time" << endl;
			}
			if (error.invalid_course_year)
			{
				cout << "\t\t    Invalid course year" << endl;
			}
			if (error.invalid_dow_formatting)
			{
				cout << "\t\t    Invalid date formatting" << endl;
			}
			if (error.overlapping_lecturer_time)
			{
				cout << "\t\t    We have found " << error.n_overlapping_lecturer_time << " course(s) that their time will overlap lecturer's schedule" << endl;
				for (int i = 0; i < error.n_overlapping_lecturer_time; i++)
				{
					cout << "\t\t    " << i + 1 << ". "
						<< setw(8) << left << courses[error.index_overlapping_lecturer[i]].id << "\t"
						<< setw(8) << left << courses[error.index_overlapping_lecturer[i]].lecturer << "\t"
						<< courses[error.index_overlapping_lecturer[i]].class_name << endl;
				}
				cout << "\t\t    These course(s) will not be imported" << endl;
			}
			if (!error.existed_course)
				break; // Break vòng lặp
		}

		if (error.n_existed_course == n_course)
		{
			cout << "\t\t    ALL The information of the CSV file has already existed in the program's data" << endl
				<< "\t\t    So the file will not be imported" << endl;
			break;
		}

		if (!error.existed_course)// && !error.existed_course_but_new_data)
		{
			cout << "\t\t    Importing: 0/" << n_course;
			int b = 0; // Giao diện - đừng quan tâm
			student *s = NULL;
			int n_student = 0;
			int temp_old = 0;
			for (int i = 0; i < n_course; i++)
			{
				importStudentToCourse(courses[i], s, n_student);
				saveCourseIDTXT(courses[i], s, n_student, courses[i].class_name);				// course.txt
				saveAllStudentCourse(s, n_student, courses[i], start_yr, start_yr + 1, sem);	// [student].txt
				if (temp_old < n_old_l && old_l[temp_old].account == courses[i].lecturer)
				{
					addCourseToLecturerTXT(old_l[temp_old], courses[i], start_yr, start_yr + 1, sem);
					temp_old++;
				}
				//if (!lecturerAcountGenerator(l, c, start_yr, end_yr, term_no))
				//	addCourseToLecturerTXT(l, c, start_yr, end_yr, term_no);					// lecturer.txt
				addCourseToSemesterTXT(courses[i], start_yr, start_yr + 1, sem);					// Semester.txt
				delete[]s;
				s = NULL;
				if (n_course < 9)
					b += 1;
				else
					b += 2;
				if (i < 9)
					b += 1;
				else
					b += 2;
				for (int j = 0; j <= b; j++)
				{
					cout << "\b";
				}
				cout << i + 1 << "/" << n_course;
				b = 0;
			}
			cout << endl;
			cout << "\t\t    Saving new lecturers: " << endl;
			lecturer *lecturers = NULL;
			int n_lecturers = 0;
			readLecturerTXT(lecturers, n_lecturers);
			moreNSize(lecturers, n_lecturers, n_new_l);
			int index_n_new_l = 0;
			for (int i = n_lecturers - n_new_l; i < n_lecturers; i++)
			{
				lecturers[i] = new_l[index_n_new_l++];
				cout << "\t\t    " << i + 1 << "\t" << lecturers[i].account << endl;
			}
			cout << endl;
			saveLecturerTXT(lecturers, n_lecturers);
			delete[]lecturers;
		}
		else
		{
			// Nếu data bị trùng
			cout << "\t\t    Warning: Data overlapping" << endl;
			if (error.n_existed_course > 0)
			{
				cout << "\t\t    We have found " << error.n_existed_course << " course(s) that their data have already been existed" << endl
					<< "\t\t    Those course(s) will not be imported" << endl
					<< "\t\t    Please delete existed course(s)' data in the program if you would like to import them" << endl;
			}
			cout << "\t\t    Importing: 0/" << n_course;
			int b = 0; // Giao diện - đừng quan tâm

			//bool is_importing_existed_course_but_new_data = false;
			//if (error.n_existed_course_but_new_data > 0)
			//{
			//	// Nếu thông tin khóa học tồn tại trong data nhưng lại import khóa học cùng tên
			//	// nhưng data khác trừ (danh sách học sinh, điểm và điểm danh)
			//	cout << "error.n_existed_course_but_new_data: " << error.n_existed_course_but_new_data << endl;
			//	cout << "Yes/No: ";
			//	if (yesNoAns())
			//	{
			//		is_importing_existed_course_but_new_data = true;
			//	}
			//}
			//if (is_importing_existed_course_but_new_data)
			//{

			//}

			student *s = NULL;
			int n_student = 0;
			int temp_old = 0, temp_new = 0;
			int index_existed = 0, index_overlapping = 0;
			lecturer *lecturers = NULL;
			int n_lecturers = 0;
			lecturer *lecturers_new = NULL;
			int n_lecturers_new = 0;
			for (int i = 0; i < n_course; i++)
			{
				if (index_existed < error.n_existed_course && i == existed_course[index_existed])
				{
					if (temp_old < n_old_l && old_l[temp_old].account == courses[i].lecturer)
					{
						temp_old++;
					}
					index_existed++;
					continue;
				}
				if (error.n_overlapping_lecturer_time > 0)
				{
					if (i == error.index_overlapping_lecturer[index_overlapping])
					{
						index_overlapping++;
						continue;
					}
				}
				importStudentToCourse(courses[i], s, n_student);
				saveCourseIDTXT(courses[i], s, n_student, courses[i].class_name);				// course.txt
				saveAllStudentCourse(s, n_student, courses[i], start_yr, start_yr + 1, sem);	// [student].txt
				if (temp_old < n_old_l && old_l[temp_old].account == courses[i].lecturer)
				{
					addCourseToLecturerTXT(old_l[temp_old], courses[i], start_yr, start_yr + 1, sem);
					temp_old++;

				}
				else if (temp_new < n_new_l && new_l[temp_new].account == courses[i].lecturer)
				{
					push_back(lecturers_new, n_lecturers_new, new_l[temp_new++]);
				}
				//if (!lecturerAcountGenerator(l, c, start_yr, end_yr, term_no))
				//	addCourseToLecturerTXT(l, c, start_yr, end_yr, term_no);					// lecturer.txt
				addCourseToSemesterTXT(courses[i], start_yr, start_yr + 1, sem);					// Semester.txt
				delete[]s;
				s = NULL;
				if (n_course < 9)
					b += 1;
				else
					b += 2;
				if (i < 9)
					b += 1;
				else
					b += 2;
				for (int j = 0; j <= b; j++)
				{
					cout << "\b";
				}
				cout << i + 1 << "/" << n_course;
				b = 0;

			}
			cout << endl;
			if (n_lecturers_new > 0)
			{
				cout << "\t\t    Importing new lecturers:" << endl;
				readLecturerTXT(lecturers, n_lecturers);
				moreNSize(lecturers, n_lecturers, n_lecturers_new);
				int index_lecturers_new = 0;
				for (int i = n_lecturers - n_lecturers_new; i < n_lecturers; i++)
				{
					lecturers[i] = new_l[index_lecturers_new++];
					cout << "\t\t    " << lecturers[i].account << endl;
				}
				saveLecturerTXT(lecturers, n_lecturers);
			}
			delete[]lecturers_new;
			delete[]lecturers;
		}
		cout << endl;
		string		sTitle = "Showing file ";
		sTitle += path;
		sTitle += " from ";
		sTitle += to_string(start_yr);
		sTitle += " to ";
		sTitle += to_string(start_yr + 1);
		cout << "\t";
		textColor(SpTitleFunc);
		cout << "\t\t\t   " << setw(76) << left << sTitle << endl;
		int index_existed = 0, index_overlapping = 0;
		for (int i = 0; i < n_course; i++)
		{
			textColor(NormalT);
			cout << "\t";
			textColor(InBoard);
			if (index_existed < error.n_existed_course && courses[existed_course[index_existed]] == courses[i])
			{
				index_existed++;
				textColor(8);
			}
			if (error.n_overlapping_lecturer_time > 0)
			{
				if (i == error.index_overlapping_lecturer[index_overlapping])
				{
					index_overlapping++;
					textColor(8);
				}
			}
			cout << setw(6) << left << i + 1
				<< setw(10) << left << courses[i].id
				<< setw(45 + 7 + 5) << left << courses[i].name
				<< setw(10) << left << courses[i].class_name
				<< setw(15) << left << courses[i].lecturer
				<< "[...]" << endl;
		}
		cout << endl;
		textColor(Notice);
		cout << "   Import student information from .CSV file successfully!\n" << endl;
	} while (true);
}