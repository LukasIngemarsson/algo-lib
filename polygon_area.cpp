// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

template <typename T>
double polygon_area(const vector<Point<T>>& pts) {    
    double res = 0;
    int n = pts.size();

    for (int i = 0; i < n; ++i) {
        Point<T> a = pts[i], b = pts[(i + 1) % n];
        res += (a.x - b.x) * (b.y + a.y);
    }
    return res / 2;
}
