#include "function.h"

void read_courses_student(std::string tID, std::string tclass, std::string tseme, std::string tyear, course*& sch, int& n){
	std::ifstream fin;
	fin.open("Data/Class/" + tclass + "/" + tID + "/" + tyear + "/" + tseme + "/course.txt");
	if (!fin.is_open())
		std::cout << "Can not open file." << std::endl;
	else {
		fin >> n;
		fin.ignore(1);
		sch = new course[n];
		for (int i = 0; i < n; i++) {
			getline(fin, sch[i].courseID);
			getline(fin, sch[i].classname);
			fin >> sch[i].status;
			fin.ignore(1);
			if (sch[i].status == 0)
				--i;
		}
		fin.close();
	}
}
void read_coursename(std::string tseme, std::string tyear, course*& sch, int n) {
	std::ifstream fin;
	for (int i = 0; i < n; i++) {
		fin.open("Data/Courses/" + tyear + "/" + tseme + "/" + sch[i].courseID + "/" + sch[i].classname + "/info.txt");
		if (!fin.is_open())
			std::cout << "Can not open file." << std::endl;
		else {
			getline(fin, sch[i].courseName);
			getline(fin, sch[i].courseName);
			fin.close();
		}
	}
}
void read_studentattendance(std::string tseme, std::string tyear , course cou, std::string tID, attendance*& att) {
	std::ifstream fin;
	fin.open("Data/Courses/" + tyear + "/" + tseme + "/" + cou.courseID + "/" + cou.classname +"/"+ tID + "/attendance.txt");
	if (!fin.is_open())
		std::cout << "Can not open file." << std::endl;
	else {
		att = new attendance[10];
		for (int i = 0; i < 10; i++) {
			fin >> att[i].date.year;
			fin >> att[i].date.month;
			fin >> att[i].date.day;
			fin >> att[i].start.hour;
			fin >> att[i].start.minute;
			fin >> att[i].end.hour;
			fin >> att[i].end.minute;
			fin >> att[i].checkin.hour;
			fin >> att[i].checkin.minute;
		}
		fin.close();
	}
}
void write_studentattendance(std::string tseme, std::string tyear, course cou, std::string tID, attendance* att) {
	std::ofstream fout;
	fout.open("Data/Courses/" + tyear + "/" + tseme + "/" + cou.courseID + "/" + cou.classname +"/"+ tID + "/attendance.txt");
	if (!fout.is_open())
		std::cout << "Can not open file." << std::endl;
	else {
		for (int i = 0; i < 10; i++) {
			fout << att[i].date.year << " ";
			if (att[i].date.month< 10)
				fout << "0" << att[i].date.month << " ";
			else
				fout << att[i].date.month << " ";
			if (att[i].date.day < 10)
				fout << "0" << att[i].date.day << std::endl;
			else
				fout << att[i].date.day << std::endl;
			
			if (att[i].start.hour < 10)
				fout << "0" << att[i].start.hour << " ";
			else
				fout << att[i].start.hour << " ";
			if (att[i].start.minute < 10)
				fout << "0" << att[i].start.minute << " ";
			else
				fout << att[i].start.minute << " ";
			if (att[i].end.hour < 10)
				fout << "0" << att[i].end.hour << " ";
			else
				fout << att[i].end.hour << " ";
			if (att[i].end.minute < 10)
				fout << "0" << att[i].end.minute << " ";
			else
				fout << att[i].end.minute << " ";
			if (att[i].checkin.hour < 10)
				fout << "0" << att[i].checkin.hour << " ";
			else
				fout << att[i].checkin.hour << " ";
			if (att[i].checkin.minute < 10)
				fout << "0" << att[i].checkin.minute << std::endl;
			else
				fout << att[i].checkin.minute << std::endl;	
		}
		fout.close();
	}
}

void checkin(student stu) {
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::string tseme;
	std::string tyear;
	std::cout << "Please enter the academic years: ";
	std::cin >> tyear;
	std::cout << "Please enter the semester: ";
	std::cin >> tseme;
	semester* p_year = NULL;
	int n_year = 0;
	if (check_semester(p_year, n_year, tyear, tseme))
	{
		course* sch = NULL;
		int n, option;
		read_courses_student(stu.id, stu.classname, tseme, tyear, sch, n);
		read_coursename(tseme, tyear, sch, n);
		system("CLS");
		std::cout << "Courses for you in " << tyear << " of " << tseme << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << i + 1 << ". " << sch[i].courseID << " - " << sch[i].courseName << std::endl;
		std::cout << "Please enter a course you want to checkin: ";
		std::cin >> option;
		if (option > n || option <= 0)
			std::cout << "Invalid choice!!!" << std::endl;
		else {
			attendance* att = NULL;
			int error_checkin = 0; //0- wrong date 1- wrong time 2- checkin fine
			read_studentattendance(tseme, tyear, sch[option - 1], stu.id, att);
			for (int i = 0; i < 10; i++) {
				if (att[i].date.month == now->tm_mon + 1 && att[i].date.day == now->tm_mday)
				{
					if ((now->tm_hour<att[i].end.hour && now->tm_hour>att[i].start.hour) || (now->tm_hour == att[i].end.hour && now->tm_min <= att[i].end.minute) || (now->tm_hour == att[i].start.hour && now->tm_min >= att[i].start.minute))
					{
						att[i].checkin.hour = now->tm_hour;
						att[i].checkin.minute = now->tm_min;
						error_checkin = 2;
					}
					else
						error_checkin = 1;
					break;
				}
			}
			system("CLS");
			if (error_checkin == 0)
				std::cout << "Today is not an available date in attendance list of this course." << std::endl;
			else if (error_checkin == 1)
				std::cout << "This time is too early or too late for you to checkin." << std::endl;
			else {
				write_studentattendance(tseme, tyear, sch[option - 1], stu.id, att);
				std::cout << "Checkin successfully! Please view checkin result to ensure if everything is alright." << std::endl;
			}
			delete[]att;
		}
		delete[]sch;
	}
	else
		std::cout << "The academic years or the semester of this academic years is no longer existing!!!" << std::endl;
}

void print_checkinboard(attendance* att, course cou) {
	std::cout << std::setfill('=');
	std::cout << std::setw(69) << "=" << std::endl;
	std::cout << std::setfill(' ');
	// Width of board: Date-20, Time-15
	std::cout << std::setw(8) << " " << "Date" << std::setw(8) << " " << "|";
	std::cout << std::setw(2) << " " << "Start time" << std::setw(3) << " " << "|";
	std::cout << std::setw(3) << " " << "End time" << std::setw(4) << " " << "|";
	std::cout << " Checkin time  " << "|" << std::endl;
	std::cout << std::setfill('-');
	std::cout << std::setw(69) << "-" << std::endl;
	std::cout << std::setfill(' ');
	for (int i = 0; i < 10; i++) {
		std::cout << std::setw(5) << " " << FormatDate(att[i].date) << std::setw(5) << " " << "|";
		std::cout << std::setw(5) << " " << FormatTime(att[i].start) << std::setw(5) << " " << "|";
		std::cout << std::setw(5) << " " << FormatTime(att[i].end) << std::setw(5) << " " << "|";
		std::cout << std::setw(5) << " " << FormatTime(att[i].checkin) << std::setw(5) << " " << "|" << std::endl;
	}
	std::cout << std::setfill('-');
	std::cout << std::setw(69) << "-" << std::endl;
	std::cout << std::setfill(' ');
}
void view_checkin(student stu) {
	std::string tseme;
	std::string tyear;
	std::cout << "Please enter the academic years: ";
	std::cin >> tyear;
	std::cout << "Please enter the semester: ";
	std::cin >> tseme;
	semester* p_year = NULL;
	int n_year = 0;
	if (check_semester(p_year, n_year, tyear, tseme))
	{
		course* sch = NULL;
		int n, option;
		read_courses_student(stu.id, stu.classname, tseme, tyear, sch, n);
		read_coursename(tseme, tyear, sch, n);
		system("CLS");
		std::cout << "Courses for you in " << tyear << " of " << tseme << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << i + 1 << ". " << sch[i].courseID << " - " << sch[i].courseName << std::endl;
		std::cout << "Please enter a course you want to view the checkin result: ";
		std::cin >> option;
		system("CLS");
		if (option > n || option <= 0)
			std::cout << "Invalid choice!!!" << std::endl;
		else {
			attendance* att = NULL;
			read_studentattendance(tseme, tyear, sch[option - 1], stu.id, att);
			std::cout << std::setw(36) << "YOUR ATTENDANCE LIST OF " << sch[option - 1].courseID << " IN CLASS " << sch[option - 1].classname << std::endl;
			print_checkinboard(att, sch[option - 1]);
			std::cout << "Print the checkin result successfully!" << std::endl;
			delete[]att;
		}
		delete[]sch;
	}
	else
		std::cout << "The academic years or the semester of this academic years is no longer existing!!!" << std::endl;
}

void read_time_room_dow(std::string tseme, std::string tyear, course*& sch, int n){
	std::string trash;
	std::ifstream fin;
	for (int i = 0; i < n; i++) {
		fin.open("Data/Courses/" + tyear + "/" + tseme + "/" + sch[i].courseID + "/" + sch[i].classname + "/info.txt");
		if (!fin.is_open())
			std::cout << "Can not open file." << std::endl;
		else {
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, trash);
			getline(fin, sch[i].dayofweek);
			fin >> sch[i].start_time.hour;
			fin >> sch[i].start_time.minute;
			fin >> sch[i].end_time.hour;
			fin >> sch[i].end_time.minute;
			fin.ignore(1);
			getline(fin, sch[i].room);
			fin.close();
		}
	}
}

void print_scheduleboard(std::string tseme, std::string tyear, course* sch, int n) {
	std::cout << std::setfill('=');
	std::cout << std::setw(151) << "=" << std::endl;
	std::cout << std::setfill(' ');
	// Width of board: No-8, Course ID-15, Course name-50, Course of class- 15, Day of week-15, Time-15, Room-10
	std::cout << std::setw(3) << " " << "No" << std::setw(3) << " " << "|";
	std::cout << std::setw(3) << " " << "Course ID" << std::setw(3) << " " << "|";
	std::cout << std::setw(19) << " " << "Course name" << std::setw(20) << " " << "|";
	std::cout << "Course of class" << "|";
	std::cout << std::setw(2) << " " << "Day of week" << std::setw(2) << " " << "|";
	std::cout << std::setw(2) << " " << "Start time" << std::setw(3) << " " << "|";
	std::cout << std::setw(3) << " " << "End time" << std::setw(4) << " " << "|";
	std::cout << std::setw(3) << " " << "Room" << std::setw(3) << " " << "|" << std::endl;
	std::cout << std::setfill('-');
	std::cout << std::setw(151) << "-" << std::endl;
	std::cout << std::setfill(' ');
	for(int i=0; i<n; i++){
		std::cout << center_align(std::to_string(i + 1), 8) << "|";
		std::cout << center_align(sch[i].courseID, 15) << "|";
		std::cout << center_align(sch[i].courseName, 50) << "|";
		std::cout << center_align(sch[i].classname, 15) << "|";
		std::cout << center_align(sch[i].dayofweek, 15) << "|";
		std::cout << std::setw(5) << " " << FormatTime(sch[i].start_time) << std::setw(5) << " " << "|";
		std::cout << std::setw(5) << " " << FormatTime(sch[i].end_time) << std::setw(5) << " " << "|";
		std::cout << center_align(sch[i].room, 10) << "|" << std::endl;
	}
	std::cout << std::setfill('-');
	std::cout << std::setw(151) << "-" << std::endl;
	std::cout << std::setfill(' ');
}

void view_schedule(student stu) {
	std::string tseme;
	std::string tyear;
	std::cout << "Please enter the academic years, semester: ";
	std::cin >> tyear >> tseme;
	system("CLS");
	semester* p_year = NULL;
	int n_year = 0;
	if (check_semester(p_year, n_year, tyear, tseme)) {
		course* sch = NULL;
		int n = 0;
		read_courses_student(stu.id, stu.classname, tseme, tyear, sch, n);
		read_coursename(tseme, tyear, sch, n);
		read_time_room_dow(tseme, tyear, sch, n);
		std::cout << std::setw(65) << "YOUR SCHEDULE IN " << tyear << " OF " << tseme << std::endl;
		print_scheduleboard(tseme, tyear, sch, n);
		std::cout << "Print schedule successfully. " << std::endl;
		delete[]sch;
	}
	else
		std::cout << "The academic years or the semester of this academic years is no longer existing!!!" << std::endl;
}

void read_scoreboard(std::string tseme, std::string tyear, course cou, std::string tID, scoreboard& sco) {
	std::ifstream fin;
	fin.open("Data/Courses/" + tyear + "/" + tseme + "/" + cou.courseID + "/" + cou.classname + "/" + tID + "/scoreboard.txt");
	if (!fin.is_open())
		std::cout << "Can not open file." << std::endl;
	else {
		fin >> sco.total;
		fin >> sco.midterm;
		fin >> sco.final;
		fin >> sco.bonus;
		fin.close();
	}
}

void view_score(student stu){
	std::string tseme;
	std::string tyear;
	std::cout << "Please enter the academic years: ";
	std::cin >> tyear;
	std::cout << "Please enter the semester: ";
	std::cin >> tseme;
	system("CLS");
	semester* p_year = NULL;
	int n_year = 0;
	if (check_semester(p_year, n_year, tyear, tseme)) {
		course* sch = NULL;
		int n, option;
		read_courses_student(stu.id, stu.classname, tseme, tyear, sch, n);
		read_coursename(tseme, tyear, sch, n);
		system("CLS");
		std::cout << "Courses for you in " << tyear << " of " << tseme << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << i + 1 << ". " << sch[i].courseID << " - " << sch[i].courseName << std::endl;
		std::cout << "Please enter a course you want to view the scores of: ";
		std::cin >> option;
		system("CLS");
		if (option > n || option <= 0)
			std::cout << "Invalid choice!!!" << std::endl;
		else {
			scoreboard sco;
			read_scoreboard(tseme, tyear, sch[option - 1], stu.id, sco);
			std::cout << "All your scores of the course " << sch[option - 1].courseID << " are: " << std::endl;
			std::cout << "Total score: " << sco.total << std::endl;
			std::cout << "Midterm score: " << sco.midterm << std::endl;
			std::cout << "Finalterm score: " << sco.final << std::endl;
			std::cout << "Bonus score: " << sco.bonus << std::endl;
		}
		delete[]sch;
	}
	else
		std::cout << "The academic years or the semester of this academic years is no longer existing!!!" << std::endl;
}
