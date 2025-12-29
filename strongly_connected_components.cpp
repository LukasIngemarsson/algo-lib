// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;

void dfs(int st, vector<vector<int>>& adj, vector<int>& output) {
    visited[st] = true;
    for (auto u : adj[st]) {
        if (!visited[u]) {
            dfs(u, adj, output);
        }
    }
    output.push_back(st);
}

pair<vector<vector<int>>, vector<vector<int>>> scc(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> order; 

    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, order);
        }
    }

    // create the graph's transposed adjacency list
    vector<vector<int>> rev_adj(n);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            rev_adj[v].push_back(u);
        }
    }

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<vector<int>> components;
    vector<int> roots(n, 0); // stores the root node of a node's SCC
    for (auto u : order) {
        if (!visited[u]) {
            vector<int> comp;
            dfs(u, rev_adj, comp);
            components.push_back(comp);
            int root = *min_element(comp.begin(), comp.end());
            for (auto v : comp) {
                roots[v] = root;
            }
        }
    }

    // create condensation adjacency list
    vector<vector<int>> cond_adj(n);
    for (int u = 0; u < n; ++u) {
        for (auto v : adj[u]) {
            if (roots[u] != roots[v]) {
                cond_adj[roots[u]].push_back(roots[v]);
            }
        }
    }

    return {components, cond_adj};
}
