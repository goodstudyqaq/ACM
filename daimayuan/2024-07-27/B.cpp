#include <bits/stdc++.h>

#include "./graph/tree/rmq-lowest-common-ancestor.hpp"

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
    int n, q;
    cin >> n >> q;
    RMQLowestCommonAncestor<> lca(n);

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        lca.add_edge(p, i);
    }
    lca.build();
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << endl;
    }
    return 0;
}