#include <bits/stdc++.h>

#include <limits>

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
    int n;
    cin >> n;
    vector<vector<long long>> h(n + 1, vector<long long>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> h[i][j];
        }
    }
    vector<long long> a(n + 1), b(n + 1);
    // 横着
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // 竖着
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<long long> dp(2);

    dp[0] = 0;
    dp[1] = a[1];
    const long long inf = numeric_limits<long long>::max() / 2;
    for (int i = 2; i <= n; i++) {
        debug(i);
        vector<long long> ndp(2, inf);

        vector<vector<long long>> tmp(2, vector<long long>(n + 1));
        vector<vector<long long>> now(2, vector<long long>(n + 1));
        for (int j = 1; j <= n; j++) {
            tmp[0][j] = h[i - 1][j];
            tmp[1][j] = h[i - 1][j] + 1;
            now[0][j] = h[i][j];
            now[1][j] = h[i][j] + 1;
        }
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                bool have_eq = false;
                for (int p = 1; p <= n; p++) {
                    if (tmp[j][p] == now[k][p]) {
                        have_eq = true;
                        break;
                    }
                }
                if (!have_eq) {
                    ndp[k] = min(ndp[k], dp[j] + (k ? a[i] : 0));
                }
            }
        }
        dp = ndp;
    }

    long long ans = min(dp[0], dp[1]);
    debug(ans);
    if (ans == inf) {
        cout << -1 << '\n';
        return;
    }

    dp[0] = 0;
    dp[1] = b[1];
    for (int i = 2; i <= n; i++) {
        vector<long long> ndp(2, inf);

        vector<vector<long long>> tmp(2, vector<long long>(n + 1));
        vector<vector<long long>> now(2, vector<long long>(n + 1));
        for (int j = 1; j <= n; j++) {
            tmp[0][j] = h[j][i - 1];
            tmp[1][j] = h[j][i - 1] + 1;
            now[0][j] = h[j][i];
            now[1][j] = h[j][i] + 1;
        }
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                bool have_eq = false;
                for (int p = 1; p <= n; p++) {
                    if (tmp[j][p] == now[k][p]) {
                        have_eq = true;
                        break;
                    }
                }
                if (!have_eq) {
                    ndp[k] = min(ndp[k], dp[j] + (k ? b[i] : 0));
                }
            }
        }
        dp = ndp;
    }
    long long ans2 = min(dp[0], dp[1]);
    if (ans2 == inf) {
        cout << -1 << '\n';
        return;
    }
    cout << ans + ans2 << '\n';
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