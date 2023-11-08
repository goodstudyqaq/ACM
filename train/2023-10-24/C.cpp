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
    vector<int> a(n), d(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    if (mx == 0) {
        cout << 0 << endl;
        return;
    }

    vector<vector<pii>> g(n);
    for (int i = 0; i < n; i++) {
        int l = max(0, i - d[i]);
        int r = min(n - 1, i + d[i]);
        g[l].push_back({r, a[i]});
    }

    int l = 0, r = mx;
    int ans = -1;

    auto check = [&](int mx) {
        vector<int> tmpa = a;
        priority_queue<pii, vector<pii>, greater<pii>> Q;
        for (int i = 0; i < n; i++) {
            for (auto it : g[i]) {
                Q.push(it);
            }
            int x = mx;
            while (x && Q.size()) {
                auto it = Q.top();
                Q.pop();
                if (it.first < i) return false;
                int tmp = min(it.second, x);
                it.second -= tmp;
                x -= tmp;
                if (it.second) {
                    Q.push(it);
                }
            }
        }
        if (Q.size()) {
            return false;
        }
        return true;
    };

    // check(5);
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
    return 0;
}