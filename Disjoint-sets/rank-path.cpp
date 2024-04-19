#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;
vector<int> ranks;

void initialize(int n) {
    parent.resize(n + 1, -1);
    ranks.resize(n + 1, 0);
}

int simpleFind(int i) {
    if (parent[i] == -1) {
        return i;
    }
    return parent[i] = simpleFind(parent[i]); // Path compression
}

void simpleUnion(int i, int j) {
    int root_i = simpleFind(i);
    int root_j = simpleFind(j);

    if (root_i != root_j) {
        if (ranks[root_i] < ranks[root_j]) {
            parent[root_i] = root_j;
        } else if (ranks[root_i] > ranks[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            ranks[root_i]++;
        }
    }
}

int main() {
    int n, m;
    cout << "Enter Number of elements: ";
    cin >> n;
    initialize(n);

    cout << "Enter number of union operations: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cout << "Enter pair: ";
        cin >> x >> y;
        simpleUnion(x, y);
    }

    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "Parent of(" << i << "): " << parent[i] << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "SimpleFind(" << i << "): " << simpleFind(i) << endl;
    }

    return 0;
}
