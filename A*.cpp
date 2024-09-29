#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

#define V 14

// Structure to represent a weighted edge in the graph
struct Edge {
    int dest, weight;
};

// Structure to represent a vertex in the graph
struct Vertex {
    int id, f, g; // f = g + h
};

// Custom comparator for priority queue
struct CompareVertex {
    bool operator()(const Vertex& v1, const Vertex& v2) {
        return v1.f > v2.f; // Priority queue with smallest f value at the top
    }
};

// A* algorithm to find shortest path from source to destination
void astar(int graph[V][V], int src, int dest) {
    std::priority_queue<Vertex, std::vector<Vertex>, CompareVertex> pq;
    std::vector<int> g(V, INT_MAX); // Actual cost from source to vertex
    std::vector<int> h(V, INT_MAX); // Heuristic cost from vertex to destination
    std::vector<int> parent(V, -1); // To store parent of each vertex

    g[src] = 0; // Start vertex
    h[src] = 0; // Heuristic for start vertex (can be modified)

    pq.push({src, h[src], g[src]}); // Push start vertex to priority queue

    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        if (current.id == dest) { // If destination is reached, break
            break;
        }

        for (int i = 0; i < V; ++i) {
            if (graph[current.id][i] != 0) {
                int cost = graph[current.id][i];
                int new_g = g[current.id] + cost;
                int new_f = new_g + h[i];

                if (new_f < g[i] + h[i]) { // If new path is better
                    g[i] = new_g;
                    parent[i] = current.id;
                    pq.push({i, new_f, new_g});
                }
            }
        }
    }

    // Print the path from source to destination
    int current = dest;
    std::vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    // If path exists
    if (path.back() == src) {
        std::cout << "Shortest path from " << src << " to " << dest << " is: ";
        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i != 0) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Path from " << src << " to " << dest << " does not exist.\n";
    }
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

    cout <<"Enter the Source Node: ";
    int src ;
    cin>>src;
    for(int i=1;i<=13;i++){
        int dest = i;
        astar(graph, src, dest);
    }
    return 0;
}



