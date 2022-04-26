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
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    int mi = 1e9, mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mi = min(mi, a[i]);
        mx = max(mx, a[i]);
    }
    long long ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += abs(a[i] - a[i - 1]);
    }

    // 计算 [1, mi - 1]
    if (mi != 1) {
        int tmp = 2 * (mi - 1);
        tmp = min(tmp, a[1] - 1);
        tmp = min(tmp, a[n] - 1);
        ans += tmp;
    }
    // 计算 [mx + 1, x]
    if (mx < x) {
        int tmp = 2 * (x - mx);
        tmp = min(tmp, x - a[1]);
        tmp = min(tmp, x - a[n]);
        ans += tmp;
    }
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