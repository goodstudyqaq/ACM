#include <bits/stdc++.h>

#include "./structure/union-find/union-find.hpp"

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
    int n;
    cin >> n;
    UnionFind uf(2 * n + 1);

    vector<int> a(n), b(n);
    vector<int> vis(n);
    int sz = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];

        if (uf.same(a[i], b[i])) {
            continue;
        }
        vis[i] = 1;
        sz++;
        uf.unite(a[i], b[i]);
    }
    cout << sz << '\n';
    // set<pii> S;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            // S.insert({a[i], b[i]});
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';

    // int l = 0, r = 0;
    // // [l, r)
    // int ans = 0;
    // for (auto it : S) {
    //     if (it.first <= r) {
    //         r = max(r, it.second);
    //     } else {
    //         ans += r - l;
    //         l = it.first;
    //         r = it.second;
    //     }
    // }
    // ans += r - l;
    // cout << ans << '\n';
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