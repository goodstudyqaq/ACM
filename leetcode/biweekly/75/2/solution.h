/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

class Solution {
   public:
    long long numberOfWays(string s) {
        int n = s.size();
        vector<vector<int>> sum, sum2;
        sum.resize(2, vector<int>(n));
        sum2.resize(2, vector<int>(n));
        for (int i = 0; i < n; i++) {
            int f = s[i] - '0';
            sum[f][i] = 1;
            if (i != 0) {
                sum[0][i] += sum[0][i - 1];
                sum[1][i] += sum[1][i - 1];
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int f = s[i] - '0';
            sum2[f][i] = 1;
            if (i != n - 1) {
                sum2[0][i] += sum2[0][i + 1];
                sum2[1][i] += sum2[1][i + 1];
            }
        }

        long long ans = 0;
        for (int i = 1; i < n - 1; i++) {
            int f = s[i] - '0';
            ans += 1LL * sum[f ^ 1][i] * sum2[f ^ 1][i];
        }
        return ans;
    }
};