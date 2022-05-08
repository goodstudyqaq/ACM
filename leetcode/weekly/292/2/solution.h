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
    int get_num(int val) {
        if (val == 7 || val == 9) return 4;
        return 3;
    }

    int countTexts(string s) {
        const int mod = 1e9 + 7;
        int n = s.size();
        vector<int> dp1(n + 1), dp2(n + 1);
        dp1[1] = 1;
        dp2[1] = 1;

        for (int i = 2; i <= n; i++) {
            int tmp = 0;
            for (int j = 1; j <= 3; j++) {
                if (i - j >= 1) {
                    tmp = (tmp + dp1[i - j]) % mod;
                }
            }
            if (i <= 3) {
                tmp = (tmp + 1) % mod;
            }
            dp1[i] = tmp;
        }
        for (int i = 2; i <= n; i++) {
            int tmp = 0;
            for (int j = 1; j <= 4; j++) {
                if (i - j >= 1) {
                    tmp = (tmp + dp2[i - j]) % mod;
                }
            }
            if (i <= 4) {
                tmp = (tmp + 1) % mod;
            }
            dp2[i] = tmp;
        }

        int now = 0;
        long long ans = 1;
        while (now < n) {
            int go = now;
            while (go < n && s[go] == s[now]) go++;
            int len = go - now;
            int num = get_num(s[now] - '0');
            if (num == 3) {
                ans = ans * dp1[len] % mod;
            } else {
                ans = ans * dp2[len] % mod;
            }
            now = go;
        }
        return ans;
    }
};