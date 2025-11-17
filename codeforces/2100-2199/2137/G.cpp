#include <bits/stdc++.h>

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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> g1(n), g2(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g1[u].push_back(v);
        g2[v].push_back(u);
    }

    vector<vector<int>> dp(n, vector<int>(2));
    // dp[u][0] u 对 C 是必胜 1 还是必败 0
    // dp[u][1] u 对 R 是必胜 1 还是必败 0
    for (int i = 0; i < n; i++) {
        dp[i][0] = 1;
        dp[i][1] = 0;
    }

    vector<vector<set<int>>> status(n, vector<set<int>>(2));

    for (int i = 0; i < n; i++) {
        for (auto v : g1[i]) {
            if (dp[v][0] == 0) {
                status[i][1].insert(v);
            }
            if (dp[v][1] == 0) {
                status[i][0].insert(v);
            }
        }
    }

    vector<bool> red(n);

    while (q--) {
        int x, u;
        cin >> x >> u;
        u--;
        if (x == 1) {
            red[u] = 1;
            if (dp[u][0] == 0 && dp[u][1] == 1) continue;
            queue<int> Q;
            dp[u][0] = 0;
            dp[u][1] = 1;
            Q.push(u);
            while (!Q.empty()) {
                auto u = Q.front();
                Q.pop();
                for (auto v : g2[u]) {
                    if (red[v]) {
                        continue;
                    }
                    if (dp[v][0] == 0 && dp[v][1] == 1) {
                        continue;
                    }

                    if (dp[u][0] == 1) {
                        status[v][1].erase(u);
                    } else {
                        status[v][1].insert(u);
                    }
                    if (dp[u][1] == 1) {
                        status[v][0].erase(u);
                    } else {
                        status[v][0].insert(u);
                    }

                    int new_0 = 0, new_1 = 0;

                    if (status[v][1].size()) {
                        new_1 = 1;
                    }

                    if (status[v][0].size()) {
                        new_0 = 1;
                    }

                    if (new_0 != dp[v][0] || new_1 != dp[v][1]) {
                        dp[v][0] = new_0;
                        dp[v][1] = new_1;
                        Q.push(v);
                    }
                }
            }
            debug(dp, status[0]);
        } else {
            if (dp[u][0]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
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