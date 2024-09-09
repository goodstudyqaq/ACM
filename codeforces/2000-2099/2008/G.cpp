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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        if (k <= a[0]) {
            cout << k - 1 << endl;
        } else {
            cout << k << endl;
        }
        return;
    }

    int g = a[0];

    for (int i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }

    if (g == 1) {
        cout << n + k - 1 << endl;
        return;
    }
    debug(g);
    if (g == 0) {
        cout << k << endl;
        return;
    }

    // g * 0 g * 1, g * 2, ... g * (n - 1)
    int tmp = g - 1;
    long long all = 1LL * tmp * (n - 1);
    debug(all);
    if (k > all) {
        k -= all;
        cout << 1LL * g * (n - 1) + k << endl;
    } else {
        int tmp2 = k / tmp;
        int tmp3 = k % tmp;
        debug(tmp2, tmp3);

        if (tmp3 == 0) {
            cout << 1LL * g * tmp2 - 1 << endl;
        } else {
            cout << 1LL * g * tmp2 + tmp3 << endl;
        }
    }
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