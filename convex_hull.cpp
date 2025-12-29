// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

template <typename T>
vector<Point<T>> convex_hull(vector<Point<T>> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    int n = pts.size();

    if (n <= 2) return pts;

    vector<Point<T>> res(2 * n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && (res[k-1] - res[k-2]).cross(pts[i] - res[k-2]) <= 0) --k;
        res[k++] = pts[i];
    }
    int lhk = k; // lower hull last index
    for (int i = n - 2; i >= 0; --i) {
        while (k > lhk && (res[k-1] - res[k-2]).cross(pts[i] - res[k-2]) <= 0) --k;
        res[k++] = pts[i];
    }
    
    res.resize(k - 1);

    return res;
}
