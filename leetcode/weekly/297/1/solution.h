/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

typedef pair<int, int> pii;
class Solution {
   public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = grid.size(), m = grid[0].size();
        const int inf = numeric_limits<int>::max() / 2;
        vector dp = vector(n, vector(m, inf));
        for (int i = 0; i < m; i++) {
            dp[0][i] = grid[0][i];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j] + moveCost[grid[i - 1][k]][j]);
                }
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};