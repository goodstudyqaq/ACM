#line 1 "C.cpp"
#include <bits/stdc++.h>

#line 3 "/Users/guoshen/code/library2/structure/union-find/union-find.hpp"

using namespace std;

struct UnionFind {
    vector<int> data;
    vector<int> f;

    UnionFind() = default;

    explicit UnionFind(size_t sz) : data(sz, 1), f(sz) {
        iota(f.begin(), f.end(), 0);
    }

    bool unite(int x, int y) {  // x merge to y
        x = find(x), y = find(y);
        if (x == y) return false;
        data[y] += data[x];
        f[x] = y;
        return true;
    }
    int find(int x) {
        if (f[x] == x) return x;
        int y = find(f[x]);
        data[y] += data[x];
        f[x] = y;
        return f[x];
    }
    int size(int x) {
        return data[find(x)];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    vector<vector<int>> groups() {
        int n = (int)data.size();
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[find(i)].push_back(i);
        }

        ans.erase(remove_if(ans.begin(), ans.end(), [&](const vector<int>& v) {
                      return v.empty();
                  }),
                  ans.end());
        return ans;
    }
};
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
#line 3 "/Users/guoshen/code/library2/graph/bipartite-graph/bipartite-graph.hpp"
/*
二分图染色，判断一个图是否是二分图
//https://codeforces.com/contest/1991/problem/E
*/

template <typename T = int>
struct BipartiteGraph : Graph<T> {
    using Graph<T>::Graph;
    using Graph<T>::size;
    UnionFind uf;
    vector<int> _color;

    explicit BipartiteGraph(int n) : Graph<T>(n), uf(2 * n), _color(2 * n, -1) {}

    void add_edge(int from, int to, T cost = 1) {
        Graph<T>::add_edge(from, to, cost);
        uf.unite(from, to + size());
        uf.unite(to, from + size());
    }

    bool bipartite_graph_coloring() {
        int n = size();
        for (int i = 0; i < n; i++) {
            int a = uf.find(i);
            int b = uf.find(i + n);
            if (a == b) return false;
            if (_color[a] < 0) _color[a] = 0, _color[b] = 1;
        }
        return true;
    }

    int color(int u) {
        return _color[uf.find(u)];
    }
};
#line 4 "C.cpp"

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
    int n;
    cin >> n;
    vector<int> a(n);
    BipartiteGraph<> g(n);
    set<int> vis;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        vis.insert(a[i]);
    }

    set<int> choose;
    for (int i = 0; i < n; i++) {
        if (vis.count(i) == 0) {
            // i 不在 a[i] 出现过，所以一定不能选 i, 所以要选 a[i]
            choose.insert(a[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (choose.count(i)) {
            continue;
        }
        g.add_edge(i, a[i]);
    }

    if (!g.bipartite_graph_coloring()) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<int>> group(2);
    for (int i = 0; i < n; i++) {
        group[g.color(i)].push_back(i);
    }
    // 选择 0，留下来的都是 color = 1 的点
    set<int> S1, S2;
    for (int u : group[0]) {
        S1.insert(u);
    }
    for (int u : group[1]) {
        S2.insert(a[u]);
    }
    if (S1 == S2) {
        cout << group[1].size() << endl;
        for (int u : group[1]) {
            cout << a[u] + 1 << ' ';
        }
        cout << endl;
    } else {
        cout << group[0].size() << endl;
        for (int u : group[0]) {
            cout << a[u] + 1 << ' ';
        }
        cout << endl;
    }
}
