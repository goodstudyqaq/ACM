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

vector<vector<int>> V;

vector<int> dp;
vector<int> sz;
// dp[u] 表示 u 感染了能存活的节点的最大个数
void dfs(int u, int pre) {
    sz[u] = 1;

    int cnt = 0;
    vector<int> V2;
    for (auto v : V[u]) {
        if (v == pre) continue;
        V2.push_back(v);
        cnt++;
        dfs(v, u);
        sz[u] += sz[v];
    }

    if (cnt == 0) {
        dp[u] = 0;
    } else if (cnt == 1) {
        dp[u] = sz[u] - 2;
    } else {
        int v1 = V2[0], v2 = V2[1];
        int tmp1 = sz[v1] - 1 + dp[v2];
        int tmp2 = sz[v2] - 1 + dp[v1];
        dp[u] = max(tmp1, tmp2);
    }
    // debug(u, cnt, dp[u], sz[u]);
}

void solve() {
    int n;
    cin >> n;
    V.clear();
    dp.clear();
    sz.clear();
    V.resize(n + 1);
    dp.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    dfs(1, 0);
    cout << dp[1] << endl;
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