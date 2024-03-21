#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

template <typename T>
struct Edge {
    int from, to;
    T cost;

    Edge() = default;
    Edge(int from, int to, T cost = 1) : from(from), to(to), cost(cost) {}

    // Edge e = Edge(); int to = e;
    operator int() const { return to; }
};

// [0, n)
template <typename Edge>
struct Graph {
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

void solve() {
    int n;
    cin >> n;

    typedef Edge<int> ei;
    Tree<ei> tree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        tree.add_undirected_edge(ei(u, v));
    }

    auto diamater = tree.get_diamater();
    int m = diamater.size();

    if (m % 2) {
        // 奇数直接搞
        int rt = m / 2;
        int idx = diamater[rt];
        cout << rt + 1 << endl;
        for (int i = 0; i <= rt; i++) {
            cout << idx + 1 << ' ' << i << endl;
        }
    } else {
        if (m % 4 == 0) {
            int u1 = m / 2 - 1;
            int u2 = m / 2;
            int u1_idx = diamater[u1];
            int u2_idx = diamater[u2];

            int limit = m / 2 - 1;
            // 1 3 5 ... limit

            int times = m / 2;
            cout << times << endl;
            for (int i = 1; i <= limit; i += 2) {
                cout << u1_idx + 1 << ' ' << i << endl;
                cout << u2_idx + 1 << ' ' << i << endl;
            }
        } else {
            // m % 4 == 2
            int rt = (m - 1) / 2;
            int idx = diamater[rt];
            cout << rt + 2 << endl;
            for (int i = 0; i <= rt; i++) {
                cout << idx + 1 << ' ' << i << endl;
            }
            cout << idx + 1 << ' ' << rt + 1 << endl;
            // cout << diamater[m - 2] + 1 << ' ' << 1 << endl;
        }
    }
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