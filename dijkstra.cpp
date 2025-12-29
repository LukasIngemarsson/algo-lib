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

pair<vi, vi> dijkstra(Graph& G, int st) { 
    int n = G.adj.size();

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    set<pii> q;
    q.insert({0, st});
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.first, w = edge.second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.insert({dis[v], v});
            }
        }
    }
    return {dis, par};
}

