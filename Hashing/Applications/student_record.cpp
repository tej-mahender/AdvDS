#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

 class Student {
    public:
    string name;
    int id;
    string dept;

     Student() {}

     Student(string name, int id, string dept) {
        this->name = name;
        this->id = id;
        this->dept = dept;
    }
 };

int main() {

    unordered_map<int,Student>record;
    int n,key;
    cout<<"Enter no. of Students: ";
    cin>>n;
            string name;
            int id;
            string dept;
    for(int i=0;i<n;i++){
            cout<<"Enter Details of student "<<i+1<<" : "<<endl;
            cout<<"Enter student name: ";
            cin>>name;
            cout<<"Enter student ID: ";
            cin>>id;
            cout<<"Enter department: ";
            cin>>dept;
            Student s(name, id, dept);
            record[id] = s;
    }
    cout<<"Enter student ID to be searched: ";
    cin>>key;
    auto it=record.find(key);
    if(it !=record.end()){
                 Student s = it->second;
                cout<<"Name: "<<s.name<<endl;
                cout<<"Student ID: "<<s.id<<endl;
                cout<<"Department: "<<s.dept<<endl;
                }
                 else
                cout<<"No record found for ID "<<key<<endl;
    return 0;
}
