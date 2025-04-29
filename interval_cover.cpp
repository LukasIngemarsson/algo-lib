// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

/*
@brief Finds the minimal set of the given intervals that covers the desired target interval.

@param target: A (start, end)-pair of the interval to be covered.
@param intervals: A vector of interval (start, end)-pairs.

@return A vector with the indices of the chosen intervals, if a valid solution exists.
Otherwise, it returns an empty vector.

@note Time complexity: `O(nlog(n))`, where `n` is the number of intervals.
*/
vector<int> cover(pair<double, double> target, vector<vector<double>> intervals) {
    sort(intervals.begin(), intervals.end()); // O(nlog(n))

    double curr_cov = target.first; // current coverage (up to curr_cov)
    vector<int> idxs;
    int i = 0;
    // this while-loop is O(n), since we will only consider each interval at most once
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
