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

struct Ladder {
    int a, b, c, d, h;
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> X(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> X[i];
    }

    vector<Ladder> ladders(k);
    vector<vector<int>> V(n + 1);
    vector<vector<int>> p(n + 1);
    p[1].push_back(1);
    p[n].push_back(m);
    for (int i = 0; i < k; i++) {
        int a, b, c, d, h;
        // (a, b) -> (c, d)
        cin >> a >> b >> c >> d >> h;
        ladders[i] = (Ladder){a, b, c, d, h};
        p[a].push_back(b);
        p[c].push_back(d);
        V[a].push_back(i);
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    debug(inf);
    vector<vector<ll>> dp(n + 1);
    vector<vector<bool>> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        sort(p[i].begin(), p[i].end());
        p[i].resize(unique(p[i].begin(), p[i].end()) - p[i].begin());
        int sz = p[i].size();
        dp[i].resize(sz, inf);
        vis[i].resize(sz, 0);
    }
    dp[1][0] = 0;
    vis[1][0] = 1;

    for (int i = 1; i <= n; i++) {
        int sz = dp[i].size();
        for (int j = 1; j < sz; j++) {
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1LL * (p[i][j] - p[i][j - 1]) * X[i]);
            if (vis[i][j - 1]) vis[i][j] = 1;
        }

        for (int j = sz - 2; j >= 0; j--) {
            dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1LL * (p[i][j + 1] - p[i][j]) * X[i]);
            if (vis[i][j + 1]) vis[i][j] = 1;
        }

        for (auto idx : V[i]) {
            auto it = ladders[idx];
            int idx1 = lower_bound(p[i].begin(), p[i].end(), it.b) - p[i].begin();
            int c = it.c;
            int idx2 = lower_bound(p[c].begin(), p[c].end(), it.d) - p[c].begin();
            dp[c][idx2] = min(dp[c][idx2], dp[i][idx1] - it.h);
            if (vis[i][idx1]) vis[c][idx2] = 1;
        }
        debug(i, vis[i], p[i], dp[i]);
    }

    ll res = dp[n].back();
    if (vis[n].back() == 0) {
        cout << "NO ESCAPE" << endl;
    } else {
        cout << res << endl;
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
}