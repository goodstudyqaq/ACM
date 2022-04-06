#include <bits/stdc++.h>
using namespace std;
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }
struct Lca {
    // [1, n]
    vector<vector<int>>& g;
    vector<int> dep;
    vector<vector<int>> parent;
    int LOG;
    void dfs(int u, int pre, int d) {
        parent[u][0] = pre;
        dep[u] = d;
        for (auto v : g[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    }
    void rmq(int n) {
        for (int i = 1; i < LOG; i++) {
            for (int j = 1; j <= n; j++) {
                if ((1 << i) > dep[j]) continue;
                int k = parent[j][i - 1];
                parent[j][i] = parent[k][i - 1];
            }
        }
    }

    Lca(vector<vector<int>>& Graph, int rt = -1) : g(Graph) {
        int n = Graph.size();
        LOG = lg2(n);
        dep.resize(n + 1);
        parent.resize(n + 1, vector<int>(LOG, -1));
        if (rt == -1) {
            rt = 1;
        }
        dfs(rt, -1, 0);
        rmq(n);
    }

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
};