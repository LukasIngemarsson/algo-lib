#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
#define INF (int)1e9

vvi floyd_warshall(vvi adj) {
    vvi d = adj;
    int n = d.size();

    // before the k-th phase, d[i][j] for any nodes i and j stores
    // the length of the shortest path between i and j, only using vertices 
    // {0, 1, ..., k - 1} as internal nodes in the path
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (d[i][k] >= INF) continue;
            for (int j = 0; j < n; ++j) {
                if (d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // handle negative cycles
    for (int k = 0; k < n; ++k) {
        if (d[k][k] >= 0) {
            continue;
        }
        // negative cycle detected, update all affected pairs of nodes
        for (int i = 0; i < n; ++i) {
            if (d[i][k] >= INF) continue;
            for (int j = 0; j < n; ++j) {
                if (d[k][j] < INF) d[i][j] = -INF;
            }
        }
    }

    return d;
}
