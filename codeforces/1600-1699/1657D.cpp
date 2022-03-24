#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, C;
    cin >> n >> C;
    vector<long long> p;
    p.resize(C + 1, 0);
    for (int i = 1; i <= n; i++) {
        int c, d, h;
        cin >> c >> d >> h;
        p[c] = max(p[c], 1LL * d * h);
    }

    vector<long long> dp;
    dp.resize(C + 1);
    for (int i = 1; i <= C; i++) {
        if (p[i] == 0) continue;
        for (int j = 1; j * i <= C; j++) {
            dp[i * j] = max(dp[i * j], 1LL * p[i] * j);
        }
    }
    for (int i = 2; i <= C; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
    }

    int m;
    cin >> m;
    while (m--) {
        long long d, h;
        cin >> d >> h;
        long long tmp = d * h;
        auto it = upper_bound(dp.begin(), dp.end(), tmp);
        if (it == dp.end()) {
            cout << -1 << ' ';
        } else {
            cout << it - dp.begin() << ' ';
        }
    }
    cout << endl;
    return 0;
}