#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert suffix_array.cpp code

vector<int> lcp(string s, SuffixArray suf_arr) {
    int n = s.size();
    vector<int> rank(n); // stores the rank/index of a suffix in the suffix array
    for (int i = 0; i < n; ++i) {
        rank[suf_arr.get_suffix(i)] = i;
    }

    /* Go through the suffix array and calculate the LCP between each
    pair of consecutive suffixes. */
    int k = 0;
    vector<int> lcp_arr(n - 1);
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suf_arr.get_suffix(rank[i] + 1);
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) {
            ++k;
        }
        lcp_arr[rank[i]] = k;
        if (k > 0) --k;
    }
    return lcp_arr;
}
