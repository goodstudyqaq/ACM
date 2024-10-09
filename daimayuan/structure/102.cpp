// http://oj.daimayuan.top/course/15/problem/635
#include <bits/stdc++.h>

#include "./structure/others/binary-indexed-tree.hpp"

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
    BIT<unsigned long long> bit(n);
    BIT<unsigned long long> bit2(n);

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int l, r;
            unsigned long long d;
            cin >> l >> r >> d;
            bit.add(l, d);
            bit.add(r + 1, -d);
            bit2.add(l, d * l);
            bit2.add(r + 1, -d * (r + 1));
        } else {
            int x;
            cin >> x;
            cout << bit.query(x) * (x + 1) - bit2.query(x) << endl;
        }
    }
}