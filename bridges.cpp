#include <bits/stdc++.h>
using namespace std;

vector<bool> vis;
vector<int> tin, low;
int timer;
vector<pair<int, int>> bridges;

void dfs(int v, const vector<vector<int>>& adj, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : adj[v]) {
        if (to == p and !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        }
        else {
            dfs(to, adj, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                bridges.push_back({min(v, to), max(v, to)});
        }
    }
}

void find_bridges(const vector<vector<int>>& adj) {
    int n = adj.size();
    vis.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    timer = 1;
    bridges.clear();
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            dfs(i, adj);
    }
}

