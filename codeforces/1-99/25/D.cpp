#include <bits/stdc++.h>

#include "./structure/union-find/union-find.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    UnionFind uf(n);
    vector<pair<int, int>> ans;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (uf.same(u, v)) {
            ans.push_back({u, v});
        } else {
            uf.unite(u, v);
        }
    }
    cout << ans.size() << '\n';
    auto groups = uf.groups();
    debug(groups);
    assert(groups.size() == ans.size() + 1);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << ' ' << groups[i][0] + 1 << ' ' << groups[i + 1][0] + 1 << '\n';
    }
}