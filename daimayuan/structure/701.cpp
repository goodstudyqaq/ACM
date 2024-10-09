#include <bits/stdc++.h>

#include "./graph/graph-template.hpp"
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

template <typename T = int>
struct DoublingLowestCommonAncestor : Graph<T> {
    using Graph<T>::g;
    vector<int> dep;
    vector<vector<T> > mi;
    vector<vector<int> > table;
    const int LOG;

    explicit DoublingLowestCommonAncestor(int n)
        : Graph<T>(n), LOG(32 - __builtin_clz(g.size())) {}

    explicit DoublingLowestCommonAncestor(const Graph<T> &g)
        : LOG(32 - __builtin_clz(g.size())), Graph<T>(g) {}

    void build(int root = 0) {
        dep.assign(g.size(), 0);
        mi.assign(LOG, vector<int>(g.size(), -1));
        table.assign(LOG, vector<int>(g.size(), -1));
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int i = 0; i < (int)table[k].size(); i++) {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else {
                    mi[k + 1][i] = min(mi[k][i], mi[k][table[k][i]]);
                    table[k + 1][i] = table[k][table[k][i]];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        v = climb(v, dep[v] - dep[u]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (table[i][u] != table[i][v]) {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }

    int get_mi(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        int d = dep[v] - dep[u];
        int res = 1e9 + 1;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((d >> i) & 1) {
                res = min(res, mi[i][v]);
                v = table[i][v];
            }
        }
        if (u == v) return res;

        for (int i = LOG - 1; i >= 0; i--) {
            if (table[i][u] != table[i][v]) {
                res = min(res, min(mi[i][u], mi[i][v]));
                u = table[i][u];
                v = table[i][v];
            }
        }

        return min(res, min(mi[0][u], mi[0][v]));
    }

    int climb(int u, int k) {
        if (dep[u] < k) return -1;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((k >> i) & 1) u = table[i][u];
        }
        return u;
    }

   private:
    void dfs(int idx, int par, int d) {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &e : g[idx]) {
            if (e.to != par) {
                mi[0][e.to] = e.cost;
                dfs(e.to, idx, d + 1);
            }
        }
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    DoublingLowestCommonAncestor<int> g(n);
    g.read(n - 1, -1, true);
    g.build(0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << g.get_mi(u, v) << '\n';
    }
}