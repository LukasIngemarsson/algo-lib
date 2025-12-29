// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void calc_divs_(int idx, ll div, const vector<pair<ll, int>>& pfs, vector<ll>& divs) {
    if (idx == pfs.size()) {
        divs.push_back(div);
        return;
    }

    auto [p, exp] = pfs[idx];
    for (int i = 0; i <= exp; ++i) {
        calc_divs_(idx + 1, div, pfs, divs);
        div *= p;
    }
}

vector<ll> calc_divs(const vector<pair<ll, int>>& pfs) {
    vector<ll> divs;
    calc_divs_(0, 1, pfs, divs);
    return divs;
}
