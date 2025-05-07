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
    int n, st, en;
    cin >> n >> st >> en;
    vector<vector<int>> V(n + 1);

    vector<int> in(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
        in[u]++;
        in[v]++;
    }
    vector<int> ans;

    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 1) {
            Q.push(i);
        }
    }

    vector<int> vis(n + 1);
    while (!Q.empty()) {
        auto u = Q.front();
        Q.pop();
        if (u == en) continue;
        ans.push_back(u);
        vis[u] = 1;
        for (auto v : V[u]) {
            if (vis[v] == 0) {
                in[v]--;
                if (in[v] == 1) {
                    Q.push(v);
                }
            }
        }
    }
    ans.push_back(en);
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << '\n';
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