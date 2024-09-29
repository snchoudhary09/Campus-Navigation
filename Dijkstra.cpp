#include <limits.h>
#include<iostream>
#include<vector>
using namespace std;

#define V 14

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printPath(vector<int> parent, int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << " -> " << j;
}

void printSolution(int dist[], vector<int> parent, int src) {
    printf("Vertex \t\t Distance from Source \t         Path\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d \t\t\t\t %d", i, dist[i], src);
        printPath(parent, i);
        cout << endl;
    }
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool sptSet[V];
    vector<int> parent(V, -1);

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(dist, parent, src);
}

int main() {
    int src;
    int graph[V][V] = {
        {   0,  550,  700,  850, 1600,    0,    0,    0,    0,    0,    0,    0,    0,    0},
        { 550,    0,  600,    0, 1200,  270,    0,    0,    0, 1000,    0,    0,    0, 1400},
        { 700,  600,    0,  900,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
        { 850,    0,  900,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
        {1600, 1200,    0,    0,    0,    0,    0,    0,    0,  300,  800,    0,    0,    0},
        {   0,  270,    0,    0,    0,    0,  160,    0,    0,    0,    0,    0,    0,    0},
        {   0,    0,    0,    0,    0,  160,    0,  300,    0,    0,    0,    0,    0,    0},
        {   0,    0,    0,    0,    0,    0,  300,    0,  300,    0,    0,    0,    0,    0},
        {   0,    0,    0,    0,    0,    0,    0,  300,    0,  400,    0,    0,  300,    0},
        {   0, 1000,    0,    0,  300,    0,    0,    0,  400,    0,  900,  700,    0,    0},
        {   0,    0,    0,    0,  800,    0,    0,    0,    0,  900,    0,  750,    0,    0},
        {   0,    0,    0,    0,    0,    0,    0,    0,    0,  700,  750,    0,  300,    0},
        {   0,    0,    0,    0,    0,    0,    0,    0,  300,    0,    0,  300,    0,  650},
        {   0, 1400,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  650,    0}
    };
    cout<<"Enter the Source Node: ";
    int t;
    cin>>t;
    dijkstra(graph, t);
    return 0;
}
