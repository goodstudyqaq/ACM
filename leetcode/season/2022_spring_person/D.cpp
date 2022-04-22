#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class Solution {
   public:
    int defendSpaceCity(vector<int>& time, vector<int>& position) {
        int n = time.size();
        vector<int> mp;
        mp = vector(102, 0);
        for (int i = 0; i < n; i++) {
            int t = time[i], pos = position[i];
            mp[pos + 1] |= (1 << (t - 1));
        }
        int LIMIT = 1 << 5;
        vector<int> cost1, cost2;
        cost1 = vector(LIMIT, 0);
        cost2 = vector(LIMIT, 0);

        for (int i = 1; i < LIMIT; i++) {
            int s1 = i & -i;
            if (s1 == i) {
                cost1[i] = 2, cost2[i] = 3;
            } else {
                int s2 = i - s1;
                int s3 = s2 & -s2;
                if (i == 3) {
                    debug(s1, s2, s3);
                }
                cost1[i] = cost1[s2] + ((s1 << 1) == s3 ? 1 : 2);
                cost2[i] = cost2[s2] + ((s1 << 1) == s3 ? 1 : 3);
            }
        }
        debug(cost1);
        debug(cost2);

        const int inf = 1e9;
        vector dp = vector(102, vector(LIMIT, inf));
        dp[0][0] = 0;
        // dp[i][j] 前 i 个仓库搞定，第 i 个仓库搞了和 i + 1 的联合屏障的状态为 j 的最小代价
        for (int i = 1; i <= 101; i++) {
            for (int j = 0; j < LIMIT; j++) {
                int mask = LIMIT - j - 1;
                for (int sub = mask, ok = true; ok; ok = (sub != mask)) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][sub] + cost2[j] + cost1[(mp[i] - ((j + sub) & mp[i]))]);
                    sub = (sub - 1) & mask;
                }
            }
        }
        return dp[101][0];
    }
};

// int main() {
// #ifdef LOCAL
//     freopen("./data.in", "r", stdin);
// #endif
//     Solution sol = Solution();

//     /*
//     [1,4,3,2,5,3,2,1,1,2,5,5,3,5,4,1,1,2,4,5,5,5,1,3,4,4,4,4,2,3,2,1,5,5,2,1,4,1,4,5,4,4,2,3,4,5,5,3,3,2,1,5,5]
// [4,29,20,12,11,7,15,17,5,25,21,15,5,3,10,10,29,11,3,25,28,14,26,19,9,25,28,12,4,22,19,23,23,13,6,3,23,11,1,26,15,27,5,16,7,4,24,23,2,20,8,20,27]
//     */
//     vector<int> time = {1, 4, 3, 2, 5, 3, 2, 1, 1, 2, 5, 5, 3, 5, 4, 1, 1, 2, 4, 5, 5, 5, 1, 3, 4, 4, 4, 4, 2, 3, 2, 1, 5, 5, 2, 1, 4, 1, 4, 5, 4, 4, 2, 3, 4, 5, 5, 3, 3, 2, 1, 5, 5};
//     vector<int> pos = {4, 29, 20, 12, 11, 7, 15, 17, 5, 25, 21, 15, 5, 3, 10, 10, 29, 11, 3, 25, 28, 14, 26, 19, 9, 25, 28, 12, 4, 22, 19, 23, 23, 13, 6, 3, 23, 11, 1, 26, 15, 27, 5, 16, 7, 4, 24, 23, 2, 20, 8, 20, 27};
//     // time = {1, 1, 1, 2, 2, 3, 5};
//     // pos = {1, 2, 3, 1, 2, 1, 3};
//     cout << sol.defendSpaceCity(time, pos) << endl;
//     return 0;
// }