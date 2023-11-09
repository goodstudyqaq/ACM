// http://oj.daimayuan.top/course/15/problem/635

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

template <typename T>
struct BIT {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    BIT<unsigned long long> bit1(n), bit2(n);

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int l, r;
            unsigned long long d;
            cin >> l >> r >> d;
            bit1.add(l, d), bit1.add(r + 1, -d);
            bit2.add(l, d * l), bit2.add(r + 1, -d * (r + 1));
        } else {
            int x;
            cin >> x;
            cout << bit1.query(x) * (x + 1) - bit2.query(x) << endl;
        }
    }
    return 0;
}