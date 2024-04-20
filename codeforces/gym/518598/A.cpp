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

struct Edge {
    int u, v, w, idx;
    bool operator<(const Edge &v) const {
        return w < v.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = Edge{u, v, w, -1};
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < m; i++) {
        edges[i].idx = i;
        int u = edges[i].u, v = edges[i].v;
        V[u].push_back(i);
        V[v].push_back(i);
    }

    int l = 0, r = m;
    int ans = -1;

    vector<int> DFN(n + 1), LOW(n + 1), vis(n + 1);
    int id;
    vector<int> belong(n + 1);
    int cnt;
    vector<int> stack(n + 1);
    vector<int> in(n + 1);

    auto check = [&](int edge_num) -> bool {
        function<void(int)> tarjan = [&](int u) {
            // debug(u);
            DFN[u] = LOW[u] = ++id;
            stack.push_back(u);
            vis[u] = 1;
            for (auto e_idx : V[u]) {
                bool flag = false;
                auto e = edges[e_idx];
                if (e_idx < edge_num) {
                    // 小于的话，相当于无向边
                    flag = true;
                } else {
                    if (e.u == u) {
                        flag = true;
                    }
                }

                if (flag) {
                    int v = (e.u == u ? e.v : e.u);
                    if (!DFN[v]) {
                        tarjan(v);
                        LOW[u] = min(LOW[u], LOW[v]);
                    } else if (vis[v]) {
                        LOW[u] = min(LOW[u], DFN[v]);
                    }
                }
            }
            if (LOW[u] == DFN[u]) {
                cnt++;
                int v;
                do {
                    v = stack.back();
                    vis[v] = 0;
                    belong[v] = cnt;
                    stack.pop_back();
                } while (v != u);
            }
        };

        for (int i = 1; i <= n; i++) DFN[i] = 0, in[i] = 0;
        cnt = 0;

        for (int i = 1; i <= n; i++) {
            if (!DFN[i]) {
                debug(i);
                id = 0;
                tarjan(i);
            }
        }
        debug(belong);

        for (int i = 0; i < m; i++) {
            int u = belong[edges[i].u], v = belong[edges[i].v];
            if (u != v) {
                in[v]++;
            }
        }
        int zero = 0;
        for (int i = 1; i <= cnt; i++) {
            if (in[i] == 0) zero++;
        }
        return zero == 1;
    };
    // l = r = 1;

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    if (ans == -1) {
        cout << -1 << endl;
    } else if (ans == 0) {
        cout << 0 << endl;
    } else {
        cout << edges[ans - 1].w << endl;
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