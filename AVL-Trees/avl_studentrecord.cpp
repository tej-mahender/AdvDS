#include <iostream>
#include <map>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    string Class;
    Student(){};
    Student(int rNo, string n, string c) : rollNo(rNo), name(n), Class(c) {}
};

class AVLtree {
public:
    map<int, Student> tree;

    void insert(Student s) {
        tree[s.rollNo] = s;
    }

    void search(int rollNo) {
        if(tree.find(rollNo) != tree.end()) {
            Student s = tree[rollNo];
            cout<<"Student Details: "<<endl;
            cout << "Name: " << s.name << endl;
            cout << "Class: " << s.Class << endl;
        } else {
            cout << "No student found with roll number " << rollNo << endl;
        }
    }
};

int main() {
    AVLtree tree;

    int n;
    int r;
    string name, Class;

    cout << "Enter Number of students: ";
    cin >> n;

    for(int i = 0; i < n; i++){
       cout << "Enter Student Rollno, Name, Class: ";
       cin >> r >> name >> Class;

       Student s(r, name, Class);
       tree.insert(s);
    }

    cout << "Enter roll number to search: ";
    cin >> r;

    tree.search(r);

    return 0;
}
