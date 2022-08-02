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

vector<vector<int>> V;
vector<int> a, w;

vector<int> L, R;
int tot;
vector<int> id;
void dfs(int u) {
    L[u] = ++tot;
    id[tot] = u;
    for (auto v : V[u]) {
        dfs(v);
    }
    R[u] = tot;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    V.resize(n + 1);
    a.resize(n + 1);
    w.resize(n + 1);
    L.resize(n + 1);
    R.resize(n + 1);
    id.resize(n + 1);

    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }
    dfs(1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    vector<vector<int>> dp;
    const int inf = numeric_limits<int>::max() / 2;

    dp.resize(n + 2, vector<int>(m + 1, -inf));
    dp[n + 1][0] = 0;

    for (int i = n; i >= 1; i--) {
        int u = id[i];
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[R[u] + 1][j];
            if (j >= w[u]) {
                dp[i][j] = max(dp[i][j], dp[i + 1][j - w[u]] + a[u]);
            }
        }
    }

    for (int i = 0; i <= m; i++) {
        if (dp[1][i] < 0) {
            cout << 0 << endl;
        } else {
            cout << dp[1][i] << endl;
        }
    }
    return 0;
}