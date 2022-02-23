// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"
// hello
class Solution {
   public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        vector<int> sum(1001, 0);
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            sum[nums[i]]++;
        }
        vector<int> have;
        for (int i = 1; i <= 1000; i++) {
            if (sum[i]) {
                have.push_back(sum[i]);
            }
        }
        int cnt = have.size();
        int m = quantity.size();
        int LIMIT = 1 << m;
        vector<vector<bool>> can(cnt + 1, vector<bool>(LIMIT, 0));
        vector<int> sum2(LIMIT, 0);
        int tmp = 0;
        for (int j = 1; j < LIMIT; j++) {
            int other = j & -j;
            int val = 0;
            if (other == j) {
                val = quantity[tmp++];
            } else {
                val = sum2[j - other] + sum2[other];
            }
            sum[j] = val;
            for (int i = 0; i < cnt; i++) {
                if (val <= have[i]) {
                    can[i + 1][j] = 1;
                }
            }
        }

        vector<vector<bool>> dp(cnt + 1, vector<bool>(LIMIT, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= cnt; i++) {
            for (int j = 0; j < LIMIT; j++) {
                dp[i][j] = dp[i - 1][j];
                for (int k = j; k; k = (k - 1) & j) {
                    if (can[i][k]) {
                        dp[i][j] = dp[i][j] | dp[i - 1][j - k];
                    }
                }
            }
        }
        return dp[cnt][LIMIT - 1];
    }
};
// world