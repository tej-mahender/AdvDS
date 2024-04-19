#include <iostream>
#include <vector>
using namespace std;

// Initialize every element as a separate tree
vector<int> parent;

// Parent of Node[i] (Root node P[i]=-1)
void initialize(int n) {
    parent.resize(n+1, -1);
}

// Union operation: merges two sets
void simpleUnion(int i, int j) {
    parent[j] = i;
}

// Find operation: finds the root of the tree containing the element i
int simpleFind(int i) {
    while (parent[i] >= 0) {
        i = parent[i];
    }
    return i;
}

int main() {
    int n,m;
    cout<<"Enter Number of elements: ";
    cin>>n;
    initialize(n);
    // Perform some unions
    cout<<"Enter number of union operations: ";
    cin>>m;
    for(int i=0;i<m;i++){
        int x,y;
        cout<<"Enter pair: ";
        cin>>x>>y;
        simpleUnion(x,y);
    }

    // Find representative/root of each element
    cout<<endl;
    for (int i = 1; i <= n; ++i) {
        cout << "Parent of(" << i << "): " << parent[i]<< endl;
    }
    cout<<endl;
     for (int i = 1; i <= n; ++i) { // Start from 1 to n
        cout << "SimpleFind(" << i << "): " << simpleFind(i) << endl;
    }
    return 0;
}
