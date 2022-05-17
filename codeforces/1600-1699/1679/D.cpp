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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<int> a(n + 1);
    vector<vector<int>> V(n + 1);
    int mi = 1e9, mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mi = min(mi, a[i]);
        mx = max(mx, a[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
    }
    vector<int> vis(n + 1);
    vector<ll> dp(n + 1);
    ll inf = numeric_limits<ll>::max() / 2;

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        dp[u] = 1;
        for (auto v : V[u]) {
            if (vis[v] == 0) {
                dfs(v);
                dp[u] = max(dp[u], dp[v] + 1);
                dp[u] = min(inf, dp[u]);
            } else if (vis[v] == 1) {
                // 有环
                dp[u] = inf;
            } else {
                dp[u] = max(dp[u], dp[v] + 1);
                dp[u] = min(inf, dp[u]);
            }
        }
        vis[u] = 2;
    };

    auto check = [&](int val) {
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
            dp[i] = 0;
            if (a[i] > val) {
                vis[i] = 2;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (vis[i] == 0) {
                dfs(i);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (dp[i] >= k) {
                return true;
            }
        }
        return false;
    };

    int L = mi, R = mx;
    int ans = -1;
    while (L <= R) {
        int mid = L + R >> 1;
        if (check(mid)) {
            ans = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}