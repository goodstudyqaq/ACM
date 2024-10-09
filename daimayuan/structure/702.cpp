#include <bits/stdc++.h>

#include "./structure/others/binary-indexed-tree.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    vector<int> l(n + 1), r(n + 1);
    int tot = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        l[u] = ++tot;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
        r[u] = tot;
    };

    dfs(1, -1);
    BIT<long long> bit(n + 1), bit2(n + 1);
    for (int i = 1; i <= n; i++) {
        bit.add(l[i], w[i]);
        bit2.add(l[i], w[i]);
        bit2.add(r[i] + 1, -w[i]);
    }

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y;
            cin >> x >> y;
            bit.add(l[x], y - w[x]);
            bit2.add(l[x], y - w[x]);
            bit2.add(r[x] + 1, -(y - w[x]));
            w[x] = y;
        } else {
            int x;
            cin >> x;
            cout << bit.query(r[x]) - bit.query(l[x] - 1) << ' ' << bit2.query(l[x]) << '\n';
        }
    }
}