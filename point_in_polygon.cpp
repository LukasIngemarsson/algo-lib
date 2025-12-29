// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

template <typename T>
int inside_polygon(const Point<T>& p, const vector<Point<T>> polygon) {
    int num_verts = polygon.size();

    for (int i = 0; i < num_verts; ++i) {
        Point<T> a = polygon[i];
        Point<T> b = polygon[(i + 1) % num_verts];

        if ((b - a).cross(p - a) == 0) {
            bool between_x = p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x);
            bool between_y = p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);

            if (between_x && between_y) return 0;
        }
    }

    double ang = 0;
    for (int i = 0; i < num_verts; ++i) {
        Point<T> a = polygon[i];
        Point<T> b = polygon[(i + 1) % num_verts];

        double theta1 = (a - p).angle();
        double theta2 = (b - p).angle();
        double theta_diff = theta2 - theta1;

        while (theta_diff > M_PI) {
            theta_diff -= 2 * M_PI;
        }
        while (theta_diff <= -M_PI) {
            theta_diff += 2 * M_PI;
        }
        ang += theta_diff;
    }

    return (abs(ang) < M_PI) ? -1 : 1; 
}
