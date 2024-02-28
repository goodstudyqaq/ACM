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

struct Edge {
    int from, to;
    int cost;

    Edge() = default;
    Edge(int from, int to, int cost = 1) : from(from), to(to), cost(cost) {}

    // Edge e = Edge(); int to = e;
    operator int() const { return to; }
};

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
};

template <typename Tree>
struct Lca {
    vector<int> dep;
    vector<vector<int>> parent;
    Lca(Tree &tree) : tree(tree), root(tree.root) {}
    int get_lca(int x, int y) {
        if (dep[x] > dep[y]) swap(x, y);
        for (int j = LOG - 1; j >= 0 && dep[x] != dep[y]; j--) {
            if (dep[y] - (1 << j) < dep[x]) continue;
            y = parent[y][j];
        }
        if (x == y) return x;
        for (int j = LOG - 1; j >= 0; j--) {
            if (dep[x] - (1 << j) < 0 || parent[x][j] == parent[y][j]) continue;
            x = parent[x][j], y = parent[y][j];
        }
        return parent[x][0];
    }

    void build(int rt = -1) {
        int n = tree.size();
        // 2^k <= n

        if (rt != -1) root = rt;
        assert(root != -1);

        LOG = lg2(n) + 1;
        dep.resize(n);
        parent.resize(n, vector<int>(LOG, -1));
        dfs(root, -1, 0);
        rmq(n);
    }

    int go(int x, int step) {
        // x 点向上走 step 步的位置
        if (dep[x] < step) {
            return -1;
        }
        int now = x;
        for (int i = LOG - 1; i >= 0; i--) {
            if ((step >> i) & 1) {
                now = parent[now][i];
            }
        }
        return now;
    }

   private:
    Tree &tree;
    int root;
    int LOG;
    int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }
    void dfs(int u, int pre, int d) {
        parent[u][0] = pre;
        dep[u] = d;
        for (auto v : tree[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    }
    void rmq(int n) {
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                if ((1 << i) > dep[j]) continue;
                int k = parent[j][i - 1];
                parent[j][i] = parent[k][i - 1];
            }
        }
    }
};

void solve() {
    int n;
    string s;
    cin >> n >> s;

    const int inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<int>> parent(n + 1, vector<int>(n + 1, 0));

    vector<int> dep(n + 1), fa(n + 1);
    function<void(int, int, int)> dfs1 = [&](int u, int pre, int d) {
        dep[u] = d;
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs1(v, u, d + 1);
        }
    };
    dfs1(1, -1, 0);

    function<int(int, int)> find = [&](int u, int v) {
        if (parent[u][v]) return parent[u][v];
        if (u == v) return u;
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        return parent[u][v] = find(fa[u], v);
    };

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            parent[i][j] = find(i, j);
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    function<int(int, int)> dfs = [&](int u, int v) -> int {
        if (dp[u][v] != -1) return dp[u][v];
        if (u == v) return 1;
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        if (fa[u] == v) {
            return (s[u - 1] == s[v - 1] ? 2 : 1);
        }

        int gou, gov;
        gou = fa[u];
        if (parent[u][v] != v) {
            gov = fa[v];
        } else {
            for (auto v2 : V[v]) {
                if (v2 != fa[v] && parent[u][v2] == v2) {
                    gov = v2;
                    break;
                }
            }
        }

        debug(u, v, gou, gov);
        int ans = max(dfs(gou, v), dfs(u, gov));
        if (s[u - 1] == s[v - 1]) {
            ans = max(ans, dfs(gou, gov) + 2);
        }
        return dp[u][v] = ans;
    };

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (dp[i][j] == -1) {
                debug(i, j);
                ans = max(ans, dfs(i, j));
            }
        }
    }
    cout << ans << endl;
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