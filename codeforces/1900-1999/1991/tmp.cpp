#line 1 "E.cpp"
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
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            ans[find(i)].push_back(i);
        }
        ans.erase(remove_if(ans.begin(), ans.end(), [&](const vector<int> &v) {
            return v.empty();
        }));
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
    vector<vector<Edge<T>>> g;
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

    inline vector<Edge<T>> &operator[](const int &k) { return g[k]; }

    inline const vector<Edge<T>> &operator[](const int &k) const { return g[k]; }
};

template <typename T = int>
using Edges = vector<Edge<T>>;
#line 3 "/Users/guoshen/code/library2/graph/bipartite-graph/bipartite-graph.hpp"
/*

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
#line 4 "E.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    BipartiteGraph<> bg(n);
    bg.read(m);

    // check 是否是二分图
    if (bg.bipartite_graph_coloring()) {
        // Bob 必胜
        cout << "Bob" << endl;
        vector<vector<int>> color_index(2);
        for (int i = 0; i < n; i++) {
            color_index[bg.color(i)].push_back(i);
        }

        auto bob_out = [&]() {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (a > b) swap(a, b);
            int i, c;

            if (b == 1) {
                if (color_index[0].size()) {
                    i = color_index[0].back() + 1;
                    c = 1;
                    color_index[0].pop_back();
                } else {
                    i = color_index[1].back() + 1;
                    c = 2;
                    color_index[1].pop_back();
                }
            } else {
                if (color_index[a].size()) {
                    i = color_index[a].back() + 1;
                    c = a + 1;
                    color_index[a].pop_back();
                } else {
                    int f = a ^ 1;
                    // i = f + 1;
                    i = color_index[f].back() + 1;
                    c = 3;
                    color_index[f].pop_back();
                }
            }
            cout << i << ' ' << c << endl;
        };

        for (int i = 0; i < n; i++) {
            bob_out();
        }

    } else {
        // Alice 必胜
        cout << "Alice" << endl;
        auto alice_out = [&](int a, int b) {
            cout << a << ' ' << b << endl;
            int i, c;
            cin >> i >> c;
            return pair<int, int>{i, c};
        };
        for (int i = 0; i < n; i++) {
            alice_out(1, 2);
        }
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
