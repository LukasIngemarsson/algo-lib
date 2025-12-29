// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<ll, int>> prime_factorize(ll n, const vector<ll>& primes) {
    vector<pair<ll, int>> pfs;

    for (ll p : primes) {
        if (p * p > n) break;

        if (n % p == 0) {
            int exp = 0;
            while (n % p == 0) {
                n /= p;
                ++exp;
            }
            pfs.emplace_back(p, exp);
        }
    }
    if (n > 1) pfs.emplace_back(n, 1);

    return pfs;
}

