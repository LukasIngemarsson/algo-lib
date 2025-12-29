// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef vector<double> vd;
#define EPS 1e-9

pair<int, vd> gaussian_elimination_partial(vector<vd> A, vd b) {
    int n = A.size(), m = A[0].size();
    vector<int> pivot_rows(m, -1); // stores the index of the pivot row for each column
    for (int r = 0, c = 0; r < n && c < m; ++c) {
        // select the row with the largest absolute value
        int sel = r;
        for (int i = r + 1; i < n; ++i) {
            if (abs(A[i][c]) > abs(A[sel][c])) {
                sel = i;
            }
        }
        if (abs(A[sel][c]) < EPS) continue;

        // swap selected row with the current row
        for (int i = c; i < m; ++i) {
            swap(A[sel][i], A[r][i]);
        }
        swap(b[sel], b[r]);
        pivot_rows[c] = r;

        // turn the elements in the current column to zeros, except for the pivot element
        for (int i = 0; i < n; ++i) {
            if (i == r) continue;

            double k = A[i][c] / A[r][c];
            A[i][c] = 0; // set manually for preciseness
            for (int j = c + 1; j < m; ++j) {
                A[i][j] -= A[r][j] * k;
            }
            b[i] -= b[r] * k;
        }
        ++r;
    }

    vd x(m);
    for (int i = 0; i < m; ++i) {
        if (pivot_rows[i] == -1) continue;
        
        x[i] = b[pivot_rows[i]] / A[pivot_rows[i]][i];
    }
    
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += x[j] * A[i][j];
        }

        if (abs(sum - b[i]) > EPS) {
            return {0, vd()};
        }
    }

    // check for free variables
    for (int i = 0; i < m; ++i) {
        int r = pivot_rows[i];
        if (r == -1) {
            x[i] = NAN;
            continue;
        }
        for (int j = i + 1; j < m; ++j) {
            if (abs(A[r][j]) > EPS) {
                x[i] = NAN;
                break;
            }
        }
    }

    return {1, x};
}
