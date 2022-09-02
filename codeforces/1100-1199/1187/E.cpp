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
    int n;
    cin >> n;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> sz(n + 1);
    ll sum = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        sz[u] = 1;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            sz[u] += sz[v];
        }
        sum += sz[u];
    };
    dfs(1, 0);
    ll ans = sum;
    debug(sz);

    function<void(int, int)> dfs2 = [&](int u, int pre) {
        ans = max(ans, sum);
        debug(u, sz);
        for (auto v : V[u]) {
            if (v == pre) continue;
            int sz_u = sz[u], sz_v = sz[v];
            sum -= sz_u + sz_v;
            sz[u] = sz_u - sz_v;
            sz[v] = n;
            sum += sz[u] + sz[v];
            dfs2(v, u);
            sum -= sz[u] + sz[v];
            sz[u] = sz_u;
            sz[v] = sz_v;
            sum += sz[u] + sz[v];
        }
    };
    dfs2(1, 0);
    cout << ans << endl;
    return 0;
}