// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

// NOTE: Insert fast_fourier_transform.cpp code

vector<int> poly_mult(vector<int>& a, vector<int>& b) {
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
