#include <bits/stdc++.h>

#include <functional>
#include <queue>

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    vector<vector<int>> V2(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V2[v].push_back(u);
    }

    const int inf = 1e9;
    vector<int> d(n + 1, inf);
    d[1] = 0;

    queue<int> Q;
    Q.push(1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (auto v : V[u]) {
            if (d[v] == inf) {
                d[v] = d[u] + 1;
                Q.push(v);
            }
        }
    }

    typedef pair<int, pair<int, int>> piii;
    priority_queue<piii, vector<piii>, greater<piii>> Q2;
    for (int i = 1; i <= n; i++) {
        Q2.push({d[i], {i, 0}});
    }

    vector<int> ans(n + 1, inf);
    for (int i = 1; i <= n; i++) ans[i] = d[i];
    debug(ans);

    vector<vector<int>> vis(n + 1, vector<int>(2, 0));
    while (!Q2.empty()) {
        auto [dis, state] = Q2.top();
        Q2.pop();
        auto [idx, flag] = state;
        // debug(dis, idx, flag);
        if (vis[idx][flag]) continue;
        vis[idx][flag] = 1;

        for (auto v : V2[idx]) {
            int need = (d[v] >= d[idx]);
            if (need) {
                if (flag == 0) {
                    if (ans[v] > d[idx]) {
                        ans[v] = d[idx];
                        Q2.push({ans[v], {v, 1}});
                    }
                }
            } else {
                // 不需要
                if (flag) {
                    if (ans[v] > ans[idx]) {
                        ans[v] = ans[idx];
                        Q2.push({ans[v], {v, 1}});
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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