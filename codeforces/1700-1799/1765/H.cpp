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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    vector<vector<int>> V(n);
    vector<int> in(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        in[v]++;
    }
    debug(V);

    vector<int> dp(n, -1);
    function<int(int)> dfs = [&](int u) -> int {
        if (dp[u] != -1) return dp[u];

        dp[u] = p[u];
        for (auto v : V[u]) {
            int tmp = dfs(v);
            dp[u] = min(dp[u], tmp - 1);
        }
        return dp[u];
    };

    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            dfs(i);
        }
    }
    debug(dp);

    set<pair<int, int>> S;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            S.insert({dp[i], i});
        }
    }
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}