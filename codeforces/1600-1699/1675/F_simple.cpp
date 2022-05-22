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
    int n, k;
    int x, y;
    cin >> n >> k;
    cin >> x >> y;
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    a.push_back(y);

    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> fa(n + 1), dep(n + 1);
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        fa[u] = pre;
        dep[u] = d;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(x, 0, 0);

    vector<bool> vis(n + 1);
    int ans = 0;
    vis[x] = 1;
    for (auto u : a) {
        while (!vis[u]) {
            vis[u] = 1;
            ans += 2;
            u = fa[u];
        }
    }
    ans -= dep[y];
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