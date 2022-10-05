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
    vector<int> f(n + 1), dep(n + 1);
    vector<vector<int>> V(n + 1);
    dep[1] = 1;
    for (int i = 2; i <= n; i++) {
        cin >> f[i];
        V[f[i]].push_back(i);
        dep[i] = dep[f[i]] + 1;
    }
    vector<vector<pii>> path(n + 1);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        path[v].push_back({u, c});
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    vector<ll> suf1(n + 2, inf), suf2(n + 2, inf);
    auto merge = [&](int u, int v, int d) {
        suf1[d + 1] = suf2[d + 1] = inf;
        for (int i = d; i >= 1; i--) {
            suf1[i] = min(suf1[i + 1], dp[u][i]);
            suf2[i] = min(suf2[i + 1], dp[v][i]);
        }

        for (int i = 1; i <= d; i++) {
            dp[u][i] = min({dp[u][i] + suf2[i], dp[v][i] + suf1[i], inf});
        }
    };

    function<void(int)> dfs = [&](int u) {
        for (int i = 1; i <= dep[u]; i++) {
            dp[u][i] = inf;
        }
        for (auto it : path[u]) {
            int v = it.first, c = it.second;
            dp[u][dep[v]] = min(dp[u][dep[v]], 1LL * c);
        }

        for (auto v : V[u]) {
            dfs(v);
            merge(u, v, dep[v]);
        }
    };
    dfs(1);
    if (dp[1][1] >= inf) {
        cout << -1 << endl;
    } else {
        cout << dp[1][1] << endl;
    }
    return 0;
}