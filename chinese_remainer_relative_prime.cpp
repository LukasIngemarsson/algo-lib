#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// NOTE: Insert modular_arithmetic.cpp code

ll chinese_remainder_relative_prime(ll a, ll b, ll n, ll m) {
    ModularArithmetic ma(m);
    ll n1 = ma.inv(n);
    ma.set_mod(n);
    ll n2 = ma.inv(m);

    ll K = n * m;
    ma.set_mod(K);

    // x = (a * n2 * m + b * n1 * n) % K
    return (ma.mult(ma.mult(a, n2), m) + ma.mult(ma.mult(b, n1), n)) % K;
}
