// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

struct PrimeSieve {
    int num_primes = 0;
    vector<bool> v; // stores if a number is prime or not

    PrimeSieve(int n) : v(n + 1, true) {
        v[0] = false, v[1] = false;
        int sqrt_n = floor(sqrt(n));
        for (int i = 2; i <= n; ++i) {
            if (v[i]) {
                ++num_primes;
                if (i > sqrt_n) continue;

                // we can start from i^2 since smaller multiples of i 
                // necessarily must have been marked by smaller prime factors
                for (int j = i * i; j <= n; j += i) {
                    v[j] = false;
                }
            }
        }
    }

    int get_num_primes() { return num_primes; }

    bool is_prime(int i) { return v[i]; }
};
