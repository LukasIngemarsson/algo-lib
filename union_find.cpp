// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent; // create a tree structure for each set, where an element points to a parent
    vector<int> rank; // stores the rank of a tree at the root index
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    } 

    int find(int a) {
        if (parent[a] != a) {
            // update parent to root for each element that we find while climbing the tree (path compression)
            parent[a] = find(parent[a]);
        }
        return parent[a];
    }

    void union_(int a, int b) {
        int a_root = find(a), b_root = find(b);
        if (a_root == b_root) {
            return;
        }
        // decide which tree attaches to the other based on their rank
        if (rank[a_root] < rank[b_root]) {
            parent[a_root] = parent[b_root];
        }
        else if (rank[a_root] > rank[b_root]) {
            parent[b_root] = parent[a_root];
        }
        else {
            parent[a_root] = parent[b_root];
            ++rank[b_root];
        }
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};
