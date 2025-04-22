#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string p_name;
    int p_age;
public:
    Person(string name, int age) : p_name(name), p_age(age) {}

    virtual void display() {
        cout << "Name : " << p_name<<endl;
        cout << "Age : " << p_age << endl;
    }
};

class Student : virtual public Person {
public:
    int roll_number;
    string s_branch;
    float s_marks[5];
    float s_cgpa;

    Student(string name, int age, int roll_no, string branch, float marks[5])
        : Person(name, age), roll_number(roll_no), s_branch(branch) {
        for (int i = 0; i < 5; i++) {
            s_marks[i] = marks[i];
        }
        calculateCGPA();
    }

    void calculateCGPA() {
        float total = 0;
        for (int i = 0; i < 5; i++) {
            total += s_marks[i];
        }
        s_cgpa = total / 5.0;
    }

    void display() override {
        Person::display();
        cout << "Roll Number: " << roll_number << endl;
        cout << "Branch: " << s_branch << endl;
        cout << "CGPA: " << s_cgpa << endl;
    }

    friend class Administration;
};

class Faculty : virtual public Person {
protected:
    int faculty_ID;
    string department;
    float salary;
public:
    Faculty(string name, int age, int id, string dept, float sal)
        : Person(name, age), faculty_ID(id), department(dept), salary(sal) {}

    void display() override {
        Person::display();
        cout << "Faculty ID : " << faculty_ID << endl;
        cout << "Department : " << department << endl;
        cout << "Salary : " << salary << endl;
    }

    friend class Administration;
};

class TeachingAssistant : public Student, public Faculty {
public:
    TeachingAssistant(string name, int age, int roll_no, string branch, float marks[5], int id, string dept, float sal)
        : Person(name, age), Student(name, age, roll_no, branch, marks), Faculty(name, age, id, dept, sal) {}

    void display() override {
        Person::display();
        cout << "Roll Number : " << roll_number << endl;
        cout << "Faculty ID : " << faculty_ID << endl;
        cout << "Department : " << department << endl;
        cout << "Salary : " << salary << endl;
    }
};

class Administration {
public:
    void displayPrivateDetails(Student& s, Faculty& f) {
        cout << "Administration Friend Function:" << endl;
        cout << "Student " << s.p_name << " from " << s.s_branch << " scored " << s.s_marks[0] << " marks." << endl;
        cout << "Faculty " << f.p_name << " teaches " << f.department << "." << endl;
    }
};

int main() {
    float studentMarks[5] = {8.9, 9.0, 8.5, 9.2, 8.8};

    Student s1("Priyanka", 19, 23, "CSE (AI-ML)", studentMarks);
    Faculty f1("Prof. A.G.Shahane",32, 1001, "CSE (AI-ML)", 70000);
    TeachingAssistant ta1("Prof.D.D.Mahajan", 42, 1923, "CSE (AI-ML)", studentMarks, 2005, "Artificial Intelligence", 80000);

    cout << "Student Details: " << endl;
    s1.display();
    cout << endl;

    cout << "Faculty Details: " << endl;
    f1.display();
    cout << endl;

    cout << "Teaching Assistant Details: " << endl;
    ta1.display();
    cout << endl;

    Administration admin;
    admin.displayPrivateDetails(s1, f1);

    return 0;
}

