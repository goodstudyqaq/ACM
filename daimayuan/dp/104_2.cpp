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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    vector<int> dep(n + 1);
    vector<int> f(n + 1);

    vector<array<int, 3>> path(m + 1);
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        V[f[i]].push_back(i);
        dep[i] = dep[f[i]] + 1;
    }

    vector<vector<pii>> V2(n + 1);
    vector<vector<array<int, 3>>> V3(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        path[i] = {u, v, c};
        int x = u, y = v;
        vector<int> tmp1, tmp2;
        tmp1.push_back(x);
        tmp2.push_back(y);
        while (x != y) {
            if (dep[x] > dep[y]) {
                x = f[x];
                tmp1.push_back(x);
            } else {
                y = f[y];
                tmp2.push_back(y);
            }
        }
        int sz = tmp1.size();
        for (int j = 0; j < sz - 1; j++) {
            V2[tmp1[j]].push_back({i, (j == 0 ? -1 : tmp1[j - 1])});
        }
        sz = tmp2.size();
        for (int j = 0; j < sz - 1; j++) {
            V2[tmp2[j]].push_back({i, (j == 0 ? -1 : tmp2[j - 1])});
        }
        debug(u, v, x);

        V3[x].push_back({i, tmp1.size() >= 2 ? tmp1[tmp1.size() - 2] : 0, tmp2.size() >= 2 ? tmp2[tmp2.size() - 2] : 0});
    }
    debug(V2);
    debug(V3);

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0LL));
    vector<ll> g(n + 1, 0LL);

    function<void(int)> dfs = [&](int u) {
        ll sum_g = 0;
        for (auto v : V[u]) {
            dfs(v);
            sum_g += g[v];
        }
        dp[u][0] = sum_g;

        for (auto it : V2[u]) {
            int path_idx = it.first;
            int last_node = it.second;
            if (last_node == -1) {
                // 在端点
                dp[u][path_idx] = sum_g + path[path_idx][2];
            } else {
                dp[u][path_idx] = sum_g - g[last_node] + dp[last_node][path_idx];
            }
            debug(u, path_idx, dp[u][path_idx]);
        }

        g[u] = sum_g;
        for (auto it : V3[u]) {
            int path_idx = it[0];
            int p1 = it[1], p2 = it[2];
            if (p1 == 0 || p2 == 0) {
                // 有一个是自己
                int other = max(p1, p2);
                dp[u][path_idx] = sum_g - g[other] + dp[other][path_idx];
            } else {
                dp[u][path_idx] = sum_g - g[p1] - g[p2] + dp[p1][path_idx] + dp[p2][path_idx] - path[path_idx][2];
            }
            g[u] = max(g[u], dp[u][path_idx]);
            debug(u, path_idx, dp[u][path_idx]);
        }
        debug(g[u]);
    };
    dfs(1);
    cout << g[1] << endl;
    return 0;
}