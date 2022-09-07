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
    int longestNiceSubarray(vector<int>& nums) {
        // nums = {744437702, 379056602, 145555074, 392756761, 560864007, 934981918, 113312475, 1090, 16384, 33, 217313281, 117883195, 978927664};
        int n = nums.size();
        const int inf = 1e9;
        vector<int> nxt(n + 1, inf);
        for (int i = 0; i < 32; i++) {
            vector<int> nnxt(n + 1);
            nnxt[n] = n;
            int last_one = n;
            for (int j = n - 1; j >= 0; j--) {
                int val = (nums[j] >> i) & 1;
                if (val == 1) {
                    nnxt[j] = last_one;
                    last_one = j;
                } else {
                    nnxt[j] = nnxt[j + 1];
                }
                nxt[j] = min(nxt[j], nnxt[j]);
            }
            // debug(nxt);
        }
        debug(nxt);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, nxt[i] - i);
        }
        return ans;
    }
};