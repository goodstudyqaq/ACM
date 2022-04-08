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

const int mod = 1e9 + 7;
int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

int inv(int val) {
    return quick(val, mod - 2);
}

typedef pair<int, int> pii;
vector<vector<pii>> V;

vector<pii> dp;
void dfs(int u, int pre) {
    int num = 0;
    for (auto it : V[u]) {
        if (it.first == pre) continue;
        num++;
        dfs(it.first, u);
    }
    if (num == 0) return;
    int inv_num = inv(V[u].size());
    int sum1 = 0, sum2 = 0;
    for (auto it : V[u]) {
        (sum1 += dp[it.first].first) %= mod;
        (sum2 += dp[it.first].second) %= mod;
        (sum2 += it.second) %= mod;
    }
    sum1 = 1LL * sum1 * inv_num % mod;
    sum2 = 1LL * sum2 * inv_num % mod;
    sum1 = (((1 - sum1) % mod) + mod) % mod;

    int sum1_inv = inv(sum1);
    int tmp1 = 1LL * inv_num * sum1_inv % mod;
    int tmp2 = 1LL * sum2 * sum1_inv % mod;
    dp[u] = {tmp1, tmp2};
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    V.resize(n);
    dp.resize(n);
    for (int i = 1; i < n; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        V[u].push_back({v, c});
        V[v].push_back({u, c});
    }
    dfs(0, -1);
    debug(dp);
    int res = (dp[0].second + mod) % mod;
    cout << res << endl;
    return 0;
}