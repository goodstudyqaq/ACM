#include <bits/stdc++.h>

#include <queue>
#include <vector>

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
typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        vector<array<int, 3>> e;

        for (auto &it : edges) {
            int val = it[2];
            if ((val >> i) & 1) {
                continue;
            } else {
                e.push_back(it);
            }
        }
        UnionFind uf(n + 1);
        for (auto &it : e) {
            uf.unite(it[0], it[1]);
        }
        if (uf.same(1, n)) {
            // 说明不要这个也可以连
            edges = e;
        } else {
            ans += (1 << i);
        }
    }
    cout << ans << '\n';
}