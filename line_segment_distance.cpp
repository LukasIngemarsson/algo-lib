// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert point.cpp and line_segment_intersect.cpp code

#define EPS 1e-9
typedef Point<double> P;

/* Calculates the minimum distance from the given line segment to the given point. */
double line_seg_dist_to_pt(const P& s, const P& e, const P& p) {
    P seg_vect = e - s;

    double seg_len_sq = seg_vect.dot(seg_vect);

    // check if the segment is simply a point (length == 0)
    if (seg_len_sq < EPS * EPS) return (p - s).norm();

    // calculate the projection parameter `t` of point `p` onto the infinite
    // line that is colinear with segment `s->e`, and clamp the value between
    // 0 and 1 (as we can only select a point that lies on the segment)
    double t = max(0.0, min(1.0, (p - s).dot(seg_vect) / seg_len_sq));
    P closest_pt = s + t * seg_vect;

    return (p - closest_pt).norm();
}

double line_seg_dist(const P& s1, const P& e1, const P& s2, const P& e2) {
    if (line_seg_intersect(s1, e1, s2, e2).size() > 0) return 0.0;

    double d1 = line_seg_dist_to_pt(s1, e1, s2);
    double d2 = line_seg_dist_to_pt(s1, e1, e2);
    double d3 = line_seg_dist_to_pt(s2, e2, s1);
    double d4 = line_seg_dist_to_pt(s2, e2, e1);

    return min({d1, d2, d3, d4});
}
