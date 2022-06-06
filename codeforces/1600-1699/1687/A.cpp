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
    vector<ll> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    if (k <= n) {
        ll res = 1LL * (k - 1) * k / 2;

        ll res2 = 0;
        for (int i = k; i <= n; i++) {
            ll tmp = sum[i] - sum[i - k];
            res2 = max(res2, tmp);
        }
        cout << res + res2 << endl;
        return;
    }

    ll ans = sum[n] + 1LL * (k - 1 + k - n) * n / 2;
    cout << ans << endl;
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
}