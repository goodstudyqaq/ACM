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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int m = n / 2;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            dp[i][0] = 1;
        } else {
            dp[i][1] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1) continue;
            int val = a[i];
            for (int k = i + 1; k <= n; k++) {
                if (a[k] > val) {
                    if (k == i + 1) {
                        dp[k][j] = max(dp[i][j] + 1, dp[k][j]);
                    } else {
                        dp[k][j + 1] = max(dp[i][j] + 1, dp[k][j + 1]);
                    }
                }
            }
        }
        debug(i, dp[i]);
    }
    vector<int> ans(m + 2);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == n) {
                ans[j] = max(ans[j], dp[i][j]);
            } else {
                ans[j + 1] = max(ans[j + 1], dp[i][j]);
            }
        }
    }

    for (int i = 1; i <= m + 1; i++) {
        ans[i] = max(ans[i], ans[i - 1]);
    }

    for (int i = 1; i <= n; i++) {
        if (i <= m + 1) {
            cout << n - ans[i] << ' ';
        } else {
            cout << n - ans[m + 1] << ' ';
        }

    }
    cout << endl;

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