#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <string>
using namespace std;

// ------------------- Person Base Class -------------------
class Person {
protected:
    string name;
    int id;

public:
    Person() : name("Unknown"), id(0) {}//default constructor
    Person(string n, int i) : name(n), id(i) {}//parameterized constructor
    Person(const Person& p) : name(p.name), id(p.id) {}//copy constructor

    virtual void display() const {
        cout << "Name: " << name << "\nID: " << id << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }

    virtual ~Person() {}//destructor
};

// ------------------- Student Derived Class -------------------
class Student : public Person {
private:
    float marks;

public:
    Student() : Person(), marks(0.0f) {}
    Student(string n, int i, float m) : Person(n, i), marks(m) {}

    void displayStudent() const {
        cout << "\n--- Student Info ---\n";
        display();
        cout << "Marks: " << marks << "\nGrade: " << calculateGrade() << endl;
        cout << "---------------------\n";
    }

    char calculateGrade() const {
        if (marks >= 90) return 'A';
        else if (marks >= 75) return 'B';
        else if (marks >= 60) return 'C';
        else if (marks >= 50) return 'D';
        else return 'F';
    }

    bool operator==(const Student& s) const {
        return id == s.id;
    }

    Student operator+(const Student& s) {
        return Student(name + "&" + s.name, id, marks + s.marks);
    }

    friend ostream& operator<<(ostream& out, const Student& s);
    friend istream& operator>>(istream& in, Student& s);
};

ostream& operator<<(ostream& out, const Student& s) {
    out << "Name: " << s.name << "\nID: " << s.id << "\nMarks: " << s.marks << "\nGrade: " << s.calculateGrade() << endl;
    return out;
}

istream& operator>>(istream& in, Student& s) {
    cin.ignore();
    cout << "Enter student name: ";
    getline(in, s.name);
    cout << "Enter student ID: ";
    in >> s.id;
    cout << "Enter student marks: ";
    in >> s.marks;
    return in;
}

// ------------------- Course Class -------------------
class Course {
private:
    string courseName;
    int courseCode;

public:
    Course() : courseName("Unknown"), courseCode(0) {}
    Course(string name, int code) : courseName(name), courseCode(code) {}

    void displayCourse() const {
        cout << "Course: " << courseName << " (Code: " << courseCode << ")" << endl;
    }

    int getCourseCode() const {
        return courseCode;
    }
};

// ------------------- Enrollment Class -------------------
class Enrollment {
private:
    map<int, vector<Course>> enrollments;

public:
    void enrollStudent(int studentId, const Course& course) {
        for (auto& c : enrollments[studentId]) {
            if (c.getCourseCode() == course.getCourseCode()) {
                throw runtime_error("Student already enrolled in this course.");
            }
        }
        enrollments[studentId].push_back(course);
    }

    void displayEnrollment(int studentId) const {
        auto it = enrollments.find(studentId);
        if (it != enrollments.end() && !it->second.empty()) {
            cout << "\nStudent ID: " << studentId << " is enrolled in:\n";
            for (const auto& course : it->second) {
                course.displayCourse();
            }
            cout << "---------------------\n";
        }
    }

    void displayAllEnrollments() const {
        if (enrollments.empty()) {
            cout << "No enrollments found.\n";
            return;
        }

        cout << "\n--- All Enrolled Students ---\n";
        for (const auto& entry : enrollments) {
            displayEnrollment(entry.first);
        }
    }

    bool isEnrolled(int studentId) const {
        auto it = enrollments.find(studentId);
        return (it != enrollments.end() && !it->second.empty());
    }
};

// ------------------- Utility Functions -------------------
void checkStudentExists(const map<int, Student>& students, int id) {
    if (students.find(id) == students.end()) {
        throw runtime_error("Student with ID " + to_string(id) + " not found.");
    }
}

void saveStudentsToFile(const map<int, Student>& students) {
    ofstream fout("students.txt");
    if (!fout) {
        cerr << "Error opening file!" << endl;
        return;
    }
    for (const auto& pair : students) {
        fout << pair.second.getName() << "," << pair.second.getId() << endl;
    }
    fout.close();
}

void displayAllStudents(const map<int, Student>& students) {
    cout << "\n--- Registered Students ---\n";
    for (const auto& pair : students) {
        cout << pair.second << endl;
    }
}

void searchStudentByName(const map<int, Student>& students, const string& name) {
    bool found = false;
    for (const auto& pair : students) {
        if (pair.second.getName() == name) {
            cout << pair.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
}

void showMenu() {
    cout << "\n************* Student Admission System *************\n";
    cout << "\n1. Register New Student\n";
    cout << "2. Enroll Student in Courses\n";
    cout << "3. Display Specific Student Info\n";
    cout << "4. Display All Enrolled Students and Their Courses\n";
    cout << "5. Search Student by Name\n";
    cout << "6. Delete Student Record\n";
    cout << "7. Display All Registered Students\n";
    cout << "8. Exit\n";
    cout << "\n****************************************************\n\n";
}

// ------------------- Main Function -------------------
int main() {
    map<int, Student> students;
    Enrollment enrollment;

    vector<Course> courses = {
        {"AIML", 201},
        {"AIDS", 202},
        {"CSE", 203},
        {"ENTC", 204},
        {"Textile", 205}
    };

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    Student s;
                    cout << "\n--- Register New Student ---\n";
                    cin >> s;
                    students[s.getId()] = s;
                    saveStudentsToFile(students);
                    break;
                }
                case 2: {
                    int studentId;
                    cout << "\nEnter student ID to enroll: ";
                    cin >> studentId;
                    checkStudentExists(students, studentId);

                    cout << "Available Courses:\n";
                    for (size_t i = 0; i < courses.size(); ++i) {
                        cout << i + 1 << ". ";
                        courses[i].displayCourse();
                    }

                    cout << "Enter course number to enroll (0 to stop):\n";
                    int courseChoice;
                    cin >> courseChoice;
                    
                    if (courseChoice == 0) 
						break;
                    if (courseChoice >= 1 && courseChoice <= (int)courses.size()) {
                        enrollment.enrollStudent(studentId, courses[courseChoice - 1]);
                        cout<<"Student is successfully enrolled!\n";
                    } else {
                        cout << "Invalid choice!\n";
                    }
                    break;
                }
                case 3: {
                    int studentId;
                    cout << "Enter student ID to display info: ";
                    cin >> studentId;
                    checkStudentExists(students, studentId);
                    students[studentId].displayStudent();
                    enrollment.displayEnrollment(studentId);
                    break;
                }
                case 4: {
                    enrollment.displayAllEnrollments();
                    break;
                }
                case 5: {
                    string name;
                    cout << "Enter student name to search: ";
                    cin.ignore();
                    getline(cin, name);
                    searchStudentByName(students, name);
                    break;
                }
                case 6: {
                    int studentId;
                    cout << "Enter student ID to delete: ";
                    cin >> studentId;
                    students.erase(studentId);
                    cout << "Student deleted successfully.\n";
                    saveStudentsToFile(students);
                    break;
                }
                case 7: {
                    displayAllStudents(students);
                    break;
                }
                case 8: {
                    cout << "Exiting system. Goodbye!\n";
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 8);

    return 0;
}

