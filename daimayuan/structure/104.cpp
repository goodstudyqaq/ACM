// http://oj.daimayuan.top/course/15/problem/636
#include "./structure/others/binary-indexed-tree.hpp"
#include <bits/stdc++.h>

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
    BIT<long long> bit(n);
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.add(i, a[i]);
    }

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, d;
            cin >> x >> d;
            bit.add(x, d - a[x]);
            a[x] = d;
        } else {
            long long s;
            cin >> s;
            cout << bit.upper_bound(s) - 1 << endl;
        }
    }
}