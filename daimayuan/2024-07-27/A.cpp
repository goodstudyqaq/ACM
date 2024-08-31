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
template <typename T>
struct RMQ {
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_high;
    function<bool(T, T)> func;

    RMQ(const vector<T>& _values, function<bool(T, T)> f) {
        func = f;
        if (!_values.empty())
            build(_values, f);
    }
    RMQ() {}

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int max_index(int a, int b) const {
        return func(values[a], values[b]) ? a : b;
        // return values[a] > values[b] ? a : b;
    }

    void build(const vector<T>& _values, function<bool(T, T)> f) {
        values = _values;
        func = f;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_high.resize(levels);

        for (int k = 0; k < levels; k++)
            range_high[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_high[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++) {
                range_high[k][i] = max_index(range_high[k - 1][i], range_high[k - 1][i + (1 << (k - 1))]);
            }
    }
    // [a, b]
    int rmq_index(int a, int b) const {
        assert(a <= b);
        int level = largest_bit(b + 1 - a);
        return max_index(range_high[level][a], range_high[level][b + 1 - (1 << level)]);
    }

    // [a, b]
    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }

    int nxt_idx(int idx) {
        int sz = range_high.size() - 1;
        int now = idx;
        for (int i = sz; i >= 0; i--) {
            if (now + (1 << i) - 1 < n && max_index(range_high[i][now], idx) == idx) {
                now += (1 << i);
            }
        }
        return now;
    }
    int nxt_idx(int idx, T val) {  // <= 根据要求去变，该代码的含义是返回第一个大于 val 的位置
        int sz = range_high.size() - 1;
        int now = idx;
        for (int i = sz; i >= 0; i--) {
            if (now + (1 << i) - 1 < n && values[range_high[i][now]] <= val) {
                now += (1 << i);
            }
        }
        return now;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    RMQ<int> rmq(a, [&](int x, int y) {
        return x < y;
    });

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << rmq.rmq_value(l, r - 1) << endl;
    }
    return 0;
}