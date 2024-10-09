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
struct Max {
    long long v;
    Max(long long x = 0) : v{x} {}

    Max &operator+=(Max a) {
        v = std::max(v, a.v);
        return *this;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    BIT<Max> bit(2e5);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        Max val = bit.query(a[i] - 1);
        Max tmp = Max(val.v + a[i]);
        ans = max(ans, tmp.v);
        bit.add(a[i], tmp);
    }
    cout << ans << endl;
}