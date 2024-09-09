#line 1 "B.cpp"
#include <bits/stdc++.h>

#line 3 "/Users/guoshen/code/library2/graph/graph-template.hpp"
using namespace std;

template <typename T = int>
struct Edge {
    int from, to;
    T cost;
    int idx;

    Edge() = default;

    Edge(int from, int to, T cost = 1, int idx = -1)
        : from(from), to(to), cost(cost), idx(idx) {}

    operator int() const { return to; }
};

template <typename T = int>
struct Graph {
    vector<vector<Edge<T> > > g;
    int es;

    Graph() = default;

    explicit Graph(int n) : g(n), es(0) {}

    size_t size() const { return g.size(); }

    virtual void add_directed_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es++);
    }

    // virtual 可以被重载，实现多态
    virtual void add_edge(int from, int to, T cost = 1) {
        g[from].emplace_back(from, to, cost, es);
        g[to].emplace_back(to, from, cost, es++);
    }

    void read(int M, int padding = -1, bool weighted = false,
              bool directed = false) {
        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a += padding;
            b += padding;
            T c = T(1);
            if (weighted) cin >> c;
            if (directed)
                add_directed_edge(a, b, c);
            else
                add_edge(a, b, c);
        }
    }

    inline vector<Edge<T> > &operator[](const int &k) { return g[k]; }

    inline const vector<Edge<T> > &operator[](const int &k) const { return g[k]; }
};

template <typename T = int>
using Edges = vector<Edge<T> >;
#line 2 "/Users/guoshen/code/library2/graph/tree/doubling-lowest-common-ancestor.hpp"
/*
树上倍增找 lca
*/

template <typename T = int>
struct DoublingLowestCommonAncestor : Graph<T> {
    using Graph<T>::g;
    vector<int> dep;
    vector<T> sum;
    vector<vector<int> > table;
    const int LOG;

    explicit DoublingLowestCommonAncestor(int n)
        : Graph<T>(n), LOG(32 - __builtin_clz(g.size())) {}

    explicit DoublingLowestCommonAncestor(const Graph<T> &g)
        : LOG(32 - __builtin_clz(g.size())), Graph<T>(g) {}

    void build(int root = 0) {
        dep.assign(g.size(), 0);
        sum.assign(g.size(), 0);
        table.assign(LOG, vector<int>(g.size(), -1));
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < LOG; k++) {
            for (int i = 0; i < (int)table[k].size(); i++) {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
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

    int climb(int u, int k) {
        if (dep[u] < k) return -1;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((k >> i) & 1) u = table[i][u];
        }
        return u;
    }

    T dist(int u, int v) { return sum[u] + sum[v] - 2 * sum[lca(u, v)]; }

   private:
    void dfs(int idx, int par, int d) {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx]) {
            if (to != par) {
                sum[to] = sum[idx] + to.cost;
                dfs(to, idx, d + 1);
            }
        }
    }
};
#line 4 "B.cpp"

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
