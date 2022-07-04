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
    double calculateTax(vector<vector<int>>& V, int income) {
        int n = V.size();
        double last = 0;
        double ans = 0;
        for (int i = 0; i < n; i++) {
            double a = V[i][0], b = V[i][1];
            double tmp = min(a - last, income - last);
            ans += tmp * b / 100.0;
            last = a;
            if (a > income) break;
        }
        return ans;
    }
};