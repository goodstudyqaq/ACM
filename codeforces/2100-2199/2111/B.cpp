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
    int n, m;
    cin >> n >> m;
    vector<int> f(n);
    f[0] = 1;
    f[1] = 2;
    for (int i = 2; i < n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    int mx = f[n - 1];
    debug(mx);

    while (m--) {
        int w, l, h;
        cin >> w >> l >> h;
        int mi = min({w, l, h});
        if (mi < mx) {
            cout << 0;
        } else {
            int val = f[n - 1] + f[n - 2];
            if (max({w, l, h}) >= val) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
    }
    cout << '\n';
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