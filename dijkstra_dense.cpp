// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

struct Graph {
    vector<vector<pii>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int w=1) {
        adj[u].push_back({v, w});
    }
};

/* 
@brief Dijkstra's algorithm. Finds the shortest path from the given 
start node to all other nodes in the given non-negative-weight graph.

@param G: The graph.
@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector 
with the immediate parent of each node in their shortest path.

@note Time complexity: `O(n^2 + m)`, where `m` is the number of edges and `n` is the number 
of nodes in the graph.
@note Good for dense graphs (when `m` approaches `n^2`, i.e., almost all possible edges exist).
*/
pair<vi, vi> dijkstra_dense(Graph& G, int st) { 
    int n = G.adj.size();

    vi dis(n, INF); // stores shorest distance from st to all nodes
    vi par(n, -1); //  stores the parent node that is used to reach each node in its shortest path
    vector<bool> vis(n, false);

    dis[st] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && (u == -1 || dis[j] < dis[u])) {
                u = j;
            }
        }
        if (dis[u] == INF) break;

        vis[u] = true;
        for (auto edge : G.adj[u]) {
            int v = edge.first, w = edge.second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
            }
        }
    }
    return {dis, par};
}

/*
@brief Reconstructs the shortest path from the given start to end node.

@param par: A vector containing the immediate parent of each node in 
their shortest path, which can be backtracked to retreive the full path.

@return A vector containing the shortest path in the order from start to end. 
This vector is empty if no shortest path exists for the start-end pair.
*/
vi reconstruct_shortest_path(vector<int>& par, int st, int end) {
    vi path;
    for (int u = end; u != st; u = par[u]) {
        if (u == -1) {
            return vi();
        }
        path.push_back(u);
    }
    path.push_back(st);

    reverse(path.begin(), path.end()); 
    return path;
}
