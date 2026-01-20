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
    vector<ll> a(n);
    vector<ll> pre_sum(n), suf_sum(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            pre_sum[i] = a[i];
        }
        if (i) {
            pre_sum[i] += pre_sum[i - 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < 0) {
            suf_sum[i] = a[i];
        }
        if (i != n - 1) {
            suf_sum[i] += suf_sum[i + 1];
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, pre_sum[i] - suf_sum[i]);
    }
    cout << ans << '\n';
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