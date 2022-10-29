#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

    int nxt_idx(int idx, int val) {
        int sz = range_high.size() - 1;
        int now = idx;
        for (int i = sz; i >= 0; i--) {
            if (now + (1 << i) - 1 < n && values[range_high[i][now]] >= val) {
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
    int n;
    cin >> n;
    vector<int> a(n + 1), dp(n + 1);
    vector<ll> sum(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i] = min(dp[i - 1] + 1, a[i]);
        sum[i] = sum[i - 1] + dp[i];
        b[i] = a[i] - i;
    }
    RMQ<int> rmq(b, [&](int x, int y) {
        return x < y;
    });
    vector<ll> trace(n + 2);
    auto cal = [&](int x) -> ll {
        return 1LL * x * (x + 1) / 2;
    };
    for (int i = n; i >= 1; i--) {
        int idx = rmq.nxt_idx(i);
        trace[i] = trace[idx] + cal(a[i] + idx - 1 - i) - cal(a[i] - 1);
    }

    int q;
    cin >> q;
    while (q--) {
        int p, x;
        cin >> p >> x;
        int tmp = min(dp[p - 1] + 1, x);
        int idx2 = rmq.nxt_idx(p + 1, tmp - p);
        debug(tmp, idx2);
        ll ans = sum[p - 1] + trace[idx2] + cal(tmp + idx2 - 1 - p) - cal(tmp - 1);
        cout << ans << endl;
    }
    return 0;
}