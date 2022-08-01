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
typedef array<int, 3> a3;

void solve() {
    int n, m;
    cin >> n >> m;
    pii s, t;
    cin >> s.first >> s.second;
    cin >> t.first >> t.second;

    vector<pii> loc(m + 1);

    vector<a3> X, Y;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        loc[i] = {x, y};
        X.push_back({x, y, i});
        Y.push_back({y, x, i});
    }

    vector<vector<pii>> V(m + 1);
    for (auto& s : vector{X, Y}) {
        sort(s.begin(), s.end());
        int sz = s.size();
        for (int i = 1; i < sz; i++) {
            auto [x1, y1, u] = s[i];
            auto [x2, y2, v] = s[i - 1];
            int dist = min(abs(x1 - x2), abs(y1 - y2));
            V[u].push_back({v, dist});
            V[v].push_back({u, dist});
        }
    }

    const ll inf = numeric_limits<ll>::max() / 2;
    vector<ll> d(m + 1, inf);
    priority_queue<pll, vector<pll>, greater<pll>> Q;
    for (int i = 1; i <= m; i++) {
        int dist = min(abs(loc[i].first - s.first), abs(loc[i].second - s.second));
        Q.push({dist, i});
    }

    while (!Q.empty()) {
        auto [dist, u] = Q.top();
        Q.pop();
        if (d[u] <= dist) continue;
        d[u] = dist;
        for (auto [v, e] : V[u]) {
            Q.push({dist + e, v});
        }
    }

    ll ans = abs(s.first - t.first) + abs(s.second - t.second);
    for (int i = 1; i <= m; i++) {
        ans = min(ans, d[i] + abs(loc[i].first - t.first) + abs(loc[i].second - t.second));
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}