// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef complex<double> cd;
#define PI acos(-1)

/*
@brief Applies the Fast Fourier Transform (FFT) to the given polynomial.

@param v: A vector containing the polynomial's coefficients.
@param inv: A boolean value indicating if the inverse or regular FFT should be applied. 
It defaults to `false`.

@note Time complexity: `O(nlog(n))`, where `n` is the order of the polynomial.
@note The transform is done in-place, i.e., the input object `v` will be altered.
*/
void fft(vector<cd>& v, bool inv=false) {
    int n = v.size();
    if (n == 1) return; // cannot divide further

    // divide polynomial into two smaller polynomials,
    // one containing the coefficients at even indices,
    // and the other containing those at odd indices
    vector<cd> a(n / 2), b(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        a[i] = v[2 * i];
        b[i] = v[2 * i + 1];
    }
    // then we recursively compute the FFT for the smaller polynomials
    fft(a, inv);
    fft(b, inv);

    double ang = (2 * PI / n) * ((inv) ? -1 : 1);
    cd wn(cos(ang), sin(ang)); // w = e ^ (i * ang) = cos(ang) + i * sin(ang)
    cd w(1); // start at w ^ 0 = 1 + 0 * i
    for (int k = 0; k < n / 2; ++k) {
        // calculate the values for the positive-negative pair w ^ k and w ^ (k + n / 2)
        v[k] = a[k] + w * b[k]; 
        v[k + n / 2] = a[k] - w * b[k];
        if (inv) {
            // will be done in each level of recursion,
            // effectively dividing the final values by n
            v[k] /= 2;
            v[k + n / 2] /= 2;
        }
        w *= wn; // move to next pair
    }
}

/*
@brief Multiplies two given polynomials using the FFT.

@param a: The coefficients of the first polynomial.
@param b: The coefficients of the second polynomial.

@return The coefficients of the resulting polynomial.

@note Time complexity: `O(nlog(n))`, where `n` is the order of the resulting polynomial.
*/
vector<int> mult_poly(vector<int>& a, vector<int>& b) {
    /*
    The naive approach for polynomial multiplication takes `O(n^2)` time, as we have to
    multiply each pair of coefficients in the two polynomials. This can be improved 
    by applying the FFT to the two polynomials, and multiplying the representations in 
    the frequency domain instead.
    */

    // polynomials are represented using complex numbers
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int num_coeffs = a.size() + b.size() - 1; // number of coefficients in the result

    // find the first power of 2 that exceeds the number of coefficients
    // in the resulting polynomial, since this convenitently matches the 
    // divide-and-conquer approach of the FFT
    int n = 1; // "overshoot" degree
    while (n < num_coeffs) {
        n <<= 1;
    }
    // resize the polynomials to the "overshoot" degree
    fa.resize(n); 
    fb.resize(n);

    // apply the FFT to both polynomials
    fft(fa);
    fft(fb);
    // in the frequency domain, we can directly multiply each entry 
    // from the respective polynomial Fourier representations.
    for (int i = 0; i < n; ++i) {
        fa[i] *= fb[i];
    }
    fft(fa, true); // recover polynomial coefficients after FFT multiplication

    // store the resulting polynomial, discarding the coefficients for excess
    // degrees that follow from the "overshoot" degree
    vector<int> result(num_coeffs);
    for (int i = 0; i < num_coeffs; ++i) {
        result[i] = round(fa[i].real()); // handle complex number error
    }
    return result;
}
