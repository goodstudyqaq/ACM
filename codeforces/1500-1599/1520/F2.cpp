#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// #define endl '\n'

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

    int search(T val) {  // 找到最后一个 res，使得 [1, res] 的前缀和 <= val
        int level = largest_bit(n);
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && val >= a[res + (1 << i)]) {  // 注意 val >= a[res + (1 << i)], 如果求的是 < val，那么相应也要去掉 = 号
                res += (1 << i);
                val -= a[res];
            }
        }
        return res;
    }
};

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int n, t;
    cin >> n >> t;

    map<int, int> Mp;
    BIT<int> bit(n + 1);
    auto query = [&](int idx) {
        // 返回 0 的个数
        if (Mp.count(idx)) {
            return Mp[idx];
        }
        // debug(idx);
        cout << "? 1 " << idx << endl;
        fflush(stdout);
        int res;
        cin >> res;

        int tmp = bit.query(idx);
        bit.add(idx, -tmp);
        bit.add(idx + 1, tmp);
        return Mp[idx] = idx - res;
    };

    auto ask = [&](int idx) {
        debug(idx);
        int res = query(idx);
        int tmp = bit.query(idx);
        return res + tmp;
    };

    auto out = [&](int ans) {
        cout << "! " << ans << endl;
        fflush(stdout);
    };

    auto update = [&](int ans) {
        bit.add(ans, -1);
    };

    while (t--) {
        int k;
        cin >> k;
        debug(k);
        int l = 1, r = n;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            if (ask(m) >= k) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        out(ans);
        update(ans);
    }
}