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
    int n;
    cin >> n;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }

    vector<ll> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }

    vector<int> dp(n + 1);
    vector<ll> val(n + 1);
    function<void(int)> dfs = [&](int u) {
        ll mx = 0;
        for (auto v : V[u]) {
            dfs(v);
            dp[u] += dp[v];
            mx += val[v];
        }
        if (mx < l[u]) {
            dp[u]++;
            val[u] = r[u];
        } else {
            val[u] = min(mx, r[u]);
        }
    };

    dfs(1);
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