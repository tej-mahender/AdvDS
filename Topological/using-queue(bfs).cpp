#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topoSort(int V, vector<vector<int>>& graph) {
    vector<int> inDegree(V);
    // Calculate in-degree for each vertex
    for (int i = 0; i < V; ++i) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }

    // Perform BFS
    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (inDegree[i] == 0 ) {
            q.push(i);
        }
    }

    // Process the queue to get topological order
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        for (int neighbor : graph[node]) {
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return result;
}

int main() {
    int n, Edges;
    cout << "Enter the number of vertices: ";
    cin >> n;
    vector<vector<int>> graph(n);
    cout << "Enter the number of edges: ";
    cin >> Edges;
    for (int i = 0; i < Edges; i++) {
        int src, dest;
        cout << "Enter edge " << i + 1 << " (source destination): ";
        cin >> src >> dest;
        graph[src].push_back(dest);
    }
    vector<int> result = topoSort(n, graph);
    cout << "Topological Order: ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
