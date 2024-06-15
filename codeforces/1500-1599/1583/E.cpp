#include <bits/stdc++.h>

#include <algorithm>
#include <cstdint>
#include <functional>

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
typedef pair<int, int> pii;

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<pii> edges(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }
    int q;
    cin >> q;
    vector<vector<int>> V2(n + 1);
    vector<pii> queries(q + 1);
    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        queries[i] = {a, b};
        V2[a].push_back(b);
        V2[b].push_back(a);
    }

    vector<int> V3;
    for (int i = 1; i <= n; i++) {
        if (V2[i].size() % 2) {
            V3.push_back(i);
        }
    }

    if (V3.size() != 0) {
        cout << "NO" << endl;
        cout << V3.size() / 2 << endl;
        return 0;
    } else {
        cout << "YES" << endl;
    }

    vector<vector<int>> V(n + 1);
    DSU dsu(n + 1);
    for (int i = 1; i <= m; i++) {
        auto [u, v] = edges[i];
        int fu = dsu.leader(u);
        int fv = dsu.leader(v);
        if (fu != fv) {
            V[u].push_back(v);
            V[v].push_back(u);
            dsu.merge(u, v);
        }
    }
    debug(V);
    vector<int> fa(n + 1), dep(n + 1);

    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        fa[u] = pre;
        dep[u] = d;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(1, 0, 0);

    for (int i = 1; i <= q; i++) {
        auto [a, b] = queries[i];

        vector<int> tmp1, tmp2;
        int x = a, y = b;
        while (x != y) {
            if (dep[x] > dep[y]) {
                tmp1.push_back(x);
                x = fa[x];
            } else {
                tmp2.push_back(y);
                y = fa[y];
            }
        }
        cout << tmp1.size() + tmp2.size() + 1 << endl;
        for (int i = 0; i < tmp1.size(); i++) {
            cout << tmp1[i] << ' ';
        }
        cout << x << ' ';
        for (int i = tmp2.size() - 1; i >= 0; i--) {
            cout << tmp2[i] << ' ';
        }
        cout << endl;
    }

}