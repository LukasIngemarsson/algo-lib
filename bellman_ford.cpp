// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define INF (int)1e9

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

pair<vi, vi> bellman_ford(int n, vector<Edge>& edges, int st) {
    vi dis(n, INF), par(n, -1);
    dis[st] = 0;
    for (int i = 0; i < 2 * (n - 1); ++i) {
        bool any = false;
        for (auto& e : edges) {
            if (dis[e.u] < INF && dis[e.u] + e.w < dis[e.v]) {
                dis[e.v] = (i < n - 1) ? dis[e.u] + e.w : -INF;
                par[e.v] = e.u;
                any = true;
            }
        }
        if (!any) { // stop early if no improvements are found
            break;
        }
    }
    return {dis, par};
}

