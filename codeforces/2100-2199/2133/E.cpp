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
    vector<set<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].insert(v);
        V[v].insert(u);
    }
    int choose_num = n / 4;

    vector<pii> ans;

    vector<int> color(n);  // color[u] = 1 绿 2 黄 3 黑

    function<void(int, int)> dfs = [&](int u, int pre) {
        bool is_leaf = true;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            is_leaf = false;
        }

        if (is_leaf) {
            color[u] = 1;
            return;
        }

        int green_cnt = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (color[v] == 1) {
                green_cnt++;
                if (green_cnt >= 3) {
                    color[u] = 3;
                    return;
                }
            } else if (color[v] == 2) {
                color[u] = 3;
                return;
            }
        }

        if (green_cnt == 2) {
            color[u] = 2;
        } else {
            color[u] = 1;
        }
    };

    dfs(0, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] == 3) {
            for (auto v : V[i]) {
                V[v].erase(i);
            }
            V[i].clear();
            ans.push_back({2, i});
        }
    }

    for (int i = 0; i < n; i++) {
        assert(V[i].size() <= 2);
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == 3) {
            ans.push_back({1, i});
        }
    }

    vector<int> vis2(n);

    function<void(int, int)> dfs2 = [&](int u, int pre) {
        vis2[u] = 1;
        ans.push_back({1, u});
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs2(v, u);
        }
    };

    for (int i = 0; i < n; i++) {
        if (color[i] != 3) {
            if (V[i].size() <= 1 && vis2[i] == 0) {
                dfs2(i, -1);
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto it : ans) {
        cout << it.first << ' ' << it.second + 1 << '\n';
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