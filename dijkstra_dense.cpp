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

