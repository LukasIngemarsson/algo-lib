#include <bits/stdc++.h>
using namespace std;

vector<int> knuth_morris_pratt(string s, string p) {
    int n = p.size();

    /* Precalculate the prefix vector which will contain the index to resume 
    pattern-searching from if the pattern matches up to that character,
    but fails after. */
    vector<int> pfx(n);
    for (int i = 1; i < n; ++i) {
        int j = pfx[i-1];
        while (j > 0 && p[i] != p[j]) {
            j = pfx[j-1];
        }
        if (p[i] == p[j]) ++j;
        pfx[i] = j;
    }

    /* Search for pattern. */
    vector<int> matches; // stores the start index of matches
    int pos = 0; // index position in the pattern
    for (int i = 0; i < s.size(); ++i) {
        while (pos > 0 && p[pos] != s[i]) {
            pos = pfx[pos-1];
        }
        if (p[pos] == s[i]) ++pos;

        if (pos == n) {
            matches.push_back(i - (n - 1));
            pos = pfx[pos-1];
        }
    }

    return matches;
}
