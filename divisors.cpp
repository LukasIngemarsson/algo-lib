#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
@brief Gets the prime factorization for a given number.

@param n: The number to factorize.
@param primes: The prime numbers up to the square root of `n`.

@return The prime factorization in the form of (prime factor, exponent) pairs.

@note The primes can suggestively be found using a Prime Sieve.
*/
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

void gen_divs(int idx, ll div, const vector<pair<ll, int>>& pfs, vector<ll>& divs) {
    if (idx == pfs.size()) {
        divs.push_back(div);
        return;
    }

    auto [p, exp] = pfs[idx];
    for (int i = 0; i <= exp; ++i) {
        gen_divs(idx + 1, div, pfs, divs);
        div *= p;
    }
}

/*
@brief Calculates all the divisors of a number given its prime factorization.

@param pfs: A vector containing (prime factor, exponent) pairs.

@return A vector containing the divisors.
*/
vector<ll> calc_divs(const vector<pair<ll, int>>& pfs) {
    vector<ll> divs;
    gen_divs(0, 1, pfs, divs);
    return divs;
}
