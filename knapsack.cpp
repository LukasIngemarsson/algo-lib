#include <bits/stdc++.h>
using namespace std;

vector<int> knapsack(int capacity, vector<pair<int, int>>& items) {
    int n = items.size();
    // dp table that stores the max combined value for placing 
    // i items (row) with a combined weight j (col)
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1));

    for (int i = 0; i <= n; ++i) {
        for (int maxw = 0; maxw <= capacity; ++maxw) {
            if (i == 0 || maxw == 0) { // no item/weight
                dp[i][maxw] = 0;
                continue;
            }
            int v = items[i-1].first, w = items[i-1].second;
            if (w <= maxw) {
                // set max value of choosing / not choosing the item
                dp[i][maxw] = max(v + dp[i-1][maxw-w], dp[i-1][maxw]);
            }
            else { // exceeds capacity, can't place item
                dp[i][maxw] = dp[i-1][maxw];
            }
        }
    }

    vector<int> idxs;
    // the capacity variable is re-used here as "capacity remaining"
    for (int i = n; i > 0 && capacity > 0; --i) { 
        if (dp[i][capacity] != dp[i-1][capacity]) {
            idxs.push_back(i-1);
            capacity -= items[i-1].second;
        }
    }

    return idxs;
}
