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

    int n, q;
    cin >> n >> q;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int m = min(100, n);

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    vector<int> sz(n + 1);
    const int inf = numeric_limits<int>::max() / 2;

    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;
        dp[u][0] = 0;
        dp[u][1] = a[u];
        for (auto v : V[u]) {
            dfs(v);

            static vector<int> tmp;

            int the_sz = min(sz[u] + sz[v], m);

            tmp.resize(the_sz + 1);
            for (int i = 0; i <= the_sz; i++) tmp[i] = -inf;
            tmp[0] = 0;
            for (int i = 1; i <= sz[u] && i <= m; i++) {
                for (int j = 0; j <= sz[v] && i + j <= m; j++) {
                    tmp[i + j] = max(tmp[i + j], dp[u][i] + dp[v][j]);
                }
            }
            dp[u] = tmp;
            sz[u] += sz[v];
        }
    };
    dfs(1);
    // debug(dp);

    while (q--) {
        int u, m;
        cin >> u >> m;
        cout << dp[u][m] << endl;
    }
}