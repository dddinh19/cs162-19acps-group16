#include "function.h"
void student_data(student*& p, int& n){
	std::ifstream fi("student.txt");
	if (!fi.is_open()) std::cout << " Can not open student data file " << std::endl;
	else {
		fi >> n;
		char tempt[50];
		p = new student[n];
		for (int i = 0; i < n; ++i) {
			fi >> tempt;
			p[i].id = new char[strlen(tempt) + 1];
			strcpy_s(p[i].id, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].pass = new char[strlen(tempt) + 1];
			strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
			fi.getline(tempt, 50);
			fi.getline(tempt, 50);
			p[i].name = new char[strlen(tempt) + 1];
			strcpy_s(p[i].name, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].classname = new char[strlen(tempt) + 1];
			strcpy_s(p[i].classname, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].status = new char[strlen(tempt) + 1];
			strcpy_s(p[i].status, strlen(tempt) + 1, tempt);
		}
		fi.close();
	}
}
void staff_data(staff*& p, int& n) {
	std::ifstream fi("staff.txt");
	if (!fi.is_open()) std::cout << " Can not open staff data file " << std::endl;
	else {
		char tempt[50];
		fi >> n;
		p = new staff[n];
		for (int i = 0; i < n; ++i) {
			fi >> tempt;
			p[i].username = new char[strlen(tempt) + 1];
			strcpy_s(p[i].username, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].pass = new char[strlen(tempt) + 1];
			strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
			fi.getline(tempt, 50);
			fi.getline(tempt, 50);
			p[i].name = new char[strlen(tempt) + 1];
			strcpy_s(p[i].name, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].sex = new char[strlen(tempt) + 1];
			strcpy_s(p[i].sex, strlen(tempt) + 1, tempt);
		}
		fi.close();
	}
}
void lecturer_data(lecturer*& p, int& n) {
	std::ifstream fi("lecturer.txt");
	if (!fi.is_open()) std::cout << " Can not open lecturer data file " << std::endl;
	else {
		char tempt[50];
		fi >> n;
		p = new lecturer[n];
		for (int i = 0; i < n; ++i) {
			fi >> tempt;
			p[i].username = new char[strlen(tempt) + 1];;
			strcpy_s(p[i].username, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].pass = new char[strlen(tempt) + 1];
			strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
			fi.getline(tempt, 50);
			fi.getline(tempt, 50);
			p[i].name = new char[strlen(tempt) + 1];
			strcpy_s(p[i].name, strlen(tempt) + 1, tempt);
			fi.getline(tempt, 50);
			p[i].degree = new char[strlen(tempt) + 1];
			strcpy_s(p[i].degree, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].sex = new char[strlen(tempt) + 1];
			strcpy_s(p[i].sex, strlen(tempt) + 1, tempt);
		}
		fi.close();
	}
}
void delete_student_data(student*& p, int n) {
	for (int i = 0; i < n; ++i) {
		delete[]p[i].id;
		delete[]p[i].pass;
		delete[]p[i].name;
		delete[]p[i].classname;
		delete[]p[i].status;
	}
	delete[]p;
}
void delete_staff_data(staff*& p, int n) {
	for (int i = 0; i < n; ++i) {
		delete[]p[i].username;
		delete[]p[i].pass;
		delete[]p[i].name;
		delete[]p[i].sex;
	}
	delete[]p;
}
void delete_lecturer_data(lecturer*& p, int n) {
	for (int i = 0; i < n; ++i) {
		delete[]p[i].username;
		delete[]p[i].pass;
		delete[]p[i].name;
		delete[]p[i].degree;
		delete[]p[i].sex;
	}
	delete[]p;
}
bool login(char username[], char pass[], student* p_student, staff* p_staff, lecturer* p_lecturer, int n_student, int n_staff, int n_lecturer, int& type, int& user) {
	for (int i = 0; i < n_student; ++i) {
		if (strcmp(p_student[i].id, username) == 0 && strcmp(p_student[i].pass, pass) == 0 && strcmp(p_student[i].status, "1") == 0) {
			user = i;
			type = 1;
			return true;
		}
	}
	for (int i = 0; i < n_staff; ++i) {
		if (strcmp(p_staff[i].username, username) == 0 && strcmp(p_staff[i].pass, pass) == 0) {
			user = i;
			type = 2;
			return true;
		}
	}
	for (int i = 0; i < n_lecturer; ++i) {
		if (strcmp(p_lecturer[i].username, username) == 0 && strcmp(p_lecturer[i].pass, pass) == 0) {
			user = i;
			type = 3;
			return true;
		}
	}
}
int staff_menu() {
	int choice;
	std::cout << "Menu for staff:" << std::endl;
	std::cout << "1.Class" << std::endl;
	std::cout << "2.Course" << std::endl;
	std::cout << "3.Score board" << std::endl;
	std::cout << "4.Attendance list" << std::endl;
	std::cout << "5.View profile info:" << std::endl;
	std::cout << "6.Change password" << std::endl;
	std::cout << "7.Log out" << std::endl;
	std::cout << "Please choose a section(1-7): " << std::endl;
	std::cin >> choice;
	return choice;
}
int staff_class() {
	int choice;
	std::cout << "Academic staff- class menu: " << std::endl;
	std::cout << "1. Import students of a class such as 18CLC6 from a csv file. " << std::endl;
	std::cout << "2.Manually add a new student to a class. " << std::endl;
	std::cout << "3.Edit an existing student." << std::endl;
	std::cout << "4.Remove a student." << std::endl;
	std::cout << "5.Change students from class A to class B" << std::endl;
	std::cout << "6.View list of classes." << std::endl;
	std::cout << "7.View list of students in a class." << std::endl;
	std::cout << "Please choose a task(1-7): " << std::endl;
	std::cin >> choice;
	return choice;
}
int staff_course() {
	int choice;
	std::cout << "Academic staff- course menu: " << std::endl;
	std::cout << "1.Create / update / delete / view academic years (2018-2019), and semesters (Fall)." << std::endl;
	std::cout << "2.From a semester, import courses such as CTT008, CTT010 from a csv file." << std::endl;
	std::cout << "3.Manually add a new course." << std::endl;
	std::cout << "4.Edit an existing course." << std::endl;
	std::cout << "5.Remove a course." << std::endl;
	std::cout << "6.Remove a specific student from a course." << std::endl;
	std::cout << "7.Add a specific student to a course." << std::endl;
	std::cout << "8.View list of courses in the current semester." << std::endl;
	std::cout << "9.View list of students of a course." << std::endl;
	std::cout << "10.View attendance list of a course." << std::endl;
	std::cout << "11.Create / update / delete / view all lecturers." << std::endl;
	std::cout << "Please choose a task(1-11): " << std::endl;
	std::cin >> choice;
	return choice;
}
int staff_scoreboard() {
	int choice;
	std::cout << "Academic staff- scoreboard menu: " << std::endl;
	std::cout << "1.Search and view the scoreboard of a course." << std::endl;
	std::cout << "2.Export a scoreboard to a csv file." << std::endl;
	std::cout << "Please choose a task(1-2): " << std::endl;
	std::cin >> choice;
	return choice;
}
int staff_attendance() {
	int choice;
	std::cout << "Academic staff- attendance list menu: " << std::endl;
	std::cout << "1.Search and view attendance list of a course." << std::endl;
	std::cout << "2.Export a attendance list to a csv file." << std::endl;
	std::cout << "Please choose a task(1-2): " << std::endl;
	std::cin >> choice;
	return choice;
}
int lecturer_menu() {
	int choice;
	std::cout << "Menu for lecturer:" << std::endl;
	std::cout << "1.View list of courses in the current semester." << std::endl;
	std::cout << "2.View list of students of a course." << std::endl;
	std::cout << "3.View attendance list of a course." << std::endl;
	std::cout << "4.Edit an attendance." << std::endl;
	std::cout << "5.Import scoreboard of a course (midterm, final, lab, bonus) from a csv file." << std::endl;
	std::cout << "6.Edit grade of a student" << std::endl;
	std::cout << "7.View a scoreboard" << std::endl;
	std::cout << "8.View profile info:" << std::endl;
	std::cout << "9.Change password" << std::endl;
	std::cout << "10.Log out" << std::endl;
	std::cout << "Please choose a task (1-10): " << std::endl;
	std::cin >> choice;
	return choice;
}
int student_menu() {
	int choice;
	std::cout << "Menu for student:" << std::endl;
	std::cout << "1.Check-in (1 check-in/week) in 11 weeks" << std::endl;
	std::cout << "2.View check-in result." << std::endl;
	std::cout << "3.View schedules." << std::endl;
	std::cout << "4.View his/her scores of a course." << std::endl;
	std::cout << "5.View profile info:" << std::endl;
	std::cout << "6.Change password" << std::endl;
	std::cout << "7.Log out" << std::endl;
	std::cout << "Please choose a task (1-7): " << std::endl;
	std::cin >> choice;
	return choice;
}
void class_data(char filename[], student*& p, int& n) {
	std::ifstream fi(filename);
	fi >> n;
	p = new student[n];
	char tempt[50];
	if (!fi.is_open()) std::cout << " Can not open " << filename << " file " << std::endl;
	else {
		for (int i = 0; i < n; ++i) {
			fi >> tempt;
			p[i].id = new char[strlen(tempt) + 1];
			strcpy_s(p[i].id, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].pass = new char[strlen(tempt) + 1];
			strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
			fi.getline(tempt, 50);
			fi.getline(tempt, 50);
			p[i].name = new char[strlen(tempt) + 1];
			strcpy_s(p[i].name, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].date.year = new char[strlen(tempt) + 1];
			strcpy_s(p[i].date.year, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].date.month = new char[strlen(tempt) + 1];
			strcpy_s(p[i].date.month, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].date.day = new char[strlen(tempt) + 1];
			strcpy_s(p[i].date.day, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].classname = new char[strlen(tempt) + 1];
			strcpy_s(p[i].classname, strlen(tempt) + 1, tempt);
			fi >> tempt;
			p[i].status = new char[strlen(tempt) + 1];
			strcpy_s(p[i].status, strlen(tempt) + 1, tempt);
		}
		fi.close();
	}
}
void delete_class_data(student*& p, int n) {
	for (int i = 0; i < n; ++i) {
		delete[]p[i].id;
		delete[]p[i].pass;
		delete[]p[i].name;
		delete[]p[i].date.year;
		delete[]p[i].date.month;
		delete[]p[i].date.day;
		delete[]p[i].classname;
		delete[]p[i].status;
	}
	delete[]p;
}
void view_student_info(student* p, int i) {
	char filename[20];
	strcpy_s(filename, strlen(p[i].classname) + 1, p[i].classname);
	strcat_s(filename, 20, ".txt");
	student* p_class = nullptr;
	int n_student_class = 0;
	class_data(filename, p_class, n_student_class);
	for (int j = 0; j < n_student_class; ++j) {
		if (strcmp(p_class[j].id, p[i].id) == 0) {
			std::cout << "Student ID: " << p_class[j].id << std::endl;
			std::cout << "Full name: " << p_class[j].name << std::endl;
			std::cout << "Date of birth(year, month, day): " << p_class[j].date.year << " " << p_class[j].date.month << " " << p_class[j].date.day << std::endl;
			std::cout << "Class: " << p_class[j].classname << std::endl;
			break;
		}
	}
	delete_class_data(p_class, n_student_class);
}
void view_staff_info(staff* p, int i) {
	std::cout << " Full name: " << p[i].name << std::endl;
	if (strcmp(p[i].sex, "1") == 0) std::cout << " Sex: Female" << std::endl;
	else std::cout << " Sex: Male" << std::endl;
}
void view_lecturer_info(lecturer* p, int i) {
	std::cout << " Full name: " << p[i].name << std::endl;
	std::cout << " Degree: " << p[i].degree << std::endl;
	if (strcmp(p[i].sex, "1") == 1)std::cout << " Sex: Female " << std::endl;
	else std::cout << " Sex: Male " << std::endl;
}
void write_student_data(student* p, int n) {
	std::ofstream fo("student.txt");
	if (!fo.is_open()) std::cout << " Can not open student data file " << std::endl;
	else {
		fo << n << std::endl;
		for (int i = 0; i < n; ++i) {
			fo << p[i].id << std::endl;
			fo << p[i].pass << std::endl;
			fo << p[i].name << std::endl;
			fo << p[i].classname << std::endl;
			fo << p[i].status << std::endl;
		}
		fo.close();
	}
}
void change_student_password(student*& p, int n, int i) {
	char tempt[20];
	do {
		std::cout << " Enter your current password " << std::endl;
		std::cin >> tempt;
	} while (strcmp(tempt, p[i].pass) != 0);
	std::cout << " Enter new password " << std::endl;
	std::cin >> tempt;
	char tempt_2[20];
	do {
		std::cout << " Enter new password again " << std::endl;
		std::cin >> tempt_2;
	} while (strcmp(tempt_2, tempt) != 0);
	p[i].pass = new char[strlen(tempt) + 1];
	strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
	write_student_data(p, n);
}
void write_staff_data(staff* p, int n) {
	std::ofstream fo("staff.txt");
	if (!fo.is_open()) std::cout << " Can not open staff data file " << std::endl;
	else {
		fo << n << std::endl;
		for (int i = 0; i < n; ++i) {
			fo << p[i].username << std::endl;
			fo << p[i].pass << std::endl;
			fo << p[i].name << std::endl;
			fo << p[i].sex << std::endl;
		}
		fo.close();
	}
}
void change_staff_password(staff*& p, int n, int i) {
	char tempt[20];
	do {
		std::cout << " Enter your current password " << std::endl;
		std::cin >> tempt;
	} while (strcmp(tempt, p[i].pass) != 0);
	char tempt_2[20];
	std::cout << " Enter new password " << std::endl;
	std::cin >> tempt;
	do {
		std::cout << " Enter new password again " << std::endl;
		std::cin >> tempt_2;
	} while (strcmp(tempt, tempt_2) != 0);
	p[i].pass = new char[strlen(tempt) + 1];
	strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
	write_staff_data(p, n);
}
void write_lecturer_data(lecturer* p, int n) {
	std::ofstream fo("lecturer.txt");
	if (!fo.is_open()) std::cout << " Can not open lecturer data file " << std::endl;
	else {
		fo << n << std::endl;
		for (int i = 0; i < n; ++i) {
			fo << p[i].username << std::endl;
			fo << p[i].pass << std::endl;
			fo << p[i].name << std::endl;
			fo << p[i].degree << std::endl;
			fo << p[i].sex << std::endl;
		}
		fo.close();
	}
}
void change_lecturer_password(lecturer*& p, int n, int i) {
	char tempt[20];
	do {
		std::cout << " Enter your current password " << std::endl;
		std::cin >> tempt;
	} while (strcmp(tempt, p[i].pass) != 0);
	char tempt_2[20];
	std::cout << " Enter new password " << std::endl;
	std::cin >> tempt;
	do {
		std::cout << " Enter new password again " << std::endl;
		std::cin >> tempt_2;
	} while (strcmp(tempt_2, tempt) != 0);
	p[i].pass = new char[strlen(tempt) + 1];
	strcpy_s(p[i].pass, strlen(tempt) + 1, tempt);
	write_lecturer_data(p, n);
}
void create_new_student_data(student* p_student, int& n_student, student* a, student*& p_student_2) {
	++n_student;
	p_student_2 = new student[n_student];
	for (int i = 0; i < n_student; ++i) {
		if (i == n_student - 1) {
			char tempt[20];
			p_student_2[n_student - 1].classname = a->classname;
			p_student_2[n_student - 1].id = a->id;
			std::cout << " Enter full name " << std::endl;
			std::cin.getline(tempt, 20);
			std::cin.getline(tempt, 20);
			p_student_2[n_student - 1].name = new char[strlen(tempt) + 1];
			strcpy_s(p_student_2[n_student - 1].name, strlen(tempt) + 1, tempt);
			p_student_2[n_student - 1].status = new char[2];
			strcpy_s(p_student_2[n_student - 1].status, 2, "1");
			std::cout << " Enter date of birth (year, month, day) " << std::endl;
			std::cin >> tempt;
			p_student_2[n_student - 1].date.year = new char[strlen(tempt) + 1];
			strcpy_s(p_student_2[n_student - 1].date.year, strlen(tempt) + 1, tempt);
			std::cin >> tempt;
			p_student_2[n_student - 1].date.month = new char[strlen(tempt) + 1];
			strcpy_s(p_student_2[n_student - 1].date.month, strlen(tempt) + 1, tempt);
			std::cin >> tempt;
			p_student_2[n_student - 1].date.day = new char[strlen(tempt) + 1];
			strcpy_s(p_student_2[n_student - 1].date.day, strlen(tempt) + 1, tempt);
			create_password(p_student_2[n_student - 1].date.year, p_student_2[n_student - 1].date.month, p_student_2[n_student - 1].date.day, p_student_2[n_student - 1].pass);
		}
		else {
			p_student_2[i].id = p_student[i].id;
			p_student_2[i].pass = p_student[i].pass;
			p_student_2[i].name = p_student[i].name;
			p_student_2[i].date.year = p_student[i].date.year;
			p_student_2[i].date.month = p_student[i].date.month;
			p_student_2[i].date.day = p_student[i].date.day;
			p_student_2[i].classname = p_student[i].classname;
			p_student_2[i].status = p_student[i].status;
		}
	}
}
void write_class_data(char filename[], student* p, int n) {
	std::ofstream fo(filename);
	if (!fo.is_open()) std::cout << " Can not open class data file " << std::endl;
	else {
		fo << n << std::endl;
		for (int i = 0; i < n; ++i) {
			fo << p[i].id << std::endl;
			fo << p[i].pass << std::endl;
			fo << p[i].name << std::endl;
			fo << p[i].date.year << " " << p[i].date.month << " " << p[i].date.day << std::endl;
			fo << p[i].classname << std::endl;
			fo << p[i].status << std::endl;
		}
		fo.close();
	}
}
void create_password(char* year, char* month, char* day, char*& pass) {
	pass = new char[strlen(year) + strlen(month) + strlen(day) + 1];
	int i;
	for (i = 0; i < strlen(year) + strlen(month) + strlen(day); ++i) {
		if (i < strlen(year)) {
			pass[i] = year[i];
		}
		else if ((i + 1 - strlen(year)) <= strlen(month)) {
			pass[i] = month[i - strlen(year)];
		}
		else {
			pass[i] = day[i - strlen(year) - strlen(month)];
		}
	}
	pass[i] = '\0';
}
void add_a_student(student*& p, int& n) {
	student* a = new student;
	char tempt[20];
	std::cout << " Enter student class " << std::endl;
	std::cin >> tempt;
	a->classname = new char[strlen(tempt) + 1];
	strcpy_s(a->classname, strlen(tempt) + 1, tempt);
	std::cout << " Enter student id " << std::endl;
	std::cin >> tempt;
	a->id = new char[strlen(tempt) + 1];
	strcpy_s(a->id, strlen(tempt) + 1, tempt);
	char filename[20];
	strcpy_s(filename, strlen(a->classname) + 1, a->classname);
	strcat_s(filename, 20, ".txt");
	student* p_class = nullptr;
	int n_student = 0;
	class_data(filename, p_class, n_student);
	for (int i = 0; i < n_student; ++i) {
		if (strcmp(p_class[i].id, a->id) == 0) {
			std::cout << " Fail add a student " << std::endl;
			delete_class_data(p_class, n_student);
			delete[]a->classname;
			delete[]a->id;
			delete a;
			return;
		}
	}
	student* p_student_2 = nullptr;
	create_new_student_data(p_class, n_student, a, p_student_2);
	std::cout << " Sucessfully add a new student " << std::endl;
	write_class_data(filename, p_student_2, n_student);
	delete_student_data(p, n);
	++n;
	write_student_data(p_student_2, n);
	student_data(p, n);
	delete_class_data(p_class, n_student - 1);
	delete[]a->classname;
	delete[]a->id;
	delete a;
	delete[]p_student_2[n_student - 1].name;
	delete[]p_student_2[n_student - 1].status;
	delete[]p_student_2[n_student - 1].date.year;
	delete[]p_student_2[n_student - 1].date.month;
	delete[]p_student_2[n_student - 1].date.day;
	delete[]p_student_2[n_student - 1].pass;
	delete[]p_student_2;
}
void edit_student_name(student*& p, student*& p_class, int n, int n_class, char* id, int i) {
	char tempt[50];
	std::cout << " Enter new student name " << std::endl;
	std::cin.getline(tempt, 50);
	std::cin.getline(tempt, 50);
	strcpy_s(p_class[i].name, strlen(tempt) + 1, tempt);
	std::cout << " Edit student name successfully " << std::endl;
	for (int i = 0; i < n; ++i) {
		if (strcmp(p[i].id, id) == 0) {
			strcpy_s(p[i].name, strlen(tempt) + 1, tempt);
			break;
		}
	}
	write_student_data(p, n);
}
void edit_student_dob(student*& p, student*& p_class, int n, int n_class, char* id, int i) {
	dob* date = new dob;
	char tempt[20];
	std::cout << " Enter new date of birth of student (year, month, day) " << std::endl;
	std::cin >> tempt;
	date->year = new char[strlen(tempt) + 1];
	strcpy_s(date->year, strlen(tempt) + 1, tempt);
	std::cin >> tempt;
	date->month = new char[strlen(tempt) + 1];
	strcpy_s(date->month, strlen(tempt) + 1, tempt);
	std::cin >> tempt;
	date->day = new char[strlen(tempt) + 1];
	strcpy_s(date->day, strlen(tempt) + 1, tempt);
	strcpy_s(p_class[i].date.year, strlen(date->year) + 1, date->year);
	strcpy_s(p_class[i].date.month, strlen(date->month) + 1, date->month);
	strcpy_s(p_class[i].date.day, strlen(date->day) + 1, date->day);
	std::cout << " Change date of birth successfully " << std::endl;
	for (int j = 0; j < n; ++j) {
		if (strcmp(p[j].id, id) == 0) {
			create_password(p_class[i].date.year, p_class[i].date.month, p_class[i].date.day, p[j].pass);
			strcpy_s(p_class[i].pass, strlen(p[j].pass) + 1, p[j].pass);
			std::cout << " Reset password successfully " << std::endl;
			break;
		}
	}
	write_student_data(p, n);
	delete[]date->year;
	delete[]date->month;
	delete[]date->day;
	delete date;
}
void remove_a_student(student*& p, student*& p_class, int n, int n_class, char* id, int i) {
	strcpy_s(p_class[i].status, 2, "0");
	for (int i = 0; i < n; ++i) {
		if (strcmp(p[i].id, id) == 0) {
			strcpy_s(p[i].status, 2, "0");
			break;
		}
	}
	std::cout << " Remove student " << id << " completely " << std::endl;
	write_student_data(p, n);
}
void change_class(student*& p, student*& p_class, int n, int n_class, char* id, int i) {
	strcpy_s(p_class[i].status, 2, "0");
	char tempt[20], filename[20];
	view_list_class();
	std::cout << " Enter class you want to change " << std::endl;
	std::cin >> tempt;
	for (int j = 0; j < n; ++j) {
		if (strcmp(p[j].id, id) == 0) {
			strcpy_s(p[j].classname, strlen(tempt) + 1, tempt);
			break;
		}
	}
	write_student_data(p, n);
	strcpy_s(filename, strlen(tempt) + 1, tempt);
	strcat_s(filename, 20, ".txt");
	student* p_tempt = nullptr;
	int n_tempt = 0;
	class_data(filename, p_tempt, n_tempt);
	student* p_class_2 = new student[n_tempt + 1];
	int n_class_2 = n_tempt + 1;
	for (int j = 0; j < n_class_2; ++j) {
		if (j == n_class_2 - 1) {
			p_class_2[j].id = p_class[i].id;
			p_class_2[j].name = p_class[i].name;
			p_class_2[j].pass = p_class[i].pass;
			p_class_2[j].date.year = p_class[i].date.year;
			p_class_2[j].date.month = p_class[i].date.month;
			p_class_2[j].date.day = p_class[i].date.day;
			p_class_2[j].classname = p_class[i].classname;
			p_class_2[j].status = new char[2];
			strcpy_s(p_class_2[j].status, 2, "1");
		}
		else {
			p_class_2[j].id = p_tempt[j].id;
			p_class_2[j].name = p_tempt[j].name;
			p_class_2[j].pass = p_tempt[j].pass;
			p_class_2[j].date.year = p_tempt[j].date.year;
			p_class_2[j].date.month = p_tempt[j].date.month;
			p_class_2[j].date.day = p_tempt[j].date.day;
			p_class_2[j].classname = p_tempt[j].classname;
			p_class_2[j].status = p_tempt[j].status;
		}
	}
	write_class_data(filename, p_class_2, n_class_2);
	if (n_tempt > 1) delete_class_data(p_tempt, n_tempt);
	delete[]p_class_2[n_class_2 - 1].status;
	delete[]p_class_2;
}
void view_student_class() {
	int n;
	student* p = nullptr;
	char tempt[20], filename[20];
	view_list_class();
	std::cout << " Enter classname to view student " << std::endl;
	std::cin >> tempt;
	strcpy_s(filename, strlen(tempt) + 1, tempt);
	strcat_s(filename, 20, ".txt");
	class_data(filename, p, n);
	if (n != 0) {
		for (int i = 0; i < n; ++i) {
			if (strcmp(p[i].status, "1") == 0) {
				std::cout << p[i].id << " " << p[i].name << std::endl;
			}
		}
		delete_class_data(p, n);
	}
}
void view_list_class() {
	std::ifstream fi("class.txt");
	if (!fi.is_open()) std::cout << " Can not open class data file " << std::endl;
	else {
		int n;
		char tempt[10];
		fi >> n;
		for (int i = 0; i < n; ++i) {
			fi >> tempt;
			std::cout << tempt << std::endl;
		}
	}
}
void edit_existing_student(student*& p, int n) {
	char tempt[20], filename[20];
	char* id;
	std::cout << " Enter student's class " << std::endl;
	std::cin >> tempt;
	strcpy_s(filename, strlen(tempt) + 1, tempt);
	strcat_s(filename, 20, ".txt");
	std::cout << " Enter student's id " << std::endl;
	std::cin >> tempt;
	id = new char[strlen(tempt) + 1];
	strcpy_s(id, strlen(tempt) + 1, tempt);
	student* p_class = nullptr;
	int n_class = 0;
	class_data(filename, p_class, n_class);
	for (int i = 0; i < n_class; ++i) {
		if (strcmp(p_class[i].id, id) == 0 && strcmp(p_class[i].status, "1") == 0) {
			int choice;
			std::cout << " Enter 1: Edit student's name " << std::endl;
			std::cout << " Enter 2: Edit student's date of birth " << std::endl;
			std::cout << " Enter 3: Change student's class " << std::endl;
			std::cout << " Enter 4: Remove a student " << std::endl;
			std::cout << " Enter 0: Exit " << std::endl;
			std::cin >> choice;
			if (choice != 0) {
				switch (choice) {
				case 1: {
					edit_student_name(p, p_class, n, n_class, id, i);
					write_class_data(filename, p_class, n_class);
					break;
				}
				case 2: {
					edit_student_dob(p, p_class, n, n_class, id, i);
					write_class_data(filename, p_class, n_class);
					break;
				}
				case 3: {
					change_class(p, p_class, n, n_class, id, i);
					write_class_data(filename, p_class, n_class);
					break;
				}
				case 4: {
					remove_a_student(p, p_class, n, n_class, id, i);
					write_class_data(filename, p_class, n_class);
					break;
				}
				}
			}
			delete[]id;
			delete_class_data(p_class, n_class);
			break;
		}
	}
}