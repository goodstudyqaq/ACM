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
    int n, mod;
    cin >> n >> mod;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }

    vector<ll> dp(n + 1);
    function<void(int)> dfs1 = [&](int u) {
        dp[u] = 1;
        for (auto v : V[u]) {
            dfs1(v);
            dp[u] = dp[u] * (dp[v] + 1) % mod;
        }
    };

    vector<ll> dp2(n + 1);  // 除了 i，和 f[i] 为连通块的方案数
    vector<ll> pre(n + 1), suf(n + 1);
    vector<ll> ans(n + 1);
    function<void(int)> dfs2 = [&](int u) {
        int sz = V[u].size();
        for (int i = 0; i < sz; i++) {
            int v = V[u][i];
            pre[i] = (dp[v] + 1) % mod;
            if (i) (pre[i] *= pre[i - 1]) %= mod;
        }
        for (int i = sz - 1; i >= 0; i--) {
            int v = V[u][i];
            suf[i] = (dp[v] + 1) % mod;
            if (i != sz - 1) (suf[i] *= suf[i + 1]) %= mod;
        }
        for (int i = 0; i < sz; i++) {
            ll left = (i == 0) ? 1 : pre[i - 1];
            ll right = (i == sz - 1) ? 1 : suf[i + 1];
            ll tmp = left * right % mod;
            if (u != 1) {
                (tmp *= (dp2[u] + 1)) %= mod;
            }
            int v = V[u][i];
            dp2[v] = tmp;
        }

        for (auto it : V[u]) {
            ans[it] = (dp2[it] + 1) * dp[it] % mod;
            dfs2(it);
        }
    };

    dfs1(1);
    debug(dp);
    dfs2(1);
    debug(dp2);
    ans[1] = dp[1];
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}