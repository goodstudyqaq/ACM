#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

class Solution {
   public:
    int unSuitability(vector<int>& op) {
        int n = op.size();
        int mx = *max_element(op.begin(), op.end());
        mx *= 2;
        const int inf = 1e9;
        vector dp = vector(mx + 1, inf);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            vector ndp = vector(mx + 1, inf);
            for (int j = 0; j <= mx; j++) {
                if (dp[j] == inf) continue;
                // op[i] 为正
                if (j + op[i] <= mx) {
                    ndp[j + op[i]] = min(ndp[j + op[i]], max(dp[j], j + op[i]));
                }
                // 为负
                if (j - op[i] >= 0) {
                    ndp[j - op[i]] = min(ndp[j - op[i]], dp[j]);
                } else {
                    ndp[0] = min(ndp[0], dp[j] - j + op[i]);
                }
            }
            dp = ndp;
        }
        return *min_element(dp.begin(), dp.end());
    }
};

// int main() {
// #ifdef LOCAL
//     freopen("./data.in", "r", stdin);
// #endif
//     vector<int> op = {5, 3, 7};
//     // op = {20, 10};
//     // op = {10, 20};
//     Solution sol;
//     int res = sol.unSuitability(op);
//     debug(res);
// }