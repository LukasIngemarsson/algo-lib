// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef complex<double> cd;
#define PI acos(-1)

/*
@brief Applies the Fast Fourier Transform (FFT) or its inverse on the given vector of complex numbers.

@param v: A vector of complex numbers (e.g., coefficients of a polynomial).
@param inv: A boolean value indicating if the inverse (true) or regular (false) FFT should be applied. 
It defaults to false.

@note Time complexity: `O(n * log(n))`, where `n` is the size of the vector.
@note The transform is done in-place, i.e., the input object `v` will be altered.
*/
void fft(vector<cd>& v, bool inv=false) {
    int n = v.size();
    if (n == 1) return; // cannot divide further

    // divide `v` into two parts,
    // one containing the elements at even indices,
    // and the other containing those at odd indices
    vector<cd> a(n / 2), b(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        a[i] = v[2 * i];
        b[i] = v[2 * i + 1];
    }
    // then we recursively compute the FFT for the smaller vectors
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

