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
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> dp(n, vector<int>(m, 1e9));

    queue<pii> Q;
    Q.push({0, 0});
    dp[0][0] = 0;

    while (!Q.empty()) {
        auto [x, y] = Q.front();
        // debug(x, y);
        Q.pop();
        // 往下
        int x2 = (x + 2) % n;
        int x1 = (x + 1) % n;
        if (a[x1][y] != 1 && a[x2][y] != 1) {
            if (dp[x2][y] > dp[x][y] + 1) {
                dp[x2][y] = dp[x][y] + 1;
                Q.push({x2, y});
            }
        }
        // 往右
        if (y + 1 < m) {
            int y1 = y + 1;
            if (a[x1][y1] != 1) {
                if (dp[x1][y1] > dp[x][y] + 1) {
                    dp[x1][y1] = dp[x][y] + 1;
                    Q.push({x1, y1});
                }
            }
        }
    }
    int res = 1e9;
    for (int i = 0; i < n; i++) {
        if (dp[i][m - 1] != 1e9) {
            int t = dp[i][m - 1];
            int real_x = ((i - t) % n + n) % n;
            if (real_x == n - 1) {
                res = min(res, t);
            } else {
                res = min(res, real_x + 1 + t);
            }
        }
    }
    if (res == 1e9) res = -1;
    cout << res << endl;
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