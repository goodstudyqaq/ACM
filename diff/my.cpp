#line 1 "E.cpp"
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
#line 2 "/Users/guoshen/code/library2/graph/tree/heavy-light-decomposition.hpp"
template <typename T = int>
struct HeavyLightDecomposition : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    /*
        sz[u]: u 子树大小
        par[u]: u 的父亲
        dep[u]: u 的深度
        in[u]: dfs 序 u 进来的时间戳
        out[u]: dfs 序 u 出去的时间戳
        head[u]: u 所在的重链的起始位置
        rev[t]: 时间戳为 t 时对应的节点
    */
    vector<int> sz, in, out, head, rev, par, dep;

    void build(int root = 0) {
        sz.assign(g.size(), 0);
        in.assign(g.size(), 0);
        out.assign(g.size(), 0);
        head.assign(g.size(), 0);
        rev.assign(g.size(), 0);
        par.assign(g.size(), 0);
        dep.assign(g.size(), 0);

        dfs_sz(root, -1, 0);
        int t = 0;
        head[root] = root;
        dfs_hld(root, -1, t);
    }

    int la(int v, int k) {
        // v 向上走 k 步到的点
        assert(dep[v] >= k);
        while (1) {
            int u = head[v];
            if (in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

    int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    vector<tuple<int, int, bool>> dec(int u, int v) {
        vector<tuple<int, int, bool>> pu, pv;
        while (head[u] != head[v]) {
            if (in[u] > in[v]) {
                pu.emplace_back(in[head[u]], in[u], true);
                u = par[head[u]];
            } else {
                pv.emplace_back(in[head[v]], in[v], false);
                v = par[head[v]];
            }
        }
        if (in[u] <= in[v])
            pv.emplace_back(in[u], in[v], false);
        else
            pu.emplace_back(in[v], in[u], true);
        reverse(pv.begin(), pv.end());
        pu.insert(pu.end(), pv.begin(), pv.end());
        return pu;
    }

   private:
    void dfs_sz(int u, int pre, int d) {
        dep[u] = d;
        par[u] = pre;
        sz[u] = 1;
        if (g[u].size() && g[u][0] == pre) swap(g[u][0], g[u].back());
        for (auto &v : g[u]) {
            if (v == pre) continue;
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[g[u][0]] < sz[v]) swap(g[u][0], v);
        }
    }

    void dfs_hld(int u, int pre, int &times) {
        in[u] = times++;
        rev[in[u]] = u;
        for (auto &v : g[u]) {
            if (v == pre) continue;
            head[v] = (g[u][0] == v ? head[u] : v);
            dfs_hld(v, u, times);
        }
        out[u] = times;
    }
};
#line 4 "E.cpp"

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
    HeavyLightDecomposition<> g(n);
    g.read(n - 1);
    g.build();
    int len = sqrt(n * log(n) / log(2));
    debug(len);
    typedef pair<int, int> pii;
    vector<pii> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].second--;
    }
    vector<int> dis(n);
    for (int i = 0; i < n; i++) {
        dis[i] = g.dep[i];
    }

    for (int i = 0; i < q; i += len) {
        int r = min(q, i + len);
        // [i, r)
        vector<int> red;
        for (int j = i; j < r; j++) {
            if (queries[j].first == 1) {
                red.push_back(queries[j].second);
            } else {
                int v = queries[j].second;
                for (auto u : red) {
                    dis[v] = min(dis[v], g.dist(u, v));
                }
                cout << dis[v] << '\n';
            }
        }

        queue<int> Q;

        for (int j = i; j < r; j++) {
            if (queries[j].first == 1) {
                debug(queries[j].second);
                dis[queries[j].second] = 0;
                Q.push(queries[j].second);
            }
        }
        debug(dis);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            debug(u, dis[u]);
            for (auto v : g[u]) {
                debug(int(v), dis[v]);
                if (dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    Q.push(v);
                }
            }
        }
    }
}
