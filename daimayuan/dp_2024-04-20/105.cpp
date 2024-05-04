#include <bits/stdc++.h>

#include <cstdlib>
#include <limits>

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
    vector<vector<int>> V(n + 1);
    vector<int> dep(n + 1);
    dep[1] = 1;
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
        dep[i] = dep[f] + 1;
    }

    typedef pair<int, int> pii;
    vector<vector<pii>> path(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        path[v].push_back({u, w});
    }

    const long long inf = numeric_limits<long long>::max() / 2;
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 2, inf));  // dp[u][i] u 子树到深度 i 的最小花费
    
    vector<long long> suf1(n + 2), suf2(n + 2);

    auto merge = [&](int u, int v, int d) {
        suf1[d + 1] = inf, suf2[d + 1] = inf;
        for (int i = d; i >= 1; i--) {
            suf1[i] = min(suf1[i + 1], dp[u][i]);
            suf2[i] = min(suf2[i + 1], dp[v][i]);
        }
        for (int i = 1; i <= d; i++) {
            dp[u][i] = min({dp[u][i] + suf2[i], suf1[i] + dp[v][i], inf});
        }
    };


    function<void(int)> dfs = [&](int u) {
        dp[u][dep[u] + 1] = 0;
        for (auto p : path[u]) {
            dp[u][dep[p.first]] = min(dp[u][dep[p.first]], 1LL * p.second);
        }

        for (auto v : V[u]) {
            dfs(v);
            merge(u, v, dep[v]);
        }

    };
    dfs(1);
    if (dp[1][1] >= inf) dp[1][1] = -1;
    cout << dp[1][1] << endl;
}