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

