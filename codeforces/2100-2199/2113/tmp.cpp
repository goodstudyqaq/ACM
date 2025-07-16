#line 1 "D.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/others/binary-indexed-tree.hpp"
using namespace std;
/*
树状数组二分:
http://oj.daimayuan.top/course/15/problem/636
https://leetcode.com/problems/finding-mk-average/
*/
//
template <typename T>
struct BIT {
#define lowbit(x) x & -x
    int n;
    vector<T> a;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) {}
    BIT() {}

    void init(int _n) {
        n = _n;
        a = vector<T>(n + 1);
    }
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

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int lower_bound(T x) const {
        // 单调增的时候才能用, 找到第一个下标使得前缀和大于等于 x
        int level = largest_bit(n);
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && a[res + (1 << i)] < x) {
                res += (1 << i);
                x -= a[res];
            }
        }
        return res + 1;
    }

    int upper_bound(T x) const {
        // 单调增的时候才能用, 找到第一个下标使得前缀和大于 x
        int level = largest_bit(n);
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && a[res + (1 << i)] <= x) {
                res += (1 << i);
                x -= a[res];
            }
        }
        return res + 1;
    }
};

// struct Max {
//     int v;
//     Max(int x = -1E9) : v{x} {}

//     Max &operator+=(Max a) {
//         v = std::max(v, a.v);
//         return *this;
//     }
// };
#line 4 "D.cpp"

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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    BIT<int> pre(2 * n + 1), suf(2 * n + 1);

    for (int i = 0; i < n; i++) {
        pre.add(a[i], 1);
    }
    int now = 0;
    int mx = 2 * n;
    while (now < n) {
        // b 被干掉了 now 个，那么就是 num 个 a 被干掉，前 num 个 a 的值都是比 b[now] 大
        int num = n - now;
        int cnt = pre.query(b[now]);

        // cnt 比 b[now] 小的个数
        int cnt2 = suf.query(mx) - suf.query(b[now]);
        // cnt2 后面 比 b[now] 大的个数

        if (cnt == 0 || (cnt == 1 && cnt2 > 0)) {
            cout << num << '\n';
            return;
        }

        // 不满足
        int go = now;
        pre.add(a[n - go - 1], -1);
        suf.add(a[n - go - 1], 1);
        go++;
        now = go;
    }
    cout << "0\n";
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
