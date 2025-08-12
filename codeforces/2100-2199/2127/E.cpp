#include <bits/stdc++.h>

#include "graph/graph-template.hpp"
#include "graph/tree/doubling-lowest-common-ancestor.hpp"

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
    int n, k;
    cin >> n >> k;
    vector<int> w(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    vector<vector<int>> color_idx(k + 1);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        color_idx[c[i]].push_back(i);
    }
    Graph<int> g(n);
    g.read(n - 1);

    if (color_idx[0].size() == n) {
        cout << 0 << '\n';

        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        }
        cout << '\n';
        return;
    }

    DoublingLowestCommonAncestor LCA(g);
    LCA.build(0);

    // 还是要写一个 dfs 序
    vector<int> stt(n);
    int timestamp = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        stt[u] = timestamp++;
        for (auto v : g[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
    };
    dfs(0, -1);

    vector<int> cnt(n);
    long long mi_cost = 0;

    /*
    3 种可能
    1. 在多个颜色的虚树下面 -> 一定有贡献
    2. 在一个虚树下面 -> 那么颜色涂成这个颜色
    3. 不在虚树下面 -> 肯定无色，孩子有颜色的话就跟孩子一个颜色，没有颜色就跟上面的一个颜色
    */

    vector<bool> vis(n);
    for (int i = 1; i <= k; i++) {
        sort(color_idx[i].begin(), color_idx[i].end(), [&](int x, int y) {
            return stt[x] < stt[y];
        });
        int sz = color_idx[i].size();
        for (int j = 0; j < sz; j++) {
            cnt[color_idx[i][j]]++;
            vis[color_idx[i][j]] = 1;
        }
        vector<int> V;
        for (int j = 0; j < sz - 1; j++) {
            int father = LCA.lca(color_idx[i][j], color_idx[i][j + 1]);
            if (vis[father] == 0) {
                cnt[father]++;
                V.push_back(father);
                vis[father] = 1;
            }
            // 方案1，2 满足
            if (c[father] == 0) {
                c[father] = i;
            }
        }
        for (int j = 0; j < sz; j++) {
            vis[color_idx[i][j]] = 0;
        }
        for (auto u : V) {
            vis[u] = 0;
        }
    }
    debug(cnt);

    for (int i = 0; i < n; i++) {
        if (cnt[i] > 1) {
            mi_cost += w[i];
        }
    }

    function<void(int, int, int)> dfs2 = [&](int u, int pre, int color) {
        if (c[u] == 0) {
            c[u] = color;
        } else {
            color = c[u];
        }
        for (auto v : g[u]) {
            if (v == pre) continue;
            dfs2(v, u, color);
        }
    };


    for (int i = 1; i <= k; i++) {
        if (color_idx[i].size()) {
            dfs2(0, -1, i);
            break;
        }
    }
    cout << mi_cost << '\n';
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
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