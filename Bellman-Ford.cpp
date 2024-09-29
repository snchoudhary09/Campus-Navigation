#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

//useful for figuring out the quickest way to get from one point to another another in a network.

#define V 14

// A structure to represent a weighted edge in graph
struct Edge {
    int src, dest, weight;
};

// A utility function to print the solution
void printSolution(int dist[], vector<int>& parent, int src) {
    std::cout << "Vertex\t\tDistance from Source\tPath\n";
    for (int i = 0; i < V; i++) {
        std::cout << i << "\t\t" << dist[i] << "\t\t\t";
        if (dist[i] != INT_MAX) {
            vector<int> path;
            int current = i;
            while (current != src) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(src);
            for (int j = path.size() - 1; j >= 0; --j) {
                std::cout << path[j];
                if (j != 0) std::cout << " -> ";
            }
        } else {
            std::cout << "No path";
        }
        std::cout << "\n";
    }
}

// The main function that finds shortest distances from src to all other vertices
// using Bellman-Ford algorithm.
void bellmanFord(int graph[V][V], int src) {
    int dist[V];
    vector<int> parent(V, -1); // To store parent of each vertex
    // Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges |V| - 1 times. A simple shortest path from src to any other
    // vertex can have at-most |V| - 1 edges
    for (int i = 0; i < V - 1; i++) {
        // Update dist value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are still in queue
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u; // Update parent of vertex v
                }
            }
        }
    }

    // Check for negative-weight cycles. The above step guarantees shortest
    // distances if graph doesn't contain negative weight cycle. If we get a
    // shorter path, then there is a cycle.
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                std::cout << "Graph contains negative weight cycle\n";
                return; // If negative cycle is detected, simply return
            }
        }
    }

    // Print the distance array and path
    printSolution(dist, parent, src);
}

// Driver program to test above functions
int main() {
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
    int s;
    cin>>s;
    bellmanFord(graph, s);

    return 0;
}
