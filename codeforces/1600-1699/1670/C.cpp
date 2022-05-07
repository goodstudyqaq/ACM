#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        if (c[i]) {
            S.insert(c[i]);
        }
    }
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= n; i++) {
        int u = a[i], v = b[i];
        if (u == v) continue;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    bool flag;
    const int mod = 1e9 + 7;

    vector<bool> vis(n + 1);

    function<void(int, int)> dfs = [&](int u, int pre) {
        vis[u] = 1;
        if (S.count(u)) {
            flag = true;
        }
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (vis[v]) continue;
            dfs(v, u);
        }
    };

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0 && V[i].size() > 0) {
            flag = false;
            dfs(i, -1);
            if (flag == 0) {
                ans = ans * 2 % mod;
            }
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