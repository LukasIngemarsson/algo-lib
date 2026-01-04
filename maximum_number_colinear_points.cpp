#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

template <typename T>
int max_num_colinear_pts(const vector<Point<T>>& pts) {
    int n = pts.size();

    if (n == 1) return 1;

    int max_cnt = 1;
    for (int i = 0; i < n; ++i) {
        Point<T> o = pts[i];

        vector<double> angs;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;

            double a = atan2(pts[j].y - o.y, pts[j].x - o.x);
            if (a < 0) a += M_PI; // normalize angle to be within [0, PI)
            angs.push_back(a);
        }
        sort(angs.begin(), angs.end());

        int cnt = 1;
        double cur_ang = angs.front();
        for (int j = 1; j < angs.size(); ++j) {
            if (angs[j] != cur_ang) {
                max_cnt = max(max_cnt, cnt);
                cur_ang = angs[j];
                cnt = 1;
            }
            else {
                ++cnt;
            }
        }
        max_cnt = max(max_cnt, cnt);
    }

    return max_cnt + 1; // +1 to account for the origin / reference point itself
}
