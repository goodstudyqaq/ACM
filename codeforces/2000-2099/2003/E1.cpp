#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> l(m), r(m);
    vector<int> go(n + 1, -1);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        go[l[i]] = r[i];
    }

    // dp[i][j] 前 i 个数用了 j 个 0
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        if (go[i] == -1) {
            for (int j = 0; j <= i; j++) {
                // dp[i][j]
                if (j > 0) {
                    dp[i][j] = dp[i - 1][j - 1] + (i - j);
                }
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
        } else {
            int l = i, r = go[i];
            debug(l, r);
            for (int j = l; j < r; j++) {
                // [l, j] 都是 0 [j + 1, r] 都是 1
                for (int k = 0; k <= i - 1; k++) {
                    // dp[i - 1][k] -> dp[r][k + j - l + 1]
                    dp[r][k + j - l + 1] = max(dp[r][k + j - l + 1], dp[i - 1][k] + (i - 1 - k) * (j - l + 1));
                }
            }
            i = go[i];
        }
    }

    int ans = 0;
    // debug(dp[4]);
    for (int i = 0; i <= n; i++) {
        if (dp[n][i] >= 0) {
            ans = max(ans, dp[n][i] + i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}