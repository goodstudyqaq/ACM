#include <bits/stdc++.h>
#include <limits>

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
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }

    vector<int> a(n + 1), w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    vector<int> L(n + 1), R(n + 1), IDX(n + 1);

    int cnt = 0;
    function<void(int)> dfs = [&](int u) {
        L[u] = ++cnt;
        IDX[cnt] = u;
        for (auto v : V[u]) {
            dfs(v);
        }
        R[u] = cnt;
    };
    dfs(1);

    const int inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> dp(n + 2, vector<int>(m + 1, -inf));
    dp[n + 1][0] = 0;

    for (int i = n; i >= 1; i--) {
        int idx = IDX[i];
        int r = R[idx] + 1;
        for (int j = 0; j <= m; j++) {
            if (j >= w[idx]) {
                dp[i][j] = dp[i + 1][j - w[idx]] + a[idx];  // 选它
            }
            dp[i][j] = max(dp[i][j], dp[r][j]);  // 不选它
        }
        // debug(idx, dp[i], r);
    }

    for (int k = 0; k <= m; k++) {
        if (dp[1][k] < 0) dp[1][k] = 0;
        cout << dp[1][k] << endl;
    }
    return 0;
}