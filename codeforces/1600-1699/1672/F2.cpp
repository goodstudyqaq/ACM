#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    vector V = vector(n + 1, vector<int>{});
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        V[a[i]].push_back(b[i]);
    }

    int mx_idx = 1;
    for (int i = 1; i <= n; i++) {
        if (V[mx_idx].size() < V[i].size()) {
            mx_idx = i;
        }
    }
    vector<int> vis(n + 1);
    vis[mx_idx] = 2;
    debug(mx_idx);

    bool have_circle = false;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (auto v : V[u]) {
            if (vis[v] == 2)
                continue;
            else if (vis[v] == 1) {
                debug(u, v);
                have_circle = true;
                break;
            } else {
                dfs(v);
            }
        }
        vis[u] = 2;
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }
    cout << (have_circle ? "WA" : "AC") << endl;
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