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
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(2, 0)));

    // dp[u][0/1][0/1] u 子树下，是否已经有连续父子，且子是叶子，u 是否被选的最大选择数
    function<void(int, int)> dfs = [&](int u, int pre) {
        int mx = 0;
        int mx2 = 0;
        dp[u][0][1] = dp[u][1][1] = 1;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            int mx1 = max(dp[v][0][0], dp[v][0][1]);
            dp[u][0][0] += mx1;
            dp[u][0][1] += dp[v][0][0];
            int tmp2 = max(dp[v][1][0], dp[v][1][1]);
            mx = max(mx, tmp2 - mx1);

            mx2 = max(mx2, dp[v][1][0] - dp[v][0][0]);
            if (V[v].size() == 1) {
                mx2 = max(mx2, 1);
            }
        }

        dp[u][1][0] = mx + dp[u][0][0];
        dp[u][1][1] = dp[u][0][1] + mx2;
    };
    dfs(1, -1);

    int ans = max({dp[1][0][0], dp[1][0][1], dp[1][1][0], dp[1][1][1]});
    if (V[1].size() == 1) {
        ans = max({ans, dp[1][0][0] + 1});
    }
    cout << ans << endl;
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