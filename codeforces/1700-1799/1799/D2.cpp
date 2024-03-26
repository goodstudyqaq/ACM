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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);

    vector<int> last(n + 1, -1);
    vector<int> idx(k + 1, -1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        last[i] = idx[a[i]];
        idx[a[i]] = i;
    }
    vector<long long> cold(k + 1), hot(k + 1);
    vector<long long> sum(n + 1);
    for (int i = 1; i <= k; i++) {
        cin >> cold[i];
    }
    for (int i = 1; i <= k; i++) {
        cin >> hot[i];
    }

    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1];
        if (a[i] == a[i - 1]) {
            sum[i] += hot[a[i]];
        } else {
            sum[i] += cold[a[i]];
        }
    }

    debug(last);
    vector<long long> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + cold[a[i]];
        if (last[i] == i - 1) {
            dp[i] = min(dp[i], dp[i - 1] + hot[a[i]]);
        } else if (last[i] != -1) {
            int idx = last[i];
            long long tmp = dp[idx + 1] + sum[i - 1] - sum[idx + 1] + hot[a[i]];
            dp[i] = min(dp[i], tmp);

        }
        debug(i, dp[i]);
    }
    cout << dp[n] << endl;
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