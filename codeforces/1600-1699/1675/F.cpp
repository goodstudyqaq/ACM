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
    cin >> n >> k;
    int x, y;
    cin >> x >> y;
    vector<bool> vis(n + 1);

    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= k; i++) {
        int a;
        cin >> a;
        vis[a] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<ll> dp(n + 1);
    vector<int> dep(n + 1);
    vector<int> cnt(n + 1);
    vector<int> fa(n + 1);
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        dep[u] = d;
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(x, 0, 1);

    auto work = [&](int u, int v) -> vector<int> {
        if (dep[u] < dep[v]) swap(u, v);
        vector<int> res;
        while (dep[u] != dep[v]) {
            res.push_back(u);
            u = fa[u];
        }
        vector<int> res2;
        while (u != v) {
            res.push_back(u);
            res2.push_back(v);
            u = fa[u];
            v = fa[v];
        }
        res.push_back(u);
        reverse(res2.begin(), res2.end());
        for (auto it : res2) {
            res.push_back(it);
        }
        reverse(res.begin(), res.end());
        return res;
    };
    auto path = work(x, y);

    map<int, int> m_path;
    for (int i = 0; i < path.size(); i++) {
        m_path[path[i]] = i;
    }
    int p_sz = path.size();
    debug(m_path);

    function<void(int, int)> dfs2 = [&](int u, int pre) {
        cnt[u] = vis[u];
        int bef = -1, nxt = -1;
        if (m_path.count(u)) {
            bef = (m_path[u] > 0 ? path[m_path[u] - 1] : -1);
            nxt = ((m_path[u] < p_sz - 1) ? path[m_path[u] + 1] : -1);
        }
        // debug(u, pre, bef, nxt);
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs2(v, u);
            if (v != bef && v != nxt) {
                if (cnt[v]) {
                    dp[u] += 2 + dp[v];
                    cnt[u] += cnt[v];
                }
            }
        }
    };
    dfs2(x, 0);

    ll res = 0;
    for (auto v : path) {
        res += dp[v];
    }
    debug(dp);
    debug(path);
    debug(x, y);
    res += path.size() - 1;
    cout << res << endl;
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