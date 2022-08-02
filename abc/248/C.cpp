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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> dp;
    dp.resize(n + 1, vector<int>(k + 1, 0));
    // dp[i][j] i 个数的乘积为 j 的方案数
    for (int i = 1; i <= m; i++) {
        dp[1][i] = 1;
    }

    const int mod = 998244353;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (dp[i][j] == 0) continue;
            for (int p = 1; p <= m; p++) {
                int tmp = p + j;
                if (tmp > k) continue;
                (dp[i + 1][tmp] += dp[i][j]) %= mod;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        // debug(i, dp[n][i]);
        (ans += dp[n][i]) %= mod;
    }
    cout << ans << endl;

    return 0;
}