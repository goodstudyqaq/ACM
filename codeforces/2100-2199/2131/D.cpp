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
    vector<int> one(n);
    for (int i = 0; i < n; i++) {
        for (auto v : V[i]) {
            if (V[v].size() == 1) {
                one[i]++;
            }
        }
    }
    vector<int> dp(n);
    function<void(int, int)> dfs = [&](int u, int pre) {
        dp[u] = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            dp[u] += max(1, dp[v]);
        }
    };

    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (one[i] > one[mx]) {
            mx = i;
        }
    }
    vector<int> V2{mx};

    int mi = 1e9;
    for (int i : V2) {
        dfs(i, -1);
        int ans = 0;
        for (auto v : V[i]) {
            if (V[v].size() == 1) {
                continue;
            }
            ans += dp[v];
        }
        mi = min(mi, ans);
    }

    cout << mi << '\n';
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