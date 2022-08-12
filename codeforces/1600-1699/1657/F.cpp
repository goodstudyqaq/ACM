#include <bits/stdc++.h>

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

struct TwoSat {
    // [0, 2 * n]
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}
    void addClause(int u, bool f, int v, bool g) {
        // (u, f) 和 (v, g) 有矛盾
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    bool satisfiable() {
        std::vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i)
            if (dfn[i] == -1) tarjan(i);

        /*
            方案可以通过变量在图中的拓扑序确定该变量的值，如果变量 !x 的拓扑序在 x 之后，那么 x 为真.
            应用到 tarjan 当中，即 x 的 SCC 编号在 !x 之前，取 x 为真。因为 tarjan 用到了栈，所以 tarjan 求出的 SCC 编号相当于反拓扑序。
        */

        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> parent, depth;
    parent.resize(n);
    depth.resize(n);

    auto dfs = [&](auto self, int u) -> void {
        for (auto v : V[u]) {
            if (parent[u] == v) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            self(self, v);
        }
    };
    parent[0] = -1;
    depth[0] = 1;
    dfs(dfs, 0);

    auto get_path = [&](int u, int v) -> vector<int> {
        if (depth[u] < depth[v]) swap(u, v);
        // d[u] > d[v]
        vector<int> p1, p2;
        while (depth[u] > depth[v]) {
            p1.push_back(u);
            u = parent[u];
        }

        while (u != v) {
            p1.push_back(u);
            p2.push_back(v);
            u = parent[u];
            v = parent[v];
        }
        p1.push_back(u);
        reverse(p2.begin(), p2.end());
        for (auto v : p2) {
            p1.push_back(v);
        }
        return p1;
    };

    vector<vector<int>> chose;
    chose.resize(n, vector<int>(2));
    vector<tuple<int, int, string>> query;
    for (int i = 0; i < q; i++) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        u--, v--;
        query.push_back({u, v, s});
        vector<int> path = get_path(u, v);
        int m = s.size();

        for (int j = 0; j < m; j++) {
            chose[path[j]][0] = s[j] - 'a';
            chose[path[j]][1] = s[m - j - 1] - 'a';
        }
    }
    TwoSat ts(n + q);
    for (int i = 0; i < q; i++) {
        auto [u, v, s] = query[i];

        vector<int> path = get_path(u, v);
        int m = s.size();
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 2; k++) {
                if (chose[path[j]][k] != s[j] - 'a') {
                    ts.addClause(path[j], k, n + i, 0);
                }
                if (chose[path[j]][k] != s[m - j - 1] - 'a') {
                    ts.addClause(path[j], k, n + i, 1);
                }
            }
        }
    }
    debug(chose);

    bool f = ts.satisfiable();
    if (f) {
        cout << "YES" << endl;
        auto ans = ts.answer();
        debug(ans);
        for (int i = 0; i < n; i++) {
            cout << (char)(chose[i][ans[i]] + 'a');
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}