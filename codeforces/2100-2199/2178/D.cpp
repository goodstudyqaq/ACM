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
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), f(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    debug(n, m, a);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        return a[x] < a[y];
    });

    ll mx = a[f[n - 1]];
    typedef array<ll, 2> al2;
    vector<al2> ans;

    auto work_for_zero = [&]() {
        int now = n - 2;
        ll tmp_sum = a[f[now]];

        while (tmp_sum < mx) {
            now--;
            tmp_sum += a[f[now]];
        }

        for (int i = 1; i <= now; i++) {
            ans.push_back({f[i - 1], f[i]});
        }

        for (int i = now; i < n - 1; i++) {
            ans.push_back({f[i], f[n - 1]});
        }
    };

    auto work_for_normal = [&]() {
        int len = m * 2;

        int idx = n - len;
        for (int i = 0; i < idx; i++) {
            ans.push_back({f[i], f[i + 1]});
        }

        for (int i = idx; i < n; i += 2) {
            ans.push_back({f[i + 1], f[i]});
        }
    };

    if (mx > sum - mx) {
        // 一定会留一个
        if (m == 0) {
            cout << -1 << '\n';
            return;
        }
        if (m * 2 > n) {
            cout << -1 << '\n';
            return;
        }
        work_for_normal();
    } else {
        // 可以全死
        if (m == 0) {
            work_for_zero();
        } else if (m * 2 > n) {
            cout << -1 << '\n';
            return;
        } else {
            work_for_normal();
        }
    }

    cout << ans.size() << '\n';
    for (auto it : ans) {
        cout << it[0] + 1 << ' ' << it[1] + 1 << '\n';
    }
    debug("zz");
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