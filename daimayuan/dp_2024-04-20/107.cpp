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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), t(n + 1);
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

    function<void(int, int)> dfs = [&](int u, int pre) {
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }

        // 计算 dp[u][0]
        // 第一种方法，直接选一个点走到底，后面再回来走其他的点，相当于有一个点的权值会被考虑，其他的权值不会被计算
        int mx = 0;
        int mx3 = 0;
        long long tmp = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            tmp += dp[v][0];
            mx = max(mx, a[v]);
            if (t[v] == 3) {
                if (mx3 == 0 || a[mx3] < a[v]) {
                    mx3 = v;
                }
            }
        }
        dp[u][0] = tmp + mx;

        // 第二种方法，挑一个点走，然后再回头，走到一个 t 等于 3 的点，相当于考虑 2 个点的权值和，但是第一个点的状态变成 dp[v][1]
        if (mx3) {
            for (auto v : V[u]) {
                if (v == pre) continue;
                if (mx3 != v) {
                    long long tmp2 = tmp - dp[v][0] + dp[v][1] + a[v] + a[mx3];
                    dp[u][0] = max(dp[u][0], tmp2);

                    if (t[v] == 3) {
                        tmp2 = tmp - dp[mx3][0] + dp[mx3][1] + a[mx3] + a[v];
                        dp[u][0] = max(dp[u][0], tmp2);
                    }
                }
            }
        }
        // 计算 dp[u][1]
        // 孩子的蝴蝶全部飞走
        dp[u][1] = tmp;
    };

    dfs(1, 0);
    cout << dp[1][0] + a[1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}