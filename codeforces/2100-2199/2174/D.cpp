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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> idx;
    int last_val = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > last_val) {
            idx.push_back(i);
            last_val = a[i];
        }
    }

    if (idx.size() == 0) {
        cout << 0 << '\n';
        return;
    }



    // 最大 360 个点
    debug(idx);
    const int inf = 1e9;
    vector<vector<int>> dp(k + 1, vector<int>(k + 1, -inf));  // dp[i][j] 最大用 i，总共用了 k 的最大方案书
    dp[0][0] = 0;

    int sz = idx.size();
    for (int i = 0; i < sz; i++) {
        vector<vector<int>> ndp(k + 1, vector<int>(k + 1, -inf));
        if (i > 0) {
            int idx1 = idx[i], idx2 = idx[i - 1];
            int step = idx1 - idx2 - 1;
            for (int p = 0; p <= k; p++) {
                for (int q = p; q <= k; q++) {
                    dp[p][q] = dp[p][q] + step * p;
                }
            }
        }
        for (int p = 0; p <= k; p++) {
            for (int q = p; q <= k; q++) {
                // ndp[p][q]
                // 一个都没用
                ndp[p][q] = dp[p][q] + p;
                if (p <= a[idx[i]]) {
                    // 用 p
                    for (int last_mx = 0; last_mx < p; last_mx++) {
                        ndp[p][q] = max(ndp[p][q], dp[last_mx][q - p] + p);
                    }
                }
            }
        }
        dp = ndp;
        // debug(dp);
    }

    int res = 0;
    int idx1 = n;
    int idx2 = idx[sz - 1];
    int step = idx1 - idx2;
    for (int p = 0; p <= k; p++) {
        for (int q = p; q <= k; q++) {
            res = max(res, dp[p][q] + step * p);
        }
    }
    cout << res << '\n';
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