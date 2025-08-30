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
    int n;
    cin >> n;
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    // 求直径
    vector<int> dep(n), fa(n);
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        dep[u] = d;
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(0, -1, 0);

    int rt = 0;
    for (int i = 1; i < n; i++) {
        if (dep[rt] < dep[i]) {
            rt = i;
        }
    }
    dfs(rt, -1, 0);

    int rt2 = 0;
    for (int i = 0; i < n; i++) {
        if (dep[rt2] < dep[i]) {
            rt2 = i;
        }
    }

    vector<int> V2;
    int now = rt2;
    while (now != -1) {
        V2.push_back(now);
        now = fa[now];
    }

    int sz = V2.size();
    debug(V2);


    int ans = n - sz;
    if (ans == 0) {
        cout << -1 << '\n';
        return;
    }
    // cout << ans << '\n';

    vector<int> vis(n);
    for (int i = 0; i < sz; i++) {
        vis[V2[i]] = 1;
    }

    vector<int> V3;
    function<void(int, int)> dfs2 = [&](int u, int pre) {
        V3.push_back(u);
        for (auto v : V[u]) {
            if (v == pre || vis[v]) continue;
            dfs2(v, u);
        }
    };
    for (int i = 1; i < sz - 1; i++) {
        int u = V2[i];
        V3.clear();
        dfs2(u, -1);

        int sz2 = V3.size();
        int last = V2[i - 1];
        for (int j = 0; j < sz2 - 1; j++) {
            cout << last + 1 << ' ' << V3[j] + 1 << ' ' << V3[j + 1] + 1 << '\n';
            return;
        }
    }

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