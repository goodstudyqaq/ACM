#include <bits/stdc++.h>

#include <algorithm>

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
        T res = T();
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

struct Max {
    int v;
    Max(int x = -1E9) : v{x} {}

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
    vector<int> a(n + 1);
    vector<long long> sum(n + 1);
    vector<long long> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i] + sum[i - 1];
        x.push_back(sum[i]);
    }
    x.push_back(0);

    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    vector<int> dp(n + 1);
    BIT<Max> bit(x.size());

    int zero_idx = lower_bound(x.begin(), x.end(), 0) - x.begin() + 1;
    bit.add(zero_idx, 0);
    debug(x);

    for (int i = 1; i <= n; i++) {
        int idx = lower_bound(x.begin(), x.end(), sum[i]) - x.begin() + 1;
        if (sum[i] >= 0) {
            dp[i] = i;
        } else {
            Max val = bit.query(idx);
            dp[i] = val.v + i;
        }
        dp[i] = max(dp[i - 1], dp[i]);
        bit.add(idx, dp[i] - i);
        // debug(i, dp[i], idx);
    }

    int res = dp[n];
    cout << res << endl;
    return 0;
}