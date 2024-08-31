#include <bits/stdc++.h>

#include <limits>

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
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    int g = gcd(a, b);
    if (g == 1) {
        cout << 0 << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        c[i] %= g;
    }

    sort(c.begin(), c.end());

    int mx = c[n - 1];
    int res = numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        res = min(res, mx - c[i]);
        mx = c[i] + g;
    }
    cout << res << endl;
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