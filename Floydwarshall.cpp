#include <iostream>
#include <limits.h>

// Number of vertices in the graph
#define V 14

// Function to print the solution matrix
void printSolution(int dist[][V]) {
    std::cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INT_MAX)
                std::cout << "INF\t";
            else
                std::cout << dist[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// Function to perform Floyd-Warshall algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize distance matrix
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            dist[i][j] = graph[i][j];

    // Update distance matrix by considering all vertices as intermediate vertices
    for (int k = 0; k < V; ++k) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; ++i) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; ++j) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distances
    printSolution(dist);
}

// Driver program to test above function
int main() {
    // Example graph adjacency matrix
    int graph[V][V] = {
    {0, 550, 700, 850, 1600, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,   INT_MAX, INT_MAX, INT_MAX},
    {550, 0, 600, INT_MAX, 1200, 270, INT_MAX, INT_MAX, INT_MAX, 1000,   INT_MAX,    INT_MAX,   INT_MAX,   1400},
    {700, 600, 0, 900, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
    {850, INT_MAX, 900, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
    {1600, 1200, INT_MAX, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 300, 800,   INT_MAX, INT_MAX,   INT_MAX},
    {INT_MAX, 270, INT_MAX, INT_MAX, INT_MAX, 0, 160, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 160, 0, 300, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 300, 0, 300, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 300, 0, 400, INT_MAX,   INT_MAX, 300, INT_MAX},
    {INT_MAX, 1000, INT_MAX, INT_MAX, 300, INT_MAX, INT_MAX,   INT_MAX,  400, 0,   900,  700,    INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 800, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 900, 0, 750,  INT_MAX, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 700, 750,  0, 300, INT_MAX},
    {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 300, INT_MAX, INT_MAX,  300, 0, 650},
    {INT_MAX, 1400, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,INT_MAX, 650, 0}
};


    // Applying Floyd-Warshall algorithm
    floydWarshall(graph);
    return 0;
}
