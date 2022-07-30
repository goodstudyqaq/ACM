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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> V(n + 1);
    vector<pii> edges;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
        edges.push_back({u, v});
    }

    if (m % 2 == 0) {
        cout << 0 << endl;
        return;
    }
    int ans = 1e9;

    for (int i = 1; i <= n; i++) {
        int sz = V[i].size();
        if (sz % 2) {
            ans = min(ans, a[i]);
        }
    }

    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        int sz_u = V[u].size();
        int sz_v = V[v].size();
        if ((sz_u + sz_v - 1) % 2) {
            ans = min(ans, a[u] + a[v]);
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