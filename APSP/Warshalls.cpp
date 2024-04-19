#include <iostream>
#include <climits>
using namespace std;
#define m 10
void printGraph(int n,int graph[][m]){
     for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
                if(graph[i][j] == INT_MAX)
                cout << "INF ";
            else
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}
void ASAP(int n,int graph[][m]){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                      if(graph[i][k] != INT_MAX && graph[k][j] != INT_MAX)
                graph[i][j]=min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
}
int main() {
    int n, Edges,t;
    cout<<"Directed (1) Undirected (0): ";
    cin>>t;
    cout << "Enter the number of vertices: ";
    cin >> n;
    int graph[m][m];
        for(int i=1;i<=n;i++){
          for(int j=1;j<=n;j++){
                if(i==j)
                graph[i][j]=0;
          else
            graph[i][j]=INT_MAX;
        }
      }
    cout << "Enter the number of edges: ";
    cin >> Edges;
    for (int i = 0; i < Edges; i++) {
        int src, dest, weight;
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> src >> dest >> weight;
        graph[src][dest]=weight;
        if(t==0)
               graph[dest][src]=weight;
    }
    cout<<endl<<"Adjacency Matrix: "<<endl;
    printGraph(n,graph);
    ASAP(n,graph);
    cout<<endl<<"Resultant Matrix: "<<endl;
    printGraph(n,graph);
    return 0;
}
