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

class Solution {
   public:
    int longestSquareStreak(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n);
        map<int, int> M;
        int res = -1;
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            M[nums[i]] = i;
            int tmp = sqrt(nums[i]);
            if (tmp * tmp != nums[i]) {
                continue;
            }
            if (M.count(tmp)) {
                dp[i] = dp[M[tmp]] + 1;
            }
            res = max(dp[i], res);
        }
        if (res < 2) return -1;
        return res;
    }
};