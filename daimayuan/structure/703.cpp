#include <bits/stdc++.h>

#include <algorithm>
#include <utility>

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
    vector<vector<pair<int, int>>> sum(n + 1);
    int tot = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        l[u] = ++tot;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            sum[u].push_back({l[v], r[v]});
        }
        r[u] = tot;
    };
    int root = 1;
    dfs(1, -1);
    BIT<long long> bit(n + 1);
    for (int i = 1; i <= n; i++) {
        bit.add(l[i], w[i]);
    }

    while (q--) {
        debug(q);
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y;
            cin >> x >> y;
            bit.add(l[x], y - w[x]);
            w[x] = y;
        } else if (ty == 2) {
            int x;
            cin >> x;
            if (root == x) {
                cout << bit.query(n) << '\n';
            } else if (l[x] < l[root] && l[root] <= r[x]) {
                int child = upper_bound(sum[x].begin(), sum[x].end(), make_pair(l[root], (int)1e9)) - sum[x].begin() - 1;
                int _l = sum[x][child].first, _r = sum[x][child].second;
                cout << bit.query(n) - (bit.query(_r) - bit.query(_l - 1)) << '\n';
            } else {
                cout << bit.query(r[x]) - bit.query(l[x] - 1) << '\n';
            }

        } else {
            int x;
            cin >> x;
            root = x;
        }
    }
}