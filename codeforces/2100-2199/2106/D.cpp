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
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int l = 0, r = 1e9;
    int ans = -1;
    // l = 7, r = 7;

    vector<vector<int>> dp(n, vector<int>(2, 0));
    auto check = [&](int val) {
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                dp[i][0] = (a[0] >= b[0]);
                // 先塞再 check a[0]
                int idx = 0;
                if (val >= b[idx]) {
                    idx++;
                }
                if (idx < m && a[0] >= b[idx]) {
                    idx++;
                }
                dp[i][1] = idx;

                // 先 check a[0] 再塞
                idx = 0;
                if (a[0] >= b[idx]) {
                    idx++;
                }
                if (idx < m && val >= b[idx]) {
                    idx++;
                }
                dp[i][1] = max(dp[i][1], idx);
            } else {
                dp[i][0] = dp[i - 1][0] + (a[i] >= b[dp[i - 1][0]]);
                dp[i][1] = dp[i - 1][1] + (a[i] >= b[dp[i - 1][1]]);

                int idx = dp[i - 1][0];
                if (val >= b[idx]) {
                    idx++;
                }
                if (idx < m && a[i] >= b[idx]) {
                    idx++;
                }
                dp[i][1] = max(dp[i][1], idx);

                idx = dp[i - 1][0];
                if (a[i] >= b[idx]) {
                    idx++;
                }
                if (idx < m && val >= b[idx]) {
                    idx++;
                }
                dp[i][1] = max(dp[i][1], idx);
            }
            // debug(i, dp[i]);
            if (dp[i][0] == m || dp[i][1] == m) return true;
        }

        return false;
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << '\n';
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