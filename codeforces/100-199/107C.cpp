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

    int n, m;
    long long y;
    cin >> n >> y >> m;
    y -= 2000;

    vector<int> a;
    a.resize(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        a[v] |= (1 << u);
    }
    vector<int> two_cnt;
    int LIMIT = 1 << n;
    two_cnt.resize(LIMIT);
    for (int i = 1; i < LIMIT; i++) {
        two_cnt[i] += two_cnt[i - (i & -i)] + 1;
    }

    vector<int> ans, location;
    ans.resize(n, n);
    location.resize(n, n);
    vector<vector<long long>> dp;
    auto work = [&](int idx) {
        dp.resize(LIMIT, vector<long long>(n + 1, 0));
        for (int i = 0; i < LIMIT; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][n] = 1;
        // 已经用了的位置的状态
        for (int i = 0; i < LIMIT - 1; i++) {
            int cnt = two_cnt[i];
            // 已经放了 [1, cnt], 接下来放 cnt + 1
            int nxt_push_val = cnt;
            if (location[nxt_push_val] != n) {
                int loc = location[nxt_push_val];
                if ((a[loc] & i) != a[loc]) {
                    continue;
                }
                if ((i >> loc) & 1) {
                    continue;
                }
                for (int j = 0; j <= n; j++) {
                    if (loc == idx) {
                        dp[i + (1 << loc)][nxt_push_val] += dp[i][j];
                    } else {
                        dp[i + (1 << loc)][j] += dp[i][j];
                    }
                }
            } else {
                for (int j = 0; j < n; j++) {
                    if ((i >> j) & 1) continue;
                    if ((a[j] & i) != a[j]) continue;
                    for (int k = 0; k <= n; k++) {
                        if (j == idx) {
                            dp[i + (1 << j)][nxt_push_val] += dp[i][k];
                        } else {
                            dp[i + (1 << j)][k] += dp[i][k];
                        }
                    }
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        work(i);
        // debug(dp[LIMIT - 1]);
        for (int j = 0; j < n; j++) {
            debug(i, j, y, dp[LIMIT - 1][j]);
            if (dp[LIMIT - 1][j] < y) {
                y -= dp[LIMIT - 1][j];
            } else {
                // 第 i 个位置选了 j
                debug(i, j);
                ans[i] = j;
                location[j] = i;
                break;
            }
        }
        if (ans[i] == n) {
            cout << "The times have changed" << endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << endl;
    return 0;
}