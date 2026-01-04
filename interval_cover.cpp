#include <bits/stdc++.h>
using namespace std;

vector<int> interval_cover(pair<double, double> target, vector<vector<double>> intervals) {
    sort(intervals.begin(), intervals.end());

    double curr_cov = target.first; // current coverage (up to curr_cov)
    vector<int> idxs;
    int i = 0;
    while (curr_cov < target.second || i == 0) { // the condition i == 0 handles the case where A == B
        pair<double, int> opt = {curr_cov, -1}; // {start, index} of opt interval that can extend our coverage
        for (; i < intervals.size() && intervals[i][0] <= curr_cov; ++i) {
            opt = max(opt, {intervals[i][1], intervals[i][2]});
        }
        if (opt.second == -1) { // no remaining intervals can improve our coverage
            idxs.clear();
            break;
        }
        idxs.push_back(opt.second);
        curr_cov = opt.first;
    }

    return idxs;
}
