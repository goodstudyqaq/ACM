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
    int r, n;
    cin >> r >> n;
    vector<int> t(n + 1), x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> x[i] >> y[i];
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector<int> dp(n + 1, -inf), mx_dp(n + 1, -inf);
    int res = 0;

    auto check = [&](int a, int b) {
        int delta_x = abs(x[a] - x[b]);
        int delta_y = abs(y[a] - y[b]);
        int delta_time = t[b] - t[a];
        return delta_x + delta_y <= delta_time;
    };

    for (int i = 1; i <= n; i++) {
        if (abs(x[i] - 1) + abs(y[i] - 1) <= t[i]) {
            dp[i] = 1;
        }
        int l = max(i - 2 * r, 0);
        dp[i] = max(dp[i], mx_dp[l] + 1);
        for (int j = l + 1; j < i; j++) {
            if (check(j, i)) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
        mx_dp[i] = max(mx_dp[i - 1], dp[i]);
    }
    cout << res << endl;
    return 0;
}