#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a Disjoint Set (Union-Find)
struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, each node is its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find function with Path Compression
    int find(int i) {
        if (parent[i] != i)
            parent[i] = find(parent[i]);
        return parent[i];
    }

    // Union function by Rank
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Comparator to sort edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

void kruskalMST(int V, vector<Edge>& edges) {
    // Step 1: Sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compareEdges);

    DSU dsu(V);
    vector<Edge> mst; // To store the result MST
    int mstWeight = 0;

    cout << "\nRunning Kruskal's Algorithm...\n";

    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;

        // Step 2: Check if the current edge forms a cycle
        // If u and v are in different sets, include this edge
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            mst.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    cout << "Src -- Dest == Weight\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (Source Destination Weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    kruskalMST(V, edges);

    return 0;
}
