#include <bits/stdc++.h>

#include <limits>

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
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }

    vector<long long> hp(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> hp[i];
    }

    const long long inf = numeric_limits<long long>::max() / 2;
    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(2, vector<long long>(n + 1, inf)));
    vector<int> sz(n + 1);
    vector<long long> tmp(n + 1);

    function<void(int)> dfs = [&](int u) {
        sz[u] = 1;

        long long tmpval = 0;
        for (auto v : V[u]) {
            tmpval += hp[v];
        }
        dp[u][1][1] = 0;
        dp[u][0][0] = tmpval + hp[u];

        for (auto v : V[u]) {
            dfs(v);

            for (int i = 0; i <= sz[u] + sz[v]; i++) tmp[i] = inf;

            for (int i = 0; i <= sz[u]; i++) {
                for (int j = 0; j <= sz[v]; j++) {
                    tmp[i + j] = min({tmp[i + j], dp[u][0][i] + dp[v][1][j] - hp[v], dp[u][0][i] + dp[v][0][j]});
                }
            }
            dp[u][0] = tmp;
            for (int i = 0; i <= sz[u] + sz[v]; i++) tmp[i] = inf;

            for (int i = 0; i <= sz[u]; i++) {
                for (int j = 0; j <= sz[v]; j++) {
                    tmp[i + j] = min({tmp[i + j], dp[u][1][i] + dp[v][1][j], dp[u][1][i] + dp[v][0][j]});
                }
            }
            dp[u][1] = tmp;
            sz[u] += sz[v];
        }
    };

    dfs(1);
    for (int i = 0; i <= n; i++) {
        cout << min(dp[1][0][i], dp[1][1][i]) << ' ';
    }
    cout << endl;
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