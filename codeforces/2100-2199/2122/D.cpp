#include <bits/stdc++.h>

#include <deque>
#include <queue>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
const int maxn = 5000;
int dp[maxn * 2 + 1][maxn];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    const int inf = 1e9;
    for (int i = 0; i <= n * 2; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = inf;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i <= n * 2; i++) {
        if (dp[i][n - 1] != inf) {
            cout << i << ' ' << dp[i][n - 1] << '\n';
            return;
        }

        for (int j = 0; j < n; j++) {
            if (dp[i][j] != inf) {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
                int sz = V[j].size();
                int v = V[j][i % sz];
                dp[i + 1][v] = min(dp[i + 1][v], dp[i][j]);
            }
        }
    }

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