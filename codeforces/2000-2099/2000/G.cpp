#include <bits/stdc++.h>

#include <functional>
#include <limits>
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
typedef pair<int, pll> pill;

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
    vector<long long> t(3);
    for (int i = 0; i < 3; i++) {
        cin >> t[i];
    }

    vector<vector<pill>> V(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        V[u].push_back({v, {l1, l2}});
        V[v].push_back({u, {l1, l2}});
    }

    int l = 0, r = t[0];
    int ans = -1;

    vector<long long> dist(n + 1);
    const long long inf = numeric_limits<long long>::max() / 2;
    auto check = [&](int m) {
        for (int i = 1; i <= n; i++) dist[i] = inf;
        dist[1] = m;
        priority_queue<pll, vector<pll>, greater<>> Q;
        Q.push({dist[1], 1});

        while (!Q.empty()) {
            auto [d, u] = Q.top();
            // debug(d, u);
            Q.pop();
            if (d > dist[u]) continue;

            for (auto &e : V[u]) {
                int v = e.first, l1 = e.second.first, l2 = e.second.second;
                // debug(u, v, l1, l2);

                // 坐车
                long long time = d + l1;
                // [t1, t2] [d, time] 是否有交集
                if (max(t[1], d) < min(t[2], time)) {
                    // 不能坐车
                    // 走路
                    long long time2 = d + l2;
                    if (dist[v] > time2) {
                        dist[v] = time2;
                        Q.push({dist[v], v});
                    }

                    // 不动
                    long long time3 = t[2] + l1;
                    if (dist[v] > time3) {
                        dist[v] = time3;
                        Q.push({dist[v], v});
                    }

                } else {
                    if (dist[v] > time) {
                        dist[v] = time;
                        Q.push({dist[v], v});
                    }
                }
            }
        }

        return dist[n] <= t[0];
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
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
    return 0;
}