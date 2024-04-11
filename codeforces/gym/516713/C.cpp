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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<vector<int>> V(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<char> ans(n);

    vector<int> sz(n);
    vector<int> fa(n);
    vector<int> nodes;
    function<int(int)> get_centroid = [&](int u) -> int {
        nodes.resize(0);

        function<void(int, int)> dfs = [&](int u, int pre) {
            sz[u] = 1;
            fa[u] = pre;
            nodes.push_back(u);
            for (auto v : V[u]) {
                if (v == pre) continue;
                if (ans[v]) continue;
                dfs(v, u);
                sz[u] += sz[v];
            }
        };

        dfs(u, -1);

        int all = sz[u];

        int mi = 1e9;
        int centroid = nodes[0];
        for (auto node : nodes) {
            int mx = all - sz[node];
            for (auto v : V[node]) {
                if (v == fa[node]) continue;
                if (ans[v]) continue;
                mx = max(mx, sz[v]);
            }
            if (mx < mi) {
                mi = mx;
                centroid = node;
            }
        }
        return centroid;
    };

    function<void(int, int)> solve = [&](int u, int d) {
        int centroid = get_centroid(u);
        debug(u, d, centroid);
        ans[centroid] = 'A' + d;
        for (auto v : V[centroid]) {
            if (ans[v]) continue;
            solve(v, d + 1);
        }
    };
    solve(0, 0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}