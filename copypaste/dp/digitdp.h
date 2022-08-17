#include <bits/stdc++.h>
using namespace std;

// https://leetcode.cn/problems/numbers-with-repeated-digits/submissions/
int dp[11][1025][2];
class Solution {
   public:
    int n;
    vector<int> v;
    int dfs(int d, int status, bool flag, bool limit, bool lead) {
        if (d == n) {
            return flag;
        }
        if (!limit && dp[d][status][flag] != -1) return dp[d][status][flag];
        int res = 0;
        int LIMIT = limit ? v[d] : 9;

        for (int i = 0; i <= LIMIT; i++) {
            if (lead && i == 0) {
                res += dfs(d + 1, status, false, false, true);
            } else {
                res += dfs(d + 1, status | (1 << i), flag || ((status >> i) & 1), limit && (i == LIMIT), false);
            }
        }
        if (!limit) dp[d][status][flag] = res;
        // debug(d, status, flag, limit, lead, res);
        return res;
    }

    int work(int val) {
        v.clear();
        while (val) {
            v.push_back(val % 10);
            val /= 10;
        }
        reverse(v.begin(), v.end());

        n = v.size();
        return dfs(0, 0, false, true, true);
    }
    int numDupDigitsAtMostN(int n) {
        memset(dp, -1, sizeof(dp));
        return work(n);
    }
};