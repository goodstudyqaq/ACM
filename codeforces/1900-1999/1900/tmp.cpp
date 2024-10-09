#line 1 "E.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/graph/connected-components/strongly-connected-components.hpp"

/*
Kosaraju 算法
复杂度 O(E + V)
强联通分量：一个强联通分量里的任意两个点两两互达
*/

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
#line 10 "/Users/guoshen/code/library2/graph/connected-components/strongly-connected-components.hpp"

template <typename T = int>
struct StronglyConnectedComponents : Graph<T> {
   public:
    using Graph<T>::Graph;
    using Graph<T>::g;
    vector<int> comp;           // comp[i] i 点在的组 id
    Graph<T> dag;               // 缩点后的图
    vector<vector<int>> group;  // group[i] 表示第 i 组有的点

    void build() {
        int n = g.size();
        rg = Graph<T>(n);
        for (int i = 0; i < n; i++) {
            for (auto &e : g[i]) {
                int u = e.from, v = e.to;
                rg.add_directed_edge(v, u, e.cost);
            }
        }

        used = vector<int>(n, 0);
        comp = vector<int>(n, -1);

        for (int i = 0; i < n; i++) {
            if (used[i] == 0) {
                dfs(i);
            }
        }
        reverse(order.begin(), order.end());

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int u = order[i];
            if (comp[u] == -1) {
                rdfs(u, cnt);
                cnt++;
            }
        }

        dag = Graph<T>(cnt);
        group.resize(cnt);
        for (int i = 0; i < n; i++) {
            for (auto &e : g[i]) {
                int u = comp[e.from], v = comp[e.to];
                if (u == v) continue;
                dag.add_directed_edge(u, v, e.cost);
            }
            group[comp[i]].push_back(i);
        }
    }

    int operator[](int k) const {
        return comp[k];
    }

   private:
    vector<int> order, used;
    Graph<T> rg;

    void dfs(int idx) {
        used[idx] = 1;
        for (auto &e : g[idx]) {
            int v = e.to;
            if (used[v] == 0) {
                dfs(v);
            }
        }
        order.push_back(idx);
    }

    void rdfs(int idx, int cnt) {
        comp[idx] = cnt;
        for (auto &e : rg[idx]) {
            int v = e.to;
            if (comp[v] == -1) {
                rdfs(v, cnt);
            }
        }
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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    StronglyConnectedComponents<int> g(n);
    g.read(m, -1, false, true);
    g.build();

    auto dag = g.dag;

    int n2 = dag.size();
    vector<int> in(n2);
    for (int i = 0; i < n2; i++) {
        for (auto v : dag[i]) {
            in[v]++;
        }
    }

    vector<long long> sum(n2);
    for (int i = 0; i < n; i++) {
        sum[g.comp[i]] += a[i];
    }

    queue<int> Q;
    vector<pair<int, long long>> res(n2);
    for (int i = 0; i < n2; i++) {
        if (in[i] == 0) {
            Q.push(i);
            res[i] = {g.group[i].size(), sum[i]};
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto v : dag[u]) {
            in[v]--;
            if (res[v].first < res[u].first + g.group[v].size()) {
                res[v].first = res[u].first + g.group[v].size();
                res[v].second = res[u].second + sum[v];
            } else if (res[v].first == res[u].first + g.group[v].size()) {
                res[v].second = min(res[v].second, res[u].second + sum[v]);
            }
            if (in[v] == 0) {
                Q.push(v);
            }
        }
    }
    pair<int, long long> ans = {0, 0};
    for (int i = 0; i < n2; i++) {
        if (ans.first < res[i].first) {
            ans = res[i];
        } else if (ans.first == res[i].first) {
            ans = min(ans, res[i]);
        }
    }
    cout << ans.first << ' ' << ans.second << endl;
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
