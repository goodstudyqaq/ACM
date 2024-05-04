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
    int nxt_idx(int idx, T val) {
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

void solve() {
    int n;
    long long x, y;
    cin >> n >> x >> y;
    vector<long long> a(n + 1);
    vector<long long> b(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] - i + 1;
    }

    b[n + 1] = 1e18;
    RMQ<long long> rmq(b, [&](long long x, long long y) {
        return x > y;
    });

    int idx = rmq.nxt_idx(1, x);
    debug(b);

    int circle_score = idx - 1 - (n - idx + 1);
    debug(idx, circle_score);
    if (circle_score <= 0) {
        if (x + idx - 1 >= y) {
            cout << y - x << endl;
        } else {
            cout << -1 << endl;
        }
        return;
    }

    long long ans = 0;
    while (x < y) {
        // x -> b[idx]
        debug(x, y);

        long long diff = b[idx] - x;
        long long times = (diff + circle_score - 1) / circle_score;

        long long mx = x + (times - 1) * circle_score + idx - 1;
        if (mx >= y) {
            if (y <= x + idx - 1) {
                ans += y - x;
                break;
            } else {
                long long t = (y - x - (idx - 1) + circle_score - 1) / circle_score;
                x += t * circle_score;
                ans += t * n;
                ans += y - x;
                break;
            }

        } else {
            ans += times * n;
            x += times * circle_score;
            idx = rmq.nxt_idx(idx, x);
            circle_score = idx - 1 - (n - idx + 1);
        }
    }
    cout << ans << endl;
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