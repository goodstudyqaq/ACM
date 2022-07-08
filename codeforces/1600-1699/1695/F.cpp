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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;

    vector<vector<pii>> V(n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        V[x].push_back({y, i});
        V[y].push_back({x, i});
    }

    vector<int> vis(n * 2 + 1);
    vector<int> vis2(n + 1);
    vector<int> stk;
    function<void(int)> dfs = [&](int u) {
        stk.emplace_back(u);
        if (vis[u]) return;
        vis[u] = 1;

        for (auto e : V[u]) {
            if (vis2[e.second]) continue;
            vis2[e.second] = 1;
            dfs(e.first);
            stk.emplace_back(u);
        }
    };
    vector<vector<int>> ans(2);
    vector<vector<char>> sol1(2), sol2(2);
    for (int i = 1; i <= n * 2; i++) {
        if (vis[i]) continue;
        stk.clear();
        dfs(i);
        if (stk.size() == 1) continue;
        if (stk.size() == 3) {
            cout << -1 << endl;
            return 0;
        }
        int sz = stk.size();
        // sz = 2k + 1
        int cols = sz / 2;
        int now = 0;
        debug(stk);

        for (int i = 0; i < cols; i++) {
            ans[0].emplace_back(stk[i]);
        }

        for (int i = sz - 2; i > sz - cols - 2; i--) {
            ans[1].emplace_back(stk[i]);
        }

        for (int i = 0; i + 1 < cols; i += 2) {
            sol1[0].emplace_back('L');
            sol1[0].emplace_back('R');
            sol1[1].emplace_back('L');
            sol1[1].emplace_back('R');
        }

        if (cols % 2) {
            sol1[0].emplace_back('U');
            sol1[1].emplace_back('D');
        }

        sol2[0].emplace_back('U');
        sol2[1].emplace_back('D');

        for (int i = 1; i + 1 < cols; i += 2) {
            sol2[0].emplace_back('L');
            sol2[0].emplace_back('R');
            sol2[1].emplace_back('L');
            sol2[1].emplace_back('R');
        }
        if (cols % 2 == 0) {
            sol2[0].emplace_back('U');
            sol2[1].emplace_back('D');
        }
    }
    debug(ans);

    cout << 2 << ' ' << ans[0].size() << endl;
    for (int i = 0; i < 2; i++) {
        for (auto v : ans[i]) {
            cout << v << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < 2; i++) {
        for (auto v : sol1[i]) {
            cout << v;
        }
        cout << endl;
    }
    for (int i = 0; i < 2; i++) {
        for (auto v : sol2[i]) {
            cout << v;
        }
        cout << endl;
    }
    return 0;
}