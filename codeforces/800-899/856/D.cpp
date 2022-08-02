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

vector<vector<int>> V;
vector<int> L, R;
int t;
vector<int> dep;
vector<vector<int>> dp;

void dfs(int u, int d) {
    L[u] = ++t;
    dep[u] = d;
    for (auto v : V[u]) {
        dfs(v, d + 1);
    }
    R[u] = t;
}

void rmp(int n) {
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            if ((1 << i) > dep[j]) continue;
            int k = dp[j][i - 1];
            dp[j][i] = dp[k][i - 1];
        }
    }
}

int query(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int j = 19; j >= 0 && dep[x] != dep[y]; j--) {
        if (dep[y] - (1 << j) < dep[x]) continue;
        y = dp[y][j];
    }
    if (x == y) return x;
    for (int j = 19; j >= 0; j--) {
        if (dep[x] - (1 << j) < 0 || dp[x][j] == dp[y][j]) continue;
        x = dp[x][j], y = dp[y][j];
    }
    return dp[x][0];
}

#define lowbit(x) x & -x
vector<int> sum;
const int maxn = 2e5 + 2;
void add(int x, int val) {
    while (x < maxn) {
        sum[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

typedef array<int, 3> a3;

vector<int> dp2, sum2;
vector<vector<a3>> E;
void dfs2(int u) {
    sum2[u] = 0;
    for (auto v : V[u]) {
        dfs2(v);
        sum2[u] += dp2[v];
    }
    dp2[u] = sum2[u];
    for (auto it : E[u]) {
        dp2[u] = max(dp2[u], query(L[it[0]]) + query(L[it[1]]) + sum2[u] + it[2]);
    }
    add(L[u], sum2[u] - dp2[u]);
    add(R[u] + 1, dp2[u] - sum2[u]);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    V.resize(n + 1);
    L.resize(n + 1);
    R.resize(n + 1);
    dep.resize(n + 1);
    dp.resize(n + 1, vector<int>(20));
    sum.resize(maxn);
    dp2.resize(n + 1);
    sum2.resize(n + 1);
    E.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        dp[i][0] = p;
        V[p].push_back(i);
    }

    dfs(1, 1);
    rmp(n);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        int lca = query(u, v);
        E[lca].push_back({u, v, c});
    }
    dfs2(1);
    cout << dp2[1] << endl;
    return 0;
}