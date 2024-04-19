#include <bits/stdc++.h>
using namespace std;
class Employee {
 public:
  int id,age;
  double height;
  string name, designation;
  Employee (int id, string name, string dept, int age, double height){
        this->id=id;
        this->name=name;
        this->designation=dept;
        this->age=age;
        this->height=height;
  }
    bool operator<(const Employee& other) const {
        return age > other.age;
 }
};

int main(){
 priority_queue<Employee>pq;
 int n;
 cout<<"Enter no of Employees: ";
 cin>>n;
   int id,age;
   double height;
  string name, designation;
  for(int i=0;i<n;i++){
  cout<<"Enter Employee "<<i+1<<" ID , Name , Designation , Age and Height : ";
  cin>>id>>name>>designation>>age>>height;
  Employee e(id,name,designation,age,height);
  pq.push(e);
  }
    cout << "Employee Information based on Age (in increasing order)"<<endl;
    while (!pq.empty()) {
        Employee emp = pq.top();
        pq.pop();
        cout <<"ID: "<<emp.id <<", Name: "<<emp.name<<", Designation: " <<emp.designation <<", Age: "<< emp.age <<", Height: "<< emp.height <<endl;
    }
    return 0;
}
