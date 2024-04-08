#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

template <typename T>
struct Edge {
    int from, to, idx;
    T cost;

    Edge() = default;
    Edge(int from, int to, int idx, T cost = 1) : from(from), to(to), idx(idx), cost(cost) {}

    // Edge e = Edge(); int to = e;
    operator int() const { return to; }
};

// [0, n)
template <typename Edge>
struct Graph {  // 通过 vector 来进行存储边
    vector<vector<Edge>> g;

    Graph() = default;
    explicit Graph(int n) : g(n) {}

    size_t size() const {
        return g.size();
    }

    void add_directed_edge(const Edge &e) {
        g[e.from].push_back(e);
    }

    void add_undirected_edge(const Edge &e) {
        g[e.from].push_back(e);
        Edge rev = e;
        swap(rev.from, rev.to);
        g[rev.from].push_back(rev);
    }

    inline const vector<Edge> &operator[](const int &u) const {
        return g[u];
    }
};

template <typename Edge>
struct Tree : Graph<Edge> {
    using Graph<Edge>::g;
    using Graph<Edge>::add_directed_edge;
    using Graph<Edge>::add_undirected_edge;
    using Graph<Edge>::size;
    int root;

    Tree() = default;
    // root = -1 为无根树
    explicit Tree(int n, int root = -1) : Graph<Edge>(n), root(root) {}

    // todo: 可以加一些常用的树的操作，比如求重心，求直径，求子树大小等
    vector<int> get_diamater() {
        // 求直径
        int n = g.size();
        vector<int> fa(n), dep(n);

        function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
            fa[u] = pre;
            dep[u] = d;
            for (auto v : g[u]) {
                if (v == pre) continue;
                dfs(v, u, d + 1);
            }
        };
        dfs(0, -1, 0);
        int rt = 0;
        for (int i = 0; i < n; i++) {
            if (dep[rt] < dep[i]) {
                rt = i;
            }
        }

        dfs(rt, -1, 0);

        for (int i = 0; i < n; i++) {
            if (dep[rt] < dep[i]) {
                rt = i;
            }
        }
        vector<int> ans;
        int now = rt;
        while (now != -1) {
            ans.push_back(now);
            now = fa[now];
        }
        return ans;
    }
};

struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

template <typename Edge>
Tree<Edge> get_mst(int n, vector<Edge> edges) {
    DSU dsu(n);

    sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) {
        return a.cost < b.cost;
    });

    Tree<Edge> tree(n);
    int m = edges.size();
    for (int i = 0; i < m; i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        if (dsu.leader(u) == dsu.leader(v)) {
            continue;
        }
        tree.add_undirected_edge(edges[i]);
        dsu.merge(u, v);
    }
    return tree;
}

template <typename Tree>
struct Lca {
    Lca(Tree &tree) : tree(tree), root(tree.root) {}
    pair<int, int> get_lca(int x, int y) {
        int the_mx = 0;
        if (dep[x] > dep[y]) swap(x, y);
        for (int j = LOG - 1; j >= 0 && dep[x] != dep[y]; j--) {
            if (dep[y] - (1 << j) < dep[x]) continue;
            the_mx = max(the_mx, mx[y][j]);
            y = parent[y][j];
        }
        if (x == y) return {x, the_mx};
        for (int j = LOG - 1; j >= 0; j--) {
            if (dep[x] - (1 << j) < 0 || parent[x][j] == parent[y][j]) continue;
            the_mx = max(the_mx, mx[x][j]);
            the_mx = max(the_mx, mx[y][j]);
            x = parent[x][j], y = parent[y][j];
        }
        the_mx = max({the_mx, mx[x][0], mx[y][0]});
        return {parent[x][0], the_mx};
    }

    void build(int rt = -1) {
        int n = tree.size();
        // 2^k <= n

        if (rt != -1) root = rt;
        assert(root != -1);

        LOG = lg2(n) + 1;
        dep.resize(n);
        parent.resize(n, vector<int>(LOG, -1));
        mx.resize(n, vector<int>(LOG, -1));
        dfs(root, -1, 0, 0);
        rmq(n);
    }

   private:
    vector<int> dep;
    vector<vector<int>> parent;
    vector<vector<int>> mx;
    Tree &tree;
    int root;
    int LOG;
    int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }
    void dfs(int u, int pre, int val, int d) {
        parent[u][0] = pre;
        mx[u][0] = val;
        dep[u] = d;
        for (auto v : tree[u]) {
            if (v == pre) continue;
            dfs(v, u, v.cost, d + 1);
        }
    }
    void rmq(int n) {
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if ((1 << i) > dep[j]) continue;
                int k = parent[j][i - 1];
                parent[j][i] = parent[k][i - 1];
                mx[j][i] = max(mx[j][i - 1], mx[k][i - 1]);
            }
        }
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    typedef Edge<int> e;
    vector<e> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edges[i] = e(u, v, i, c);
    }

    Tree<e> tree = get_mst(n, edges);
    long long ans = 0;
    set<int> idx;
    for (int i = 0; i < n; i++) {
        for (auto v : tree.g[i]) {
            idx.insert(v.idx);
            ans += v.cost;
        }
    }
    ans /= 2;
    tree.root = 0;

    Lca<Tree<e>> lca(tree);
    lca.build();
    debug(idx);

    for (int i = 0; i < m; i++) {
        // debug(i);
        if (idx.count(i)) {
            cout << ans << endl;
        } else {
            int u = edges[i].from, v = edges[i].to;
            auto it = lca.get_lca(u, v);
            debug(u, v, it, edges[i].cost);
            long long res = ans - it.second + edges[i].cost;
            cout << res << endl;
        }
    }
    return 0;
}