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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    vector<ll> x(n + 1);
    vector<ll> C(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    for (int i = 1; i <= m; i++) {
        ll a, b;
        cin >> a >> b;
        C[a] = b;
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, -inf));

    dp[1][0] = 0;
    dp[1][1] = x[1] + C[1];

    for (int i = 2; i <= n; i++) {
        ll mx = 0;
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j - 1] + x[i] + C[j];
            mx = max(mx, dp[i - 1][j]);
        }
        dp[i][0] = mx;
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << endl;
}