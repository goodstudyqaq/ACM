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

ll get_dis(ll x1, ll y1, ll x2, ll y2) {
    ll x = x1 - x2;
    ll y = y1 - y2;
    return x * x + y * y;
}

struct Hungary {
    vector<int> cx, cy;
    vector<bool> used;
    int count;
    vector<vector<int>> g;

    bool dfs(int u) {
        for (auto v : g[u]) {
            if (!used[v]) {
                used[v] = 1;
                if (cy[v] == -1 || dfs(cy[v])) {
                    cy[v] = u;
                    cx[u] = v;
                    return 1;
                }
            }
        }
        return 0;
    }

    Hungary() {}
    Hungary(int uN, int vN, vector<vector<int>> &_g) {
        g = _g;
        cx.resize(uN, -1);
        cy.resize(vN, -1);
        used.resize(vN, 0);
        int res = 0;
        for (int u = 0; u < uN; u++) {
            used.assign(vN, 0);
            if (dfs(u)) res++;
        }
        count = res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<ll> x1(n), y1(n), x2(n + 1), y2(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> x1[i] >> y1[i];
    }
    for (int i = 0; i <= n; i++) {
        cin >> x2[i] >> y2[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        ll d0 = get_dis(x1[i], y1[i], x2[0], y2[0]);
        vector<ll> D(n);
        for (int j = 1; j <= n; j++) {
            ll d = get_dis(x1[i], y1[i], x2[j], y2[j]);
            D[j - 1] = d;
            if (d <= d0) {
                adj[i].push_back(j - 1);
            }
        }
        sort(adj[i].begin(), adj[i].end(), [&](int a, int b) {
            return D[a] < D[b];
        });
    }
    Hungary h(n, n, adj);
    int cnt = h.count;
    if (cnt < n) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    cout << "POSSIBLE" << endl;

    vector<int> f(n);
    vector<bool> vis(n);

    for (int i = 0; i < n; i++) {
        int x = -1;
        for (int j = 0; j < n; j++) {
            while (f[j] < adj[j].size() && vis[h.cy[adj[j][f[j]]]]) {
                f[j]++;
            }
            if (f[j] < adj[j].size() && h.cx[j] == adj[j][f[j]]) {
                x = j;
                break;
            }
        }
        cout << x + 1 << ' ' << h.cx[x] + 2 << endl;
        vis[x] = 1;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}