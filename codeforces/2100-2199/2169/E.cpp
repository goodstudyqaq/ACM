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
    vector<long long> x(n), y(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }
    const ll inf = numeric_limits<long long>::max() / 2;
    ll sum_c = 0;
    ll mi_c = inf;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        sum_c += c[i];
        mi_c = min(mi_c, c[i]);
    }

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    const int S = 1 << 4;  // -x, x, -y, y
    vector<long long> dp(S, -inf);
    dp[0] = 0;
    auto work = [&](int idx, int status) {
        if (status == 0) {
            return -x[idx] * 2;
        } else if (status == 1) {
            return x[idx] * 2;
        } else if (status == 2) {
            return -y[idx] * 2;
        } else {
            return y[idx] * 2;
        }
    };

    for (int i = 0; i < n; i++) {
        vector<long long> ndp(S);
        for (int j = 0; j < S; j++) {
            ndp[j] = dp[j] + c[i];

            vector<int> tmp;
            for (int k = 0; k < 4; k++) {
                if ((j >> k) & 1) {
                    tmp.push_back(k);
                }
            }

            // 影响 1 个
            for (auto it : tmp) {
                ndp[j] = max(ndp[j], dp[j - (1 << it)] + work(i, it));
            }

            // 影响两个
            int sz = tmp.size();
            for (int p = 0; p < sz; p++) {
                for (int q = p + 1; q < sz; q++) {

                    if ((tmp[p] ^ 1) == tmp[q]) continue;

                    ndp[j] = max(ndp[j], dp[j - (1 << tmp[p]) - (1 << tmp[q])] + work(i, tmp[p]) + work(i, tmp[q]));
                }
            }
        }
        dp = ndp;
        debug(i, dp);
    }
    cout << max(dp[S - 1], sum_c - mi_c) << '\n';
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