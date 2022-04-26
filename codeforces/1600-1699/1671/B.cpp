#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    int mx = -1e9, mi = 1e9;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
        mx = max(mx, a[i]);
        mi = min(mi, a[i]);
    }
    cout << (mx - mi <= 2 ? "YES" : "NO") << endl;
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