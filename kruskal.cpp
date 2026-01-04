#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert union_find.cpp code

typedef long long ll;

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

pair<ll, vector<Edge>> mst(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    ll cost = 0;
    vector<Edge> res;
    for (Edge& e : edges) {
        if (!uf.same(e.u, e.v)) {
            cost += e.w;
            res.push_back(e);
            uf.union_(e.u, e.v);

            if (res.size() == n - 1)
                break;
        }
    } 
    if (res.size() < n - 1) { // no valid MST
        return {-1, vector<Edge>()};
    }
    return {cost, res};
}
