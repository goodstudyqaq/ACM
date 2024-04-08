#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    vector<long long> a(n + 1);
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    if (n == 2) {
        cout << max(a[1] + a[2], abs(a[1] - a[2]) * 2) << endl;
        return;
    }
    if (n > 3) {
        cout << 1LL * mx * n << endl;
        return;
    }
    // n = 3
    if (mx == a[1] || mx == a[3]) {
        cout << 1LL * mx * 3 << endl;
        return;
    }

    long long ans = max(a[1] * 3, a[3] * 3);
    typedef array<long long, 3> a3;
    set<a3> S;
    function<void(int d)> dfs = [&](int d) {
        debug(a);
        if (d == 0) return;

        if (S.count({a[1], a[2], a[3]})) {
            return;
        }
        S.insert({a[1], a[2], a[3]});

        ans = max(ans, a[1] + a[2] + a[3]);
        auto ca = a;
        // 1 2
        int tmp = abs(a[1] - a[2]);
        a[1] = a[2] = tmp;
        if (a[1] != ca[1] || a[2] != ca[2]) {
            dfs(d - 1);
            a = ca;
        }
        // 2 3
        tmp = abs(a[2] - a[3]);
        a[2] = a[3] = tmp;
        if (a[2] != ca[2] || a[3] != ca[3]) {
            dfs(d - 1);
            a = ca;
        }

        // 1 3
        tmp = abs(a[1] - a[3]);
        a[1] = a[2] = a[3] = tmp;
        if (a[1] != ca[1] || a[2] != ca[2] || a[3] != ca[3]) {
            dfs(d - 1);
            a = ca;
        }
    };

    dfs(10);
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
    return 0;
}