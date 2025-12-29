// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    vector<int> arr;

    SuffixArray(string s) {
        // append string with arbitrary symbol that is lexicographically 
        // smaller than the all characters in the input data
        s += '\t'; // ascii value 9

        int n = s.size();
        const int alphabet = 256;

        /* Start by sorting suffixes only considering the first character of each suffix. */
        arr.resize(n);
        vector<int> c(n); // stores equivalence classes for suffix starting indices
        vector<int> cnt(max(alphabet, n));

        // count char frequencies
        for (int i = 0; i < n; ++i) {
            ++cnt[s[i]];
        }
        // calculate cumulative sum
        for (int i = 1; i < alphabet; ++i) {
            cnt[i] += cnt[i-1];
        }
        // populates the suffix array sorted by single-char prefixes
        for (int i = 0; i < n; ++i) {
            arr[--cnt[s[i]]] = i;
        }

        // assign initial class IDs to suffixes
        c[arr[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[arr[i]] != s[arr[i-1]]) ++classes;
            c[arr[i]] = classes - 1;
        }

        /* Iteratively sort suffixes, doubling prefix lengths after each iteration. 
        At each iteration, the class array `c` and suffix array `arr` contain the 
        results from the previous iteration, and temporary vectors are used to 
        store the results from the current iteration. */
        vector<int> tmp_arr(n), tmp_c(n);

        // in each iteration, sort suffixes based on their first `k` characters
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; ++i) {
                tmp_arr[i] = arr[i] - k; // shift
                if (tmp_arr[i] < 0) tmp_arr[i] += n; // wrap-around
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);
            // count prefix frequencies
            for (int i = 0; i < n; ++i) {
                ++cnt[c[tmp_arr[i]]];
            }
            // calculate cumulative sum
            for (int i = 1; i < classes; ++i) {
                cnt[i] += cnt[i-1];
            }
            // insert suffixes into array sorted by prefix
            for (int i = n - 1; i >= 0; --i) {
                arr[--cnt[c[tmp_arr[i]]]] = tmp_arr[i];
            }

            // assign new class IDs for the new prefix length
            tmp_c[arr[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i) {
                if (c[arr[i]] != c[arr[i-1]] || c[(arr[i] + k) % n] != c[(arr[i-1] + k) % n]) {
                    ++classes;
                }
                tmp_c[arr[i]] = classes - 1;
            }
            c.swap(tmp_c);
        }
        arr.erase(arr.begin()); // remove symbol
    }

    int get_suffix(int i) {
        return arr[i];
    }
};
