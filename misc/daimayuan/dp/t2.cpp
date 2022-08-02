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

const int maxm = 100;
vector<vector<int>> V;
vector<vector<int>> dp;
vector<int> a;
vector<int> sz;
const int inf = numeric_limits<int>::max() / 2;

void dfs(int u) {
    sz[u] = 0;
    dp[u][0] = 0;
    for (auto v : V[u]) {
        dfs(v);
        int v_sz = sz[v];
        int u_sz = sz[u];
        static vector<int> tmp;
        int it_sz = min(maxm, u_sz + v_sz);
        tmp.resize(it_sz + 1);
        for (int i = 0; i <= it_sz; i++) {
            tmp[i] = -inf;
        }
        for (int i = 0; i <= min(u_sz, maxm); i++) {
            for (int j = 0; j <= min(v_sz, maxm) && i + j <= maxm; j++) {
                tmp[i + j] = max(tmp[i + j], dp[u][i] + dp[v][j]);
            }
        }
        for (int i = 0; i <= min(it_sz, maxm); i++) {
            dp[u][i] = tmp[i];
        }
        sz[u] += sz[v];
    }

    for (int i = min(sz[u], maxm - 1); i >= 0; i--) {
        dp[u][i + 1] = dp[u][i] + a[u];
    }
    sz[u]++;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    V.resize(n + 1);
    dp.resize(n + 1, vector<int>(maxm + 1, -inf));
    a.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dfs(1);

    while (q--) {
        int u, m;
        cin >> u >> m;
        cout << dp[u][m] << endl;
    }
    return 0;
}