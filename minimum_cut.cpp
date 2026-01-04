#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert edmonds_karp.cpp code

void dfs(const Graph& G, int u, unordered_set<int>& U) {
    U.insert(u);
    for (int v : G.adj[u]) {
        if (G.cap[u][v] > 0 && U.find(v) == U.end()) {
            dfs(G, v, U);
        }
    }
}

unordered_set<int> min_cut(Graph& G, int s, int t) {
    edmonds_karp(G, s, t);
    unordered_set<int> U;
    dfs(G, s, U);
    return U;
}
