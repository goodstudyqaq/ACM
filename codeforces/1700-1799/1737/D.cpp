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
    int n, m;
    cin >> n >> m;
    const ll inf = 1e9 + 1;
    vector g1 = vector(n + 1, vector(n + 1, inf));
    vector g2 = vector(n + 1, vector(n + 1, inf));
    for (int i = 1; i <= n; i++) g2[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g1[u][v] = g1[v][u] = min(g1[u][v], 1LL * w);
        g2[u][v] = g2[v][u] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g2[i][j] = min(g2[i][j], g2[i][k] + g2[k][j]);
            }
        }
    }

    ll ans = numeric_limits<ll>::max() / 2;

    // 选边
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        ll mi = inf;
        for (int j = 1; j <= n; j++) {
            if (g1[i][j] != inf) {
                cnt++;
                mi = min(mi, g1[i][j]);
                ans = min(ans, (g2[1][i] + g2[n][j] + 1) * g1[i][j]);

                for (int x = 1; x <= n; x++) {
                    ans = min(ans, (g2[i][x] + 1 + g2[1][x] + g2[n][x] + 1) * g1[i][j]);
                }
            }
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