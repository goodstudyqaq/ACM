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
    vector<int> p(2);
    vector<ll> t(2);
    cin >> p[0] >> t[0];
    cin >> p[1] >> t[1];
    int h, s;

    cin >> h >> s;

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<ll> dp(h + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= h; i++) {
        // 更垮的一类松弛
        // dp[i] = min(dp[max(0, i - (p[0] - s))] + t[0], dp[max(0, i - (p[1] - s))] + t[1]);

        for (int j = 1; j <= i; j++) {
            if (1LL * j * t[0] >= t[1]) {
                ll ct = (j - 1) * (p[0] - s) + (1LL * j * t[0] - t[1]) / t[1] * (p[1] - s) + (p[0] + p[1] - s);
                // debug(ct);
                dp[i] = min(dp[i], dp[max(0LL, 1LL * i - ct)] + 1LL * j * t[0]);
            }

            if (1LL * j * t[1] >= t[0]) {
                ll ct = (j - 1) * (p[1] - s) + (1LL * j * t[1] - t[0]) / t[0] * (p[0] - s) + (p[0] + p[1] - s);
                dp[i] = min(dp[i], dp[max(0LL, 1LL * i - ct)] + 1LL * j * t[1]);
            }
        }
    }
    debug(dp);

    ll res = dp[h];
    for (int i = 0; i <= h; i++) {
        int left = h - i;
        int times = (left - 1) / (p[0] - s) + 1;
        res = min(res, dp[i] + t[0] * times);

        times = (left - 1) / (p[1] - s) + 1;
        res = min(res, dp[i] + t[1] * times);
    }

    cout << res << endl;
    return 0;
}