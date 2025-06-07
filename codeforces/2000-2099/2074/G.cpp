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
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n, vector<long long>(n));

    for (int l = 3; l <= n; l++) {
        for (int i = 0; i + l - 1 <= n - 1; i++) {
            int j = i + l - 1;
            // [i, j]
            long long tmp = a[i] * a[i + 1] * a[i + 2] + (i + 3 <= j ? dp[i + 3][j] : 0);
            dp[i][j] = tmp;

            for (int c3 = i; c3 < j; c3++) {
                long long tmp2 = dp[i][c3] + dp[c3 + 1][j];
                dp[i][j] = max(dp[i][j], tmp2);
            }

            for (int c1 = i; c1 <= i + 2; c1++) {
                for (int c3 = j; c3 >= j - 2 && c3 > c1; c3--) {
                    for (int c2 = c1 + 1; c2 < c3; c2++) {
                        long long tmp3 = a[c1] * a[c2] * a[c3];
                        if (c1 + 1 <= c2 - 1) {
                            tmp3 += dp[c1 + 1][c2 - 1];
                        }

                        if (c2 + 1 <= c3 - 1) {
                            tmp3 += dp[c2 + 1][c3 - 1];
                        }

                        dp[i][j] = max(dp[i][j], tmp3);
                    }
                }
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
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