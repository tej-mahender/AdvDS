#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void heapify(vector<int>& heap, int i, int n) {
    int parent = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] > heap[parent]) {
        parent = left;
    }

    if (right < n && heap[right] > heap[parent]) {
        parent = right;
    }

    if (parent != i) {
        swap(heap[i], heap[parent]);
        heapify(heap, parent, n);
    }
}

void insert(vector<int>& heap, int value) {
    heap.push_back(value);
    int i = heap.size() - 1;
    while (i > 0){
        int parent = (i-1)/2;
        if(heap[parent] < heap[i]) {
        swap(heap[parent], heap[i]);
        i = parent;
    }
    else
        break;
    }
}

int extractMax(vector<int>& heap) {
    if (heap.empty()) {
        return -1;
    }

    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    heapify(heap, 0, heap.size());

    return max;
}

vector<int> merge(vector<int>& heap1, vector<int>& heap2) {
    while(!heap2.empty())
       insert(heap1,extractMax(heap2));
 return heap1;
}

void display(const vector<int>& heap) {
    cout << "Priority Queue: ";
    for (int value : heap) {
        cout << value << " ";
    }
    cout <<endl;
}

int main() {
    vector<int> priorityQueue;
    int choice, value,n;
    cout << "1.Inserting " << endl;
    cout << "2.ExtractMax(Delete)" << endl;
    cout << "3.Merge" << endl;
    cout << "4.Display" <<endl;
    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            insert(priorityQueue, value);
            break;
        case 2:
            cout << "Deleted value: " << extractMax(priorityQueue) << endl;
            break;
        case 3:
            {
                vector<int> secondHeap;
                cout << "Enter the number of elements to insert in the second priority queue: ";
                cin >> n;
                cout << "Enter the elements:";
                for (int i = 0; i < n; i++) {
                    //int element;
                    cin >> value;
                    insert(secondHeap,value);
                }
                priorityQueue = merge(priorityQueue, secondHeap);
            }
            break;
        case 4:
            display(priorityQueue);
            break;

        default:
            cout << "Invalid choice!";
        }

        cout << "\nDo you want to continue:(press 1 for yes): ";
        cin >> choice;
    }
     while (choice == 1);
     return 0;
}
