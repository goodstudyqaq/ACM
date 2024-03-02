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
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, q;
    cin >> n >> m >> q;

    vector<int> x(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
    }

    vector<int> val(n + 1);
    for (int i = 1; i <= m; i++) {
        int v;
        cin >> v;
        val[x[i]] = v;
    }
    BIT<long long> bit(n + 1);
    vector<long long> now_val(n + 1);

    auto work = [&](int idx, int r, int val) {
        // val * r + val * (r - 1)
        long long tmp = 1LL * val * r * (r + 1) / 2;
        bit.add(idx, tmp - now_val[idx]);
        now_val[idx] = tmp;
    };

    work(n, n - 2, val[1]);

    set<int> S;
    S.insert(1);
    S.insert(n);

    auto work2 = [&](int idx) {
        auto right = S.lower_bound(idx);
        auto left = prev(right);

        work(idx, idx - (*left) - 1, val[*left]);
        work(*right, (*right) - idx - 1, val[idx]);
        S.insert(idx);
    };

    for (int i = 1; i <= m; i++) {
        int it = x[i];
        if (it == 1 || it == n) continue;
        work2(it);
    }
    debug(now_val);

    auto work3 = [&](int l, int r) {
        auto it1 = S.lower_bound(l);
        auto it2 = prev(S.upper_bound(r));

        long long res1 = bit.query(*it2) - bit.query(*it1);
        debug(res1);

        if (r != *it2) {
            auto it3 = next(it2);
            res1 += 1LL * val[*it2] * (*it3 - *it2 - 1 + *it3 - r) * (r - *it2) / 2;
        }
        debug(res1);

        if (l != *it1) {
            auto it3 = prev(it1);
            res1 += 1LL * val[*it3] * (*it1 - l) * (*it1 - l + 1) / 2;
        }
        debug(res1);
        return res1;
    };

    while (q--) {
        debug(q);
        int t;
        cin >> t;
        if (t == 1) {
            int x, v;
            cin >> x >> v;
            val[x] = v;
            work2(x);
        } else {
            int l, r;
            cin >> l >> r;

            cout << work3(l, r) << endl;
        }
    }
    return 0;
}