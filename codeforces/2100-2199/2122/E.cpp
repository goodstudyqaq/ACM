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

vector<int> dp;
void init() {
    const int m = 5e5;
    dp.resize(m + 1);
    dp[1] = 1;

    for (int i = 2; i <= m; i++) {
        dp[i] = 1e9;
        for (int j = 1; j <= sqrt(i); j++) {
            if (i % j == 0) {
                // dp[j - 2], dp[i / j]
                if (j - 2 > 0) {
                    dp[i] = min(dp[i], dp[j - 2] + dp[i / j]);
                }
                int j2 = i / j;
                if (j2 - 2 > 0) {
                    dp[i] = min(dp[i], dp[j2 - 2] + dp[i / j2]);
                }
            }
        }
    }
}

void solve() {
    int m;
    cin >> m;
    if (dp[m] == 1e9) {
        cout << -1 << '\n';
    } else {
        cout << dp[m] << '\n';
    }

}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}