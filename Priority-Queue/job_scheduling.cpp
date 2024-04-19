#include <bits/stdc++.h>
using namespace std;

class Process {
  public:
    string name;
    int arrivalTime;
    int burstTime;
    bool operator>(const Process& other) const {
      return this->burstTime > other.burstTime;
    }
};
void schedule(vector<Process>&processes, int n) {
    //sorts according to arrival function using lambda function
      sort(processes.begin(), processes.end(), [](Process a, Process b)
            {return a.arrivalTime < b.arrivalTime;}
        );

      int currentTime = processes[0].arrivalTime;
      //priorityqueue declaration as min heap
      priority_queue<Process, vector<Process>, greater<Process>> readyQueue;
      readyQueue.push(processes[0]);
      processes[0].arrivalTime = -1;

      cout << "PID\tArrival time\tBurst time" << endl;
      while (!readyQueue.empty()) {
        Process current = readyQueue.top();
        readyQueue.pop();

        cout << current.name << "\t"
             << current.arrivalTime << "\t\t"
             << current.burstTime << endl;

        currentTime += current.burstTime;

        for (int i = 0; i < n; i++) {
          if (processes[i].arrivalTime <= currentTime && processes[i].arrivalTime != -1) {
            readyQueue.push(processes[i]);
            processes[i].arrivalTime = -1;
          }
        }
      }
    }



int main() {

  int n;
  cout << "Enter number of processes: ";
  cin >> n;
vector<Process> p(n);
  for(int i = 0; i < n; i++) {
     cout << "Enter name, arrival time and burst time for process " << (i+1) << ": ";
     cin >> p[i].name >> p[i].arrivalTime >> p[i].burstTime;
  }
  cout << "\nScheduled Jobs:" << endl;
   schedule(p, n);
}
