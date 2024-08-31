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

    vector<long long> dp(n + 1);
    dp[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] > a[i + 1]) {
            long long tmp = dp[i + 1];
            long long wait = tmp - a[i + 1];
            long long diff = a[i] - a[i + 1];
            if (diff > wait) {
                dp[i] = a[i];
            } else {
                dp[i] = dp[i + 1] + 1;
            }
        } else {
            dp[i] = dp[i + 1] + 1;
        }
        debug(i, dp[i]);
    }
    cout << dp[1] << endl;
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