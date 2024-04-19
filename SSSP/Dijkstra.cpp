#include <iostream>
#include <climits>
using namespace std;
#define m 10

int minDist(int dist[], bool visited[], int n){
    int min = INT_MAX, index;
    for (int i = 1; i <= n; i++)
        if (!visited[i] && dist[i] <= min){
            min = dist[i];
             index = i;
        }
    return index;
}

void print(int dist[], int n){
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 1; i <= n; i++)
        cout << i << "\t\t" << dist[i] << endl;
}

void dijkstra(int graph[m][m], int src, int n){
    int dist[n];
    bool visited[n];

    for (int i = 1; i <= n; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {

        int u = minDist(dist, visited, n);

        visited[u] = true;

        for (int v = 1; v <= n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    print(dist, n);
}

int main() {
    int n, Edges, t, s;
    cout << "Enter the number of vertices: ";
    cin >> n;
    int graph[m][m];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
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
    dijkstra(graph, s, n);
    return 0;
}
