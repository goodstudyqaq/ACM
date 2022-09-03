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

    int n, x, y;
    cin >> n >> x >> y;
    vector dp = vector(n + 1, 0LL);

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            dp[i] = min(dp[i - 1] + x, dp[i / 2] + y);
        } else {
            dp[i] = min(dp[i - 1] + x, dp[(i + 1) / 2] + y + x);
        }
    }
    cout << dp[n] << endl;
    return 0;
}