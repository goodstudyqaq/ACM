#include <bits/stdc++.h>

#include <queue>

#include "./graph/connected-components/two-edge-connected-components.hpp"

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
    int n, m;
    cin >> n >> m;

    vector<pii> edges(m);
    TwoEdgeConnectedComponents<> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges[i] = {u, v};
        g.add_edge(u, v);
    }
    g.build();

    auto check = [&]() {
        return g.belong[0] != g.belong[n - 1];
    };
    debug(g.belong);

    if (!check()) {
        int q;
        cin >> q;
        while (q--) {
            int u;
            cin >> u;
            cout << -1 << ' ';
        }
        cout << '\n';
        return;
    }

    vector<int> fa(n);
    function<void(int, int)> dfs = [&](int u, int pre) {
        fa[u] = pre;
        for (auto v : g.tree[u]) {
            if (v == pre) {
                continue;
            }
            dfs(v, u);
        }
    };

    dfs(g.belong[0], -1);

    set<pii> need;
    int now = g.belong[n - 1];

    while (now) {
        int pre = fa[now];
        need.insert({pre, now});
        now = pre;
    }

    vector<int> ans(n, -1);
    typedef array<int, 3> a3;
    priority_queue<a3, vector<a3>, greater<>> Q;
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        int bu = g.belong[u], bv = g.belong[v];

        if (need.count({bu, bv}) || need.count({bv, bu})) {
            if (ans[u] == -1) {
                ans[u] = i;
                Q.push({1, ans[u], u});
            }
            if (ans[v] == -1) {
                ans[v] = i;
                Q.push({1, ans[v], v});
            }
        }
    }
    while (!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        int u = it[2];
        for (auto &e : g[u]) {
            if (ans[e] == -1) {
                ans[e] = it[1];
                Q.push({it[0] + 1, ans[e], e});
            }
        }
    }

    int query;
    cin >> query;
    while (query--) {
        int c;
        cin >> c;
        c--;
        cout << ans[c] + 1 << ' ';
    }
    cout << '\n';
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