#include<iostream>
#include<vector>
#include<algorithm>
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
        swap(heap[parent], heap[i]);
        heapify(heap, parent, n);
    }
}
void heapSort(vector<int>& heap) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, i, n);
 }
    for (int i = n - 1; i > 0; i--) {
        swap(heap[0], heap[i]);
        heapify(heap, 0, i);
    }
}
int main() {
 int n, value;
 vector<int> h;
 cout << "Enter the number of elements: ";
 cin >> n;
 cout << "Enter the elements: ";
 for (int i = 0; i < n; i++) {
    cin >> value;
    h.push_back(value);
 }
 heapSort(h);
 cout << "Sorted order: ";
 for (int i = 0; i < n; i++)
    cout << h[i] << " ";
    cout << endl;
 return 0;
}
