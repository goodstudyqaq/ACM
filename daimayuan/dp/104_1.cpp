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

    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        V[f[i]].push_back(i);
        dep[i] = dep[f[i]] + 1;
    }
    vector<vector<array<int, 3>>> path(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        int x = u, y = v;
        while (x != y) {
            if (dep[x] > dep[y]) {
                x = f[x];
            } else {
                y = f[y];
            }
        }
        path[x].push_back({u, v, c});
    }

    vector<ll> dp(n + 1);
    vector<ll> sdp(n + 1);
    function<void(int)> dfs = [&](int u) -> void {
        for (auto v : V[u]) {
            dfs(v);
            sdp[u] += dp[v];
        }

        dp[u] = sdp[u];

        for (auto it : path[u]) {
            int x = it[0], y = it[1], c = it[2];

            ll tmp = sdp[u];
            while (x != u) {
                tmp += sdp[x] - dp[x];
                x = f[x];
            }

            while (y != u) {
                tmp += sdp[y] - dp[y];
                y = f[y];
            }

            tmp += c;
            dp[u] = max(dp[u], tmp);
        }
    };
    dfs(1);
    cout << dp[1] << endl;
    return 0;
}