#include <bits/stdc++.h>

#include "./structure/union-find/weighted-union-find.hpp"

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
    int t = 0;
    WeightedUnionFind<long long> uf(n);
    for (int i = 0; i < q; i++) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            long long l, r, x;
            cin >> l >> r >> x;
            l = (l + t) % n + 1;
            r = (r + t) % n + 1;
            l--, r--;
            // a[l] - a[r] = x
            uf.unite(l, r, x);
        } else {
            long long l, r;
            cin >> l >> r;
            l = (l + t) % n + 1;
            r = (r + t) % n + 1;
            l--, r--;
            if (uf.find(l) != uf.find(r)) continue;

            long long tmp = uf.weight(l) - uf.weight(r);
            // a[l] - a[r] = tmp
            cout << tmp << '\n';
            t = abs(tmp);
        }
    }
}