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
const int mod = 1e9 + 7;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    if (k == 2) {
        cout << n * (n - 1) / 2 << endl;
        return;
    }
    int belong;
    vector<vector<int>> num(n + 1, vector<int>(n + 1, 0));
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        num[belong][d]++;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (V[i].size() < k) continue;
        for (auto it : V[i]) {
            // 清空 num[it]
            for (int j = 1; j <= n; j++) num[it][j] = 0;
        }

        for (auto it : V[i]) {
            belong = it;
            dfs(it, i, 1);
        }
        // dp[i][j] =  前 i 个

        for (int d = 1; d <= n - 1; d++) {
            vector<int> tmp;
            for (auto it : V[i]) {
                if (num[it][d] > 0) {
                    tmp.push_back(it);
                }
            }
            if (tmp.size() < k) break;
            int sz = tmp.size();
            vector<vector<int>> dp(sz + 1, vector<int>(k + 1, 0));
            dp[0][0] = 1;
            for (int j = 0; j < sz; j++) {
                for (int p = 0; p <= min(j, k); p++) {
                    if (dp[j][p] == 0) continue;
                    dp[j + 1][p] += dp[j][p];
                    if (p + 1 <= k) {
                        (dp[j + 1][p + 1] += 1LL * dp[j][p] * num[tmp[j]][d] % mod) %= mod;
                    }
                }
            }
            (ans += dp[sz][k]) %= mod;
        }
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
}