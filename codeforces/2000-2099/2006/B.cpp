#include <bits/stdc++.h>

#include "./graph/tree/doubling-lowest-common-ancestor.hpp"

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
    long long w;
    cin >> n >> w;

    DoublingLowestCommonAncestor<> lca(n);
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        lca.add_edge(p[i], i);
    }
    lca.build(0);

    vector<int> sz(n);
    function<void(int, int)> dfs = [&](int u, int pre) {
        sz[u] = 1;
        for (auto v : lca[u]) {
            if (v == pre) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
    };

    dfs(0, -1);
    // debug("dfs");

    vector<int> sure(n);
    vector<int> dist(n);

    for (int i = 0; i < n; i++) {
        int v = (i + 1) % n;
        dist[i] = lca.dist(i, v);
    }

    vector<long long> val(n, 0);
    long long sure_edge_val_sum = 0;
    int sure_num = 0;

    for (int i = 0; i < n - 1; i++) {
        int u;
        long long y;
        cin >> u >> y;
        u--;
        int _sz = sz[u];
        sure_edge_val_sum += y;

        sure[u - 1]++;
        if (sure[u - 1] == dist[u - 1]) sure_num++;
        sure[u + _sz - 1]++;
        if (sure[u + _sz - 1] == dist[u + _sz - 1]) sure_num++;

        cout << sure_edge_val_sum * 2 + (w - sure_edge_val_sum) * (n - sure_num) << ' ';
    }
    cout << endl;
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