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
    int takeCharacters(string s, int k) {
        int n = s.size();
        // [l, r)
        int r = 0;
        map<char, int> M;
        while (M['a'] < k || M['b'] < k || M['c'] < k) {
            if (r == n) break;
            M[s[r]]++;
            r++;
        }
        if (M['a'] < k || M['b'] < k || M['c'] < k) return -1;
        int ans = 1e9;
        for (int l = n - 1; l >= -1; l--) {
            // (l, n - 1]
            ans = min(ans, r + n - 1 - l);
            if (l < 0) break;
            M[s[l]]++;
            while (r - 1 >= 0 && M[s[r - 1]] > k) {
                M[s[r - 1]]--;
                r--;
            }
        }
        if (ans == 1e9) ans = -1;
        return ans;
    }
};