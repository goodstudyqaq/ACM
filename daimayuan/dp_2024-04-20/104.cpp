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

    int n, m;
    cin >> n >> m;
    vector<int> f(n + 1);
    vector<vector<int>> V(n + 1);
    vector<int> dep(n + 1);
    dep[1] = 0;
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        V[f[i]].push_back(i);
        dep[i] = dep[f[i]] + 1;
    }

    typedef array<int, 3> a3;
    vector<vector<a3>> path(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, a;
        cin >> u >> v >> a;

        int x = u, y = v;
        while (x != y) {
            if (dep[x] > dep[y]) {
                x = f[x];
            } else {
                y = f[y];
            }
        }
        path[x].push_back({u, v, a});
    }

    vector<long long> dp(n + 1), sumdp(n + 1);

    function<void(int)> dfs = [&](int u) {
        for (auto v : V[u]) {
            dfs(v);
            sumdp[u] += dp[v];
        }
        dp[u] = sumdp[u];

        for (auto p : path[u]) {
            int x = p[0], y = p[1], w = p[2];

            long long res = 0;

            while (x != u) {
                res += sumdp[x] - dp[x];
                x = f[x];
            }

            while (y != u) {
                res += sumdp[y] - dp[y];
                y = f[y];
            }

            res += sumdp[u] + w;
            dp[u] = max(dp[u], res);
        }
    };
    dfs(1);
    cout << dp[1] << endl;
}