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

    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }

    vector<long long> dp(n + 1);
    function<void(int)> dfs = [&](int u) {
        dp[u] = 1;
        for (auto v : V[u]) {
            dfs(v);
            dp[u] = dp[u] * ((dp[v] + 1) % m) % m;
        }
    };
    dfs(1);

    vector<long long> dp2(n + 1);
    vector<long long> ans(n + 1);
    vector<long long> pre(n + 1), suf(n + 1);
    debug(dp);

    function<void(int)> dfs2 = [&](int u) {
        pre[0] = 1;
        for (int i = 0; i < V[u].size(); i++) {
            pre[i + 1] = pre[i] * ((dp[V[u][i]] + 1) % m) % m;
        }

        suf[V[u].size()] = 1;
        for (int i = V[u].size() - 1; i >= 0; i--) {
            suf[i] = (suf[i + 1] * (dp[V[u][i]] + 1) % m) % m;
        }

        for (int i = 0; i < V[u].size(); i++) {
            int v = V[u][i];
            long long tmp = pre[i] * suf[i + 1] % m;
            if (u != 1) {
                tmp = (tmp * (dp2[u] + 1) % m) % m;
            }
            dp2[v] = tmp % m;
            ans[v] = dp[v] * (dp2[v] + 1) % m;
        }
        for (int i = 0; i < V[u].size(); i++) {
            dfs2(V[u][i]);
        }
    };
    ans[1] = dp[1];
    dfs2(1);
    debug(dp2);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}