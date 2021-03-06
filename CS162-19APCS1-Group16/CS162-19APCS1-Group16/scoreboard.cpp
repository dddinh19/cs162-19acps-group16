#include "function.h" 
void printScore(scoreboard a, std::string stuID, std::string stuName, int k) {
	std::cout << center_align(std::to_string(k), 8) << "|";
	std::cout << center_align(stuID, 20) << "|";
	std::cout << center_align(stuName, 30) << "|";
	std::cout.setf(std::ios::fixed);
	std::cout.precision(2);
	std::cout << "  "<<a.midterm<<"  " << "|";
	std::cout << "  " << a.final << "  " << "|";
	std::cout << "  " << a.bonus << "  " << "|";
	std::cout << "  " << a.total << "  " << "|" << std::endl;
	std::cout << std::setfill('-');
	std::cout << std::setw(97) << "-" << std::endl;
	std::cout << std::setfill(' ');
}
void staff_view_scoreboard(){
	semester* p_year = nullptr;
	int n_year = 0;
	std::string tyears, tseme;
	semester_data(p_year, n_year);
	view_academic_year(p_year, n_year);
	std::cout << "Enter academic year " << std::endl;
	std::cin >> tyears;
	if (view_semester(p_year, n_year, tyears) != -1) {
		std::cout << "Enter semester " << std::endl;
		std::cin >> tseme;
		if (check_semester(p_year, n_year, tyears, tseme))
		{
			course* p_course;
			int n_course = 0;
			std::string filename = "Data/Courses/" + tyears + "/" + tseme + "/course.txt";
			lecturer_course_data(filename, p_course, n_course);
			read_coursename(tseme, tyears, p_course, n_course);
			read_time_room_dow(tseme, tyears, p_course, n_course);
			system("CLS");
			int choice;
			std::cout << std::setw(75) << "COURSES IN " << tyears << " OF " << tseme << std::endl;
			print_scheduleboard(tseme, tyears, p_course, n_course);
			do {
				std::cout << "Please enter an attached number of the course you want to view students list: ";
				std::cin >> choice;
				if (choice <= 0 && choice > n_course)
					std::cout << "Invalid choice!!! Please choose again. " << std::endl;
			} while (choice <= 0 && choice > n_course);
			if (check_course(p_course, n_course, p_course[choice - 1].courseID, p_course[choice - 1].classname)) {
				student* p_student = nullptr;
				int n_student = 0;
				filename = "Data/Courses/" + tyears + "/" + tseme + "/" + p_course[choice - 1].courseID + "/" + p_course[choice - 1].classname + "/student.txt";
				student_course_data(filename, p_student, n_student);
				system("CLS");
				std::cout << std::setw(45) << "SCOREBOARD OF " << p_course[choice - 1].courseID << " IN CLASS " << p_course[choice - 1].classname << std::endl;
				std::cout << std::setfill('=');
				std::cout << std::setw(97) << "=" << std::endl;
				std::cout << std::setfill(' ');
				// No-8, Student ID-20, Student name-30, Mark-8
				std::cout << std::setw(3) << " " << "No" << std::setw(3) << " " << "|";
				std::cout << std::setw(5) << " " << "Student ID" << std::setw(5) << " " << "|";
				std::cout << std::setw(9) << " " << "Student name" << std::setw(9) << " " << "|";
				std::cout << std::setw(2) << " " << "MID" << std::setw(3) << " " << "|";
				std::cout << std::setw(1) << " " << "FINAL" << std::setw(2) << " " << "|";
				std::cout << std::setw(1) << " " << "BONUS" << std::setw(2) << " " << "|";
				std::cout << std::setw(1) << " " << "TOTAL" << std::setw(2) << " " << "|" << std::endl;
				std::cout << std::setfill('-');
				std::cout << std::setw(97) << "-" << std::endl;
				std::cout << std::setfill(' ');
				for (int i = 0; i < n_student; i++) {
					read_class_of_student(p_student[i]);
					read_student_name1(p_student[i]);
					filename = "Data/Courses/" + tyears + "/" + tseme + "/" + p_course[choice - 1].courseID + "/" + p_course[choice - 1].classname + "/" + p_student[i].id + "/scoreboard.txt";
					read_scoreboard(filename, p_student[i].score);
					printScore(p_student[i].score, p_student[i].id, p_student[i].name, i + 1);
				}
				delete[]p_student;
			}
			else std::cout << "Course does not exist " << std::endl;
			delete[]p_course;
		}
		else std::cout << "Semester does not exist " << std::endl;
	}
	else std::cout << "Academic year does not exist " << std::endl;
	delete[]p_year;
}

void export_scoreboard()
{
	std::ofstream fo;
	semester* p_year = nullptr;
	int n_year = 0;
	std::string year, sem;
	semester_data(p_year, n_year);
	view_academic_year(p_year, n_year);
	std::cout << "Enter academic year " << std::endl;
	std::cin >> year;
	if (view_semester(p_year, n_year, year) != -1) {
		std::cout << "Enter semester " << std::endl;
		std::cin >> sem;
		if (check_semester(p_year, n_year, year, sem))
		{
			std::string p_class;
			std::cout << "Enter the class to export the scoreboard of the course: ";
			std::cin >> p_class;
			if (check_class(p_class))
			{
				course c; int n;
				std::ifstream fi;
				int num_course = 0;
				fi.open("Data/Courses/" + year + "/" + sem + "/course.txt");
				fi >> num_course;
				course* cou_2 = new course[num_course];
				for (int i = 0; i < num_course; i++)
				{
					fi >> cou_2[i].courseID;
					fi >> cou_2[i].classname;
					fi >> cou_2[i].status;
					if (cou_2[i].status == 0)
						i--;
				}
				fi.close();
				std::cout << "Course ID: ";
				std::cin >> c.courseID;
				if (check_course(cou_2, num_course, c.courseID, p_class))
				{
					std::ofstream fo("Data/Courses/" + year + "/" + sem + "/" + c.courseID + "/" + p_class + "/scoreboard.csv");
					fo << "No,Student ID,Student name,Midterm,Final,Bonus,Total" << std::endl;
					fi.open("Data/Courses/" + year + "/" + sem + "/" + c.courseID + "/" + p_class + "/student.txt");
					fi >> n;
					student* stu = new student[n];
					for (int i = 0; i < n; i++)
					{
						getline(fi, stu[i].id);
						getline(fi, stu[i].id);
						fi >> stu[i].status;
						if (stu[i].status == 0) i--;
					}
					fi.close();
					float mt, fn, bn, tt;
					for (int i = 0; i < n; i++)
					{
						read_class_of_student(stu[i]);
						read_student_name1(stu[i]);
						fi.open("Data/Courses/" + year + "/" + sem + "/" + c.courseID + "/" + p_class + "/" + stu[i].id + "/scoreboard.txt");
						fi >> mt >> fn >> bn >> tt;
						fo << i + 1 << "," << stu[i].id << "," << stu[i].name << "," << mt << "," << fn << "," << bn << "," << tt << std::endl;
					}
					fo.close();
				}
				else
					std::cout << "This course doesn't exist." << std::endl;
				delete[]cou_2;
			}
			else
				std::cout << "This class doesn't exist." << std::endl;
		}
		else std::cout << "Semester does not exist " << std::endl;
	}
	else std::cout << "Academic year does not exist " << std::endl;
	delete[] p_year;
}
