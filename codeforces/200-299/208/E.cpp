#include <bits/stdc++.h>

#include <vector>

#include "graph/graph-template.hpp"

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
    Graph<> g(n);
    vector<int> rts;

    const int LIMIT = 17;
    vector<vector<int>> par(n, vector<int>(LIMIT, -1));

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        if (p >= 0) {
            par[i][0] = p;
            g.add_directed_edge(p, i);
        } else {
            rts.push_back(i);
        }
    }

    for (int i = 1; i < LIMIT; i++) {
        for (int j = 0; j < n; j++) {
            int p = par[j][i - 1];
            if (p != -1) {
                par[j][i] = par[p][i - 1];
            }
        }
    }

    vector<int> dep(n);
    function<void(int, int)> dfs = [&](int u, int d) {
        dep[u] = d;
        for (auto v : g[u]) {
            dfs(v, d + 1);
        }
    };

    for (auto rt : rts) {
        dfs(rt, 0);
    }

    auto climb = [&](int u, int p) {
        for (int i = LIMIT - 1; i >= 0; i--) {
            if ((p >> i) & 1) {
                u = par[u][i];
                if (u == -1) {
                    return -1;
                }
            }
        }
        return u;
    };

    int q;
    cin >> q;
    vector<vector<pair<int, int>>> query(n);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int v, p;
        cin >> v >> p;
        v--;
        int fa = climb(v, p);
        if (fa == -1) {
            ans[i] = 0;
        } else {
            query[fa].push_back({dep[v], i});
        }
    }

    function<map<int, int>(int)> dfs2 = [&](int u) -> map<int, int> {
        map<int, int> M;
        M[dep[u]] = 1;

        for (auto v : g[u]) {
            auto m = dfs2(v);

            if (m.size() > M.size()) {
                swap(m, M);
            }
            for (auto it : m) {
                M[it.first] += it.second;
            }
        }

        for (auto it : query[u]) {
            ans[it.second] = M[it.first] - 1;
        }
        return M;
    };
    for (auto rt : rts) {
        dfs2(rt);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}