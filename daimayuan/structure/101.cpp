// http://oj.daimayuan.top/course/15/problem/634
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
    vector<int> a(n + 1);
    BIT<long long> bit(n);
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
            int x;
            cin >> x;
            cout << bit.query(x) << endl;
        }
    }
}