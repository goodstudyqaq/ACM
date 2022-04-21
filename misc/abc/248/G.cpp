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
const int mod = 998244353;

const int MAXN = 1e5 + 10;
bool ok[MAXN], vis[MAXN];
int sz[MAXN];
int dp[MAXN];
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    const int maxn = 1e5;

    vector<vector<int>> G;
    G.resize(maxn + 1);
    for (int i = 1; i <= maxn; i++) {
        for (int j = i; j <= maxn; j += i) {
            G[j].emplace_back(i);
        }
    }

    int N;
    cin >> N;

    vector<vector<int>> G2;
    G2.resize(maxn + 1);
    for (int i = 1; i <= N; i++) {
        int A;
        cin >> A;
        for (auto it : G[A]) {
            G2[it].emplace_back(i);
        }
    }

    vector<vector<int>> V;
    V.resize(N + 1);
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        V[u].emplace_back(v);
        V[v].emplace_back(u);
    }

    function<void(int, int)> dfs = [&](int u, int pre) {
        sz[u] = 1;
        vis[u] = 1;
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (ok[v]) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
    };

    function<long long(int, int, int)> solve = [&](int u, int pre, int tot) -> long long {
        long long res = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (ok[v]) {
                res += solve(v, u, tot) + 1LL * sz[v] * (tot - sz[v]);
            }
        }
        return res;
    };

    for (int i = 1; i <= maxn; i++) {
        if (G2[i].size() == 0) continue;
        // debug(i);
        for (auto u : G2[i]) {
            ok[u] = 1;
            vis[u] = 0;
        }
        for (int j = 1; j <= N; j++) {
            if (ok[j] && vis[j] == 0) {
                dfs(j, -1);
                long long tmp = solve(j, -1, sz[j]) + 1LL * sz[j] * (sz[j] - 1) / 2 % mod;
                dp[i] = (dp[i] + tmp % mod) % mod;
            }
        }

        for (auto u : G2[i]) {
            ok[u] = 0;
        }
    }

    for (int i = maxn; i >= 1; i--) {
        for (int j = i * 2; j <= maxn; j += i) {
            (dp[i] -= dp[j]) %= mod;
        }
    }

    int ans = 0;
    for (int i = 1; i <= maxn; i++) {
        ans = (ans + 1LL * i * dp[i] % mod) % mod;
    }
    ans = (ans + mod) % mod;
    cout << ans << endl;
}