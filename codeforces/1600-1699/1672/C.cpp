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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> v;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i + 1]) {
            v.push_back(i);
        }
    }

    int sz = v.size();
    if (sz <= 1) {
        cout << 0 << endl;
        return;
    }

    int mi = v[0], mx = v[sz - 1];
    if (mi == mx - 1) {
        cout << 1 << endl;
        return;
    }
    mi++;
    mx--;
    debug(mi, mx);
    cout << mx - mi + 1 << endl;
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