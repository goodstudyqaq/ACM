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
    vector<long long> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<long long> dp(n + 1);
    dp[n] = h[n] - 1;
    dp[n - 1] = min(h[n - 1] + max(h[n] - (n - 1), 0LL), h[n - 1] - 1 + dp[n]);

    for (int i = n - 2; i >= 1; i--) {
        dp[i] = min(h[i] + max(0LL, h[i + 1] - i) + dp[i + 2], h[i] - 1 + dp[i + 1]);
    }
    cout << dp[1] + 1 << '\n';
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