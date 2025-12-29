// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct FenwickTree {
    int n; // tree size
    vector<ll> tree; // stores the tree values

    FenwickTree(int n) : n(n), tree(n + 1) {}

    // O(n) init
    FenwickTree(vector<ll> v) : n(v.size()), tree(v.size() + 1) {
        copy(v.begin(), v.end(), tree.begin() + 1); // 1-indexed
        for (int i = 1; i <= n; ++i) {
            int par = i + (i & -i);
            if (par <= n) {
                tree[par] += tree[i];
            }
        }
    }

    void add(int i, int d) { 
        // after each iteration, add the last set bit to i
        for (; i <= n; i += i & -i) { 
            tree[i] += d;
        }
    }

    ll sum(int i) {
        ll sum = 0;
        // after each iteration, subtract the last set bit from i
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }

    ll sum(int i, int j) {
        return sum(j) - sum(i - 1);
    }
};
