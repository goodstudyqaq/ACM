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
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> p(k);
    for (int i = 0; i < k; i++) {
        cin >> p[i];
        p[i]--;
    }

    vector<vector<a2>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back({v, i});
        V[v].push_back({u, i});
    }

    queue<a2> Q;
    vector<int> vis(n);
    for (auto it : p) {
        if (vis[it] == 1) continue;
        Q.push({it, -1});
        vis[it] = 1;
    }

    set<int> S;
    while (!Q.empty()) {
        auto [u, pre] = Q.front();
        debug(u);
        Q.pop();
        for (auto it : V[u]) {
            auto [v, idx] = it;
            if (v == pre) continue;
            if (vis[v]) {
                S.insert(idx);
            } else {
                vis[v] = 1;
                Q.push({v, u});
            }
        }
    }

    cout << S.size() << '\n';
    for (auto it : S) {
        cout << it + 1 << ' ';
    }
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}