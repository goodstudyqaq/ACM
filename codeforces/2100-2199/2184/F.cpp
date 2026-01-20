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
typedef array<int, 2> a2;

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
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<vector<bool>> dp(n, vector<bool>(3));
    function<void(int, int)> dfs = [&](int u, int pre) {
        int sz = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            sz++;
            dfs(v, u);
        }

        if (sz == 0) {
            dp[u] = {0, 1, 0};
            return;
        }

        vector<bool> now(3, false);
        now[0] = true;

        for (auto v : V[u]) {
            if (v == pre) continue;
            vector<bool> go(3, false);
            for (int i = 0; i < 3; i++) {
                if (now[i]) {
                    for (int j = 0; j < 3; j++) {
                        if (dp[v][j]) {
                            go[(i + j) % 3] = true;
                        }
                    }
                }
            }
            now = go;
        }
        dp[u] = now;
        dp[u][1] = 1;
        debug(u, dp[u]);
    };

    dfs(0, -1);
    if (dp[0][0]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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