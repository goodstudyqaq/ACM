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
typedef array<int, 2> a2;

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
    vector<ll> a(n), sum(n), sum2(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // sumi
    for (int i = 0; i < n; i++) {
        sum[i] = abs(a[i]);
        if (i) {
            sum[i] += sum[i - 1];
        }

        sum2[i] = -a[i];
        if (i) {
            sum2[i] += sum2[i - 1];
        }
    }

    const ll inf = 1e18;
    ll res = -inf;
    for (int i = 0; i < n; i++) {
        ll ans = sum2[n - 1] - sum2[i];
        if (i) {
            ans += sum[i - 1] - sum[0];
            ans += a[0];
        }
        res = max(res, ans);
    }
    cout << res << '\n';
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