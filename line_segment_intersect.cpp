// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp code

#define EPS 1e-9
typedef Point<double> P;

/* Checks if the given point lies on the given line segment. */
bool on_segment(const P& s, const P& e, const P& p) {
    // check if `p` is colinear with segment `s->e`
    if (abs((e - s).cross(p - s)) > EPS) return false;

    // check if `p` lies on the segment `s->e`
    return (p - s).dot(p - e) <= EPS;
}

int sgn(double d) {
    return (d > EPS) - (d < -EPS);
}

vector<P> line_seg_intersect(const P& s1, const P& e1, const P& s2, const P& e2) {
    double o1 = (e2 - s2).cross(s1 - s2);
    double o2 = (e2 - s2).cross(e1 - s2);
    double o3 = (e1 - s1).cross(s2 - s1);
    double o4 = (e1 - s1).cross(e2 - s1);

    if (sgn(o1) * sgn(o2) < 0 && sgn(o3) * sgn(o4) < 0) {
        P intersect_pt = (s1 * o2 - e1 * o1) / (o2 - o1);
        return { intersect_pt };
    }

    set<P> intersect_pts;
    if (on_segment(s2, e2, s1)) intersect_pts.insert(s1);
    if (on_segment(s2, e2, e1)) intersect_pts.insert(e1);
    if (on_segment(s1, e1, s2)) intersect_pts.insert(s2);
    if (on_segment(s1, e1, e2)) intersect_pts.insert(e2);

    return vector<P>(intersect_pts.begin(), intersect_pts.end());
}
