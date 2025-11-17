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
    vector<int> in(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
        in[u]++;
        in[v]++;
    }

    vector<int> fa(n);
    vector<int> color(n);
    function<void(int, int)> dfs = [&](int u, int pre) {
        fa[u] = pre;
        if (u) {
            color[u] = color[pre] ^ 1;
        }
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
    };
    color[0] = 0;
    dfs(0, -1);

    vector<int> route;
    int now = n - 1;
    while (now != -1) {
        route.push_back(now);
        now = fa[now];
    }
    reverse(route.begin(), route.end());
    typedef array<int, 2> a2;
    vector<a2> ans;

    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (in[i] == 1 && i != n - 1) {
            Q.push(i);
        }
    }
    int f = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        // debug(u, color[u], f);
        if (color[u] == f) {
            ans.push_back({1, 0});
            f ^= 1;
            ans.push_back({2, u});
        } else {
            ans.push_back({1, 0});
            ans.push_back({1, 0});
            ans.push_back({2, u});
        }
        for (auto v : V[u]) {
            in[v]--;
            if (in[v] == 1 && v != n - 1) {
                Q.push(v);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto it : ans) {
        if (it[0] == 1) {
            cout << 1 << '\n';
        } else {
            cout << it[0] << ' ' << it[1] + 1 << '\n';
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