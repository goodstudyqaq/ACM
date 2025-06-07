#line 1 "C.cpp"
#include <bits/stdc++.h>

#line 4 "C.cpp"

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
#line 6 "C.cpp"

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
    vector<pii> p(n);
    vector<int> Y;
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        Y.push_back(p[i].second);
    }
    sort(p.begin(), p.end());

    sort(Y.begin(), Y.end());
    Y.resize(unique(Y.begin(), Y.end()) - Y.begin());

    BIT<int> bit_left(n);
    BIT<int> bit_right(n);

    for (int i = 0; i < n; i++) {
        int idx = lower_bound(Y.begin(), Y.end(), p[i].second) - Y.begin();
        bit_right.add(idx + 1, 1);
    }

    auto check = [&](int val) -> pair<bool, int> {
        int idx = bit_left.lower_bound(val);

        int v1 = bit_left.query(idx);
        int v2 = bit_left.query(n) - v1;

        int v3 = bit_right.query(idx);
        int v4 = bit_right.query(n) - v3;

        if (min({v1, v2, v3, v4}) >= val) return {true, idx};

        idx = bit_right.lower_bound(val);
        v1 = bit_left.query(idx);
        v2 = bit_left.query(n) - v1;

        v3 = bit_right.query(idx);
        v4 = bit_right.query(n) - v3;

        if (min({v1, v2, v3, v4}) >= val) return {true, idx};
        return {false, -1};
    };

    auto work = [&]() -> pii {
        // 用二分 check ？
        int v1 = bit_left.query(n);
        int v2 = bit_right.query(n);

        int r = min(v1, v2) / 2;
        int l = 0;

        int ans = 0;
        int ansy = 0;
        while (l <= r) {
            int m = l + r >> 1;
            auto res = check(m);
            if (res.first) {
                ans = m;
                ansy = res.second;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return {ans, ansy};
    };

    int ans = 0;

    int now = 0;
    int ansx = 0, ansy = 0;
    while (now < n) {
        auto tmp_ans = work();
        if (ans < tmp_ans.first) {
            ans = tmp_ans.first;
            ansy = Y[tmp_ans.second - 1] + 1;
            ansx = p[now].first;
        }
        debug(now, ans);

        int go = now;
        while (go < n && p[go].first == p[now].first) {
            go++;
        }
        for (int i = now; i < go; i++) {
            int idx = lower_bound(Y.begin(), Y.end(), p[i].second) - Y.begin();
            bit_right.add(idx + 1, -1);
            bit_left.add(idx + 1, 1);
        }
        now = go;
    }

    // vector<int> cnt(4);
    // for (int i = 0; i < n; i++) {
    //     if (p[i].first >= ansx && p[i].second >= ansy) {
    //         cnt[0]++;
    //     } else if (p[i].first < ansx && p[i].second >= ansy) {
    //         cnt[1]++;
    //     } else if (p[i].first >= ansx && p[i].second < ansy) {
    //         cnt[2]++;
    //         debug(p[i]);
    //     } else {
    //         cnt[3]++;
    //     }
    // }
    // debug(cnt);

    cout << ans << '\n';
    cout << ansx << ' ' << ansy << '\n';
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
