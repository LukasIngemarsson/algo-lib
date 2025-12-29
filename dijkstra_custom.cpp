// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF 1e9

/* Replace the parameters and logic of Edge and Graph depending on use case. */

struct Edge {
    int v, w;

    Edge(int v, int w) : v(v), w(w) {}

    int calc_weight(int t) { // custom weight (dependent on other parameters)
        // int tot_w = ...
        // return tot_w;
    }
};

struct Graph {
    vector<vector<Edge>> adj; // adjacency list

    Graph(int n) : adj(n) {}

    void add_edge(int u, int v, int w=1) {
        adj[u].push_back(Edge(v, w));
    }
};

pair<vi, vi> dijkstra_custom(Graph& G, int st) { 
    int n = G.adj.size();

    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    set<pii> q;
    q.insert({0, st});
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : G.adj[u]) {
            int v = edge.v, w = edge.calc_weight(dis[u]);
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                q.insert({dis[v], v});
            }
        }
    }
    return {dis, par};
}

