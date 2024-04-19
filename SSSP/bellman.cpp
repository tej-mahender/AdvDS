#include <iostream>
#include <climits>
using namespace std;
#define m 10

void printSolution(int dist[], int n) {
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 1; i <= n; i++)
        cout << i << "\t\t" << dist[i] << endl;
}

void bellmanFord(int graph[m][m], int n, int src) {
    int dist[n];
    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (graph[j][k] && dist[j] != INT_MAX && dist[j] + graph[j][k] < dist[k]) {
                    dist[k] = dist[j] + graph[j][k];
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] && dist[i] != INT_MAX && dist[i] + graph[i][j] < dist[j]) {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }
    }
    printSolution(dist, n);
}

int main() {
    int n, Edges, t, s;
    cout << "Enter the number of vertices: ";
    cin >> n;
    int graph[m][m];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            graph[i][j] = 0;
        }
    }
    cout << "Enter the number of edges: ";
    cin >> Edges;
    for (int i = 0; i < Edges; i++) {
        int src, dest, weight;
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> src >> dest >> weight;
        graph[src][dest] = weight;
    }
    cout << "Enter Source vertex: ";
    cin >> s;
    bellmanFord(graph, n, s);
    return 0;
}
