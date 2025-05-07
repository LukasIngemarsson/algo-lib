// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
A class for rational numbers, supporting common arithmetic 
operations and comparison operators. Initialization defaults
to numerator = 0 and denominator = 1.
*/
struct RationalArithmetic {
    ll n, d;

    RationalArithmetic() : n(0), d(1) {}
    
    RationalArithmetic(ll n, ll d) : n(n), d(d) {
        normalize();
    }

    /* Finds the greatest commmon divisor (GCD) for two integers. */
    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    /* Normalizes the rational number, i.e., divides it by the factors 
    shared by the numerator and denominator. */
    void normalize() {
        ll g = gcd(abs(n), abs(d));
        n /= g; 
        d /= g;
        if (d < 0) {
            n *= -1;
            d *= -1;
        }
    }

    /* --- Operations --- */

    RationalArithmetic operator+(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d + other.n * d, d * other.d);
    }

    RationalArithmetic operator-(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d - other.n * d, d * other.d);
    }

    RationalArithmetic operator*(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.n, d * other.d);
    }

    RationalArithmetic operator/(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d, d * other.n);
    }

    /* --- Comparison operators --- */

    bool operator<(const RationalArithmetic& other) const {
        return n * other.d < other.n * d;
    }

    bool operator>(const RationalArithmetic& other) const {
        return n * other.d > other.n * d;
    }

    bool operator<=(const RationalArithmetic& other) const {
        return n * other.d <= other.n * d;
    }
    
    bool operator>=(const RationalArithmetic& other) const {
        return n * other.d >= other.n * d;
    }

    bool operator==(const RationalArithmetic& other) const {
        return n * other.d == other.n * d;
    }

    bool operator!=(const RationalArithmetic& other) const {
        return n * other.d != other.n * d;
    }

    /* --- Input and output --- */

    friend istream& operator>>(istream& in, RationalArithmetic& r) {
        in >> r.n >> r.d;
        r.normalize();
        return in;
    }

    friend ostream& operator<<(ostream& out, const RationalArithmetic& r) {
        out << r.n << " / " << r.d;
        return out;
    }
};
