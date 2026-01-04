#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi reconstruct_shortest_path(vi& par, int st, int end) {
    vi path;
    for (int u = end; u != st; u = par[u]) {
        if (u == -1) {
            return vi();
        }
        path.push_back(u);
    }
    path.push_back(st);

    reverse(path.begin(), path.end()); 
    return path;
}
