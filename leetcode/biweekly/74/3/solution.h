/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

class Solution {
   public:
    vector<vector<int>> dp;
    vector<int> sum;
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size();
        dp.resize(n + 1, vector<int>(numCarpets + 1));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= numCarpets; j++) {
                dp[i][j] = 0;
            }
        }

        sum.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (floor[i] == '1') {
                sum[i + 1] = 1;
            }
            if (i != 0) {
                sum[i + 1] += sum[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= (i - 1) / carpetLen + 1 && j <= numCarpets; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j > 0) {
                    int l = max(0, i - carpetLen);
                    if (l == 0) {
                        dp[i][j] = max(dp[i][j], sum[i]);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[l][j - 1] + sum[i] - sum[l]);
                    }
                }
            }
        }
        int res = 0;
        for (int j = 0; j <= (n - 1) / carpetLen + 1 && j <= numCarpets; j++) {
            res = max(res, dp[n][j]);
        }
        return sum[n] - res;
    }
};