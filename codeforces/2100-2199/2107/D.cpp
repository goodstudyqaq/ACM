#include <bits/stdc++.h>

#include <queue>

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
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> vis(n + 1);

    vector<int> dep(n + 1), fa(n + 1);
    auto find = [&](int u) -> vector<int> {

        int rt = u;
        function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
            dep[u] = d;
            fa[u] = pre;

            if (dep[u] > dep[rt]) {
                rt = u;
            } else if (dep[u] == dep[rt] && u > rt) {
                rt = u;
            }

            for (auto v : V[u]) {
                if (v == pre) continue;
                if (vis[v]) continue;
                dfs(v, u, d + 1);
            }
        };

        dfs(u, -1, 1);
        int rt1 = rt;
        dfs(rt1, -1, 1);

        vector<int> res;

        // 从 rt 到 rt1
        int now = rt;
        while (now != -1) {
            res.push_back(now);
            now = fa[now];
        }
        return res;
    };

    typedef pair<int, int> pii;
    typedef pair<int, pii> piii;
    auto get_state = [&](const vector<int> &v) {
        int sz = v.size();
        int l = v[0], r = v[sz - 1];
        if (l < r) swap(l, r);
        return piii{sz, {l, r}};
    };

    auto now = find(1);

    priority_queue<piii> Q;
    auto s = get_state(now);
    Q.push(s);
    map<piii, vector<int>> states;
    states[s] = now;

    while (!Q.empty()) {
        auto it = Q.top();
        Q.pop();
        cout << it.first << ' ' << it.second.first << ' ' << it.second.second << ' ';

        auto &nodes = states[it];
        for (auto it : nodes) {
            vis[it] = 1;
        }
        for (auto it : nodes) {
            for (auto v : V[it]) {
                if (vis[v] == 0) {
                    auto it2 = find(v);
                    auto s = get_state(it2);
                    states[s] = it2;
                    Q.push(s);
                }
            }
        }
        states.erase(it);
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