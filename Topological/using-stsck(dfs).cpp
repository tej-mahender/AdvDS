#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& s) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, s);
        }
    }
    s.push(node);
}

vector<int> topoSort(int V, vector<vector<int>>& graph) {
    vector<bool> visited(V, false);
    stack<int> s;
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited, s);
        }
    }
    vector<int> result;
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
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
