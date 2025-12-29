// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

vector<int> lis(vector<int>& nums) { 
    vector<int> seq; // stores the current ascending set of numbers
    vector<int> idxs; // stores the index of the corresponding numbers in seq
    vector<int> parent(nums.size(), -1); // stores the index of the parent of a number/element

    for (int i = 0; i < nums.size(); ++i) {
        // binary search to find index of the first number currently in the sequence,
        // that is not less than the candidate number nums[i]
        int pos = lower_bound(seq.begin(), seq.end(), nums[i]) - seq.begin();
        if (pos == seq.size()) { // no number in the current sequence is >= the candidate num
            seq.push_back(nums[i]);
            idxs.push_back(i);
        }
        else {
            seq[pos] = nums[i];
            idxs[pos] = i;
        }
        if (pos > 0) {
            parent[i] = idxs[pos-1];
        }
    }

    vector<int> lis_idxs;
    for (int i = idxs.back(); i >= 0; i = parent[i]) {
        lis_idxs.push_back(i);
    }
    reverse(lis_idxs.begin(), lis_idxs.end());

    return lis_idxs;
}
