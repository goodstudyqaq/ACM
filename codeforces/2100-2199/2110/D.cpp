#include <bits/stdc++.h>

#include <algorithm>
#include <functional>
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<long long> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<vector<pair<int, long long>>> V(n);
    vector<vector<pair<int, long long>>> V2(n);
    for (int i = 0; i < m; i++) {
        int s, t, w;
        cin >> s >> t >> w;
        s--, t--;
        V[s].push_back({t, w});
        V2[t].push_back({s, w});
    }

    const long long inf = 1e18;
    vector<long long> mi(n, inf);
    priority_queue<pll, vector<pll>, greater<>> Q;
    mi[n - 1] = 0;
    Q.push({0, n - 1});
    vector<int> vis(n);
    while (!Q.empty()) {
        auto [val, u] = Q.top();
        Q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : V2[u]) {
            long long need = max(w, val);
            if (mi[v] > need) {
                mi[v] = need;
                Q.push({mi[v], v});
            }
        }
    }

    int l = 0, r = 1e9;
    int ans = -1;

    auto check = [&](long long mx) {
        vector<int> dp(n, -1);
        dp[0] = min(b[0], mx);
        for (int u = 0; u < n; ++u) {
            for (auto [v, w]: V[u]) {
                if (dp[u] < w) continue;
                dp[v] = max(dp[v], (int)min(dp[u] + b[v], mx));
            }
        }
        return dp[n - 1] != -1;
        // vector<int> vis(n);
        // priority_queue<pll> Q;
        // Q.push({min(b[0], mx), 0});
        // vector<int> d(n, -1);
        // d[0] = min(b[0], mx);
        // while (!Q.empty()) {
        //     auto [val, u] = Q.top();
        //     Q.pop();
        //     if (vis[u]) continue;
        //     vis[u] = 1;
        //     for (auto [v, w] : V[u]) {
        //         if (d[u] >= w) {
        //             long long tmp = min(mx, val + b[v]);
        //             if (d[v] < tmp) {
        //                 d[v] = tmp;
        //                 Q.push({d[v], v});
        //             }
        //         }
        //     }
        // }
        // return d[n - 1] != -1;
    };
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << '\n';
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