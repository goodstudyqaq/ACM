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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<ll> dp(2);

    const ll inf = 1e18;
    vector<ll> mx_dp(2, -inf);
    for (int i = 1; i <= n; i++) {
        vector<ll> ndp(2);
        ndp[0] = a[i];
        if (dp[0] > 0) ndp[0] += dp[0];

        // ndp[1]

        ll tmp = a[i] + b[i];
        if (dp[0] > 0) tmp += dp[0];

        ll tmp2 = a[i];
        if (dp[1] > 0) tmp2 += dp[1];
        ndp[1] = max(tmp, tmp2);

        dp = ndp;
        mx_dp[0] = max(mx_dp[0], dp[0]);
        mx_dp[1] = max(mx_dp[1], dp[1]);
    }

    cout << mx_dp[k % 2] << '\n';
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