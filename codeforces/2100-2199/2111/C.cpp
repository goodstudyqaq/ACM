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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        l[i] = i;
        if (i > 0 && a[i] == a[i - 1]) {
            l[i] = l[i - 1];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        r[i] = i;
        if (i != n - 1 && a[i] == a[i + 1]) {
            r[i] = r[i + 1];
        }
    }

    long long ans = 1e18;
    for (int i = 0; i < n; i++) {
        int l_ = l[i];
        int r_ = r[i];

        ans = min(ans, 1LL * (l_ + n - r_ - 1) * a[i]);
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