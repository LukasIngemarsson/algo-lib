// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

pair<Point<double>, Point<double>> closest_pair_uniform(vector<Point<double>> pts) {
    int n = pts.size();

    sort(pts.begin(), pts.end());

    pair<Point<double>, Point<double>> closest{pts[0], pts[1]}; 
    double min_dist = closest.first.dist_to(closest.second);
    for (int i = 2; i < n; ++i) {
        Point<double> pt1 = pts[i];

        for (int j = i - 1; j >= 0; --j) {
            Point<double> pt2 = pts[j];
            double dist = pt1.dist_to(pt2);

            if (dist < min_dist) {
                min_dist = dist;
                closest = {pt1, pt2};
            }
            else if ((pt1.x - pt2.x) > min_dist) {
                break;
            }
        }
    }

    return closest;
}
