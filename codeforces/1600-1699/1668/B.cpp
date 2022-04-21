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
    long long n, m;
    cin >> n >> m;
    vector<long long> a(n);
    m -= n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        m -= a[i];
    }
    sort(a.begin(), a.end());
    m = m - a[n - 1] + a[0];

    if (m < 0) {
        cout << "NO" << endl;
        return;
    } else {
        cout << "YES" << endl;
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
}