#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<vector<pii>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        V[u].push_back({v, x});
        V[v].push_back({u, x});
    }

    vector<int> f(n + n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        g[i].push_back(i + n);
    }

    for (int i = 1; i <= n; i++) {
        f[i + n] = n;
    }
    vector<int> sz(n + 1);

    function<void(int, int)> dfs1 = [&](int u, int pre) {
        sz[u] = 1;
        for (auto [v, val] : V[u]) {
            if (v == pre) continue;
            g[val].push_back(v);
            dfs1(v, u);
            sz[u] += sz[v];
            g[val].pop_back();
            f[g[val].back()] -= sz[v];
        }
        f[u] += sz[u];
    };

    dfs1(1, 0);
    debug(f);

    ll ans = 0;
    function<void(int, int)> dfs2 = [&](int u, int pre) {
        for (auto [v, val] : V[u]) {
            if (v == pre) continue;
            ans += 1LL * f[v] * f[g[val].back()];
            g[val].push_back(v);
            dfs2(v, u);
            g[val].pop_back();
        }
    };
    dfs2(1, 0);
    cout << ans << endl;
}