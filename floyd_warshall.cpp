// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
#define INF (int)1e9

/*
@brief Calculates the shortest path between each pair of nodes in the given adjacency matrix, 
using the Floyd-Warshall algorithm.

@param adj: An adjacency matrix containing the weight of each edge that exists in the graph, 
filled with `INF` if no edge exists between two nodes.

@return A matrix containing the shortest path between each node pair. If no shortest path exists 
between two nodes, their cell will contain `INF`, and if an arbitrarily short path exists due 
to a negative cycle, their cell will contain `-INF`.

@note Time complexity: `O(n ^ 3)`, where `n` is the number of nodes in the graph.
*/
vvi sp_all_pairs(vvi adj) {
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
