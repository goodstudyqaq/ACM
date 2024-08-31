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
    string a, b;
    cin >> a >> b;

    int n = a.size(), m = b.size();
    const int inf = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));

    for (int i = 0; i <= m; i++) {
        dp[0][i] = i;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j] + 1;
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            } 
        }
    }

    int ans = inf;
    for (int i = 0; i <= m; i++) {
        ans = min(ans, dp[n][i] + m - i);
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