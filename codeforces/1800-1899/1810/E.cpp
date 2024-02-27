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
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<bool> vis_zero(n + 1);
    auto check = [&](int node) -> bool {
        // a[u] = 0
        set<int> vis;
        set<pair<int, int>> can_reach;
        can_reach.insert({a[node], node});
        vis_zero[node] = 1;
        // debug(node);
        while (true) {
            if (can_reach.size() == 0) break;
            auto it = can_reach.begin();
            // debug(*it);
            int score = vis.size();
            if (score >= it->first) {
                int u = it->second;
                can_reach.erase(it);
                vis.insert(u);
                if (a[u] == 0) {
                    vis_zero[u] = 1;
                }
                for (auto v : V[u]) {
                    if (vis.count(v) == 0) {
                        can_reach.insert({a[v], v});
                    }
                }
            } else {
                break;
            }
        }
        // debug(vis, vis.size() == n);
        return vis.size() == n;
    };

    for (int i = 1; i <= n; i++) {
        if (a[i] == 0 && vis_zero[i] == 0) {
            if (check(i)) {
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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