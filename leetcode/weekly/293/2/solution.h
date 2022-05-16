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
    int largestCombination(vector<int>& V) {
        int n = V.size();
        int ans = 1;
        for (int i = 0; i < 25; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                int tmp = (V[j] >> i) & 1;
                if (tmp) {
                    cnt++;
                }
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};