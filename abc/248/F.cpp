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
    int n, p;
    cin >> n >> p;
    vector dp = vector(n, vector(n, vector(6, 0)));
    // dp[i][j][k] 到 i 位置，已经删了 j 个，最后一个状态为 k 的方案数

    dp[1][1][0] = 1;
    dp[1][1][1] = 1;
    dp[1][0][2] = 1;
    dp[1][1][3] = 1;
    int m = n - 1;

    debug(p);
    for (int i = 1; i < m; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < 6; k++) {
                if (dp[i][j][k] == 0) continue;
                if (k != 2) {
                    (dp[i + 1][j + 1][0] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 1][1] += dp[i][j][k]) %= p;
                    (dp[i + 1][j][2] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 1][3] += dp[i][j][k]) %= p;
                } else if (k == 2) {
                    (dp[i + 1][j + 1][0] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 1][1] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 1][2] += dp[i][j][k]) %= p;
                    (dp[i + 1][j][2] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 2][4] += dp[i][j][k]) %= p;
                    (dp[i + 1][j + 2][5] += dp[i][j][k]) %= p;
                }
            }
        }
    }

    vector<int> ans(n);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 6; j++) {
            int tmp = dp[m][i][j];
            if (tmp == 0) continue;
            if (j == 2) {
                (ans[i] += tmp) %= p;
                (ans[i + 1] += tmp) %= p;
            } else {
                (ans[i] += tmp) %= p;
            }
        }
    }
    // debug(dp[m]);

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}