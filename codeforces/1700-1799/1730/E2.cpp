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

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int max_index(int a, int b) const {
        return func(values[a], values[b]) ? a : b;
        // return values[a] > values[b] ? a : b;
    }

    void build(const vector<T>& _values, function<bool(T, T)> f) {
        values = _values;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_high.resize(levels);

        for (int k = 0; k < levels; k++)
            range_high[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_high[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_high[k][i] = max_index(range_high[k - 1][i], range_high[k - 1][i + (1 << (k - 1))]);
    }
    // [a, b)
    int rmq_index(int a, int b) const {
        assert(a < b);
        int level = largest_bit(b - a);
        return max_index(range_high[level][a], range_high[level][b - (1 << level)]);
    }

    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }

    int nxt_idx(int idx) {
        int sz = range_high.size() - 1;
        int now = idx;
        for (int i = sz; i >= 0; i--) {
            if (now + (1 << i) - 1 < n && max_index(range_high[i][now], idx) == idx) {
                // debug(now, i, range_high.size());
                now += (1 << i);
            }
        }
        // debug(idx, now + 1);
        return now;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    RMQ<int> rmq1 = RMQ<int>(a, [&](int a, int b) { return a < b; });
    RMQ<int> rmq2 = RMQ<int>(a, [&](int a, int b) { return a > b; });

    ll ans = 0;

    for (int i = n - 1; i >= 0; i--) {
        // debug(i);
        int l1 = i, l2 = i;
        int now_idx = i;
        int now_mx = a[i], now_mi = a[i];
        ll sub_ans = 0;

        while (now_idx < n) {
            int nxt_idx = (l1 == now_idx ? rmq1.nxt_idx(now_idx) : l1);
            int nxt2_idx = (l2 == now_idx ? rmq2.nxt_idx(now_idx) : l2);
            // debug(now_idx, nxt_idx, nxt2_idx);
            l1 = nxt_idx;
            l2 = nxt2_idx;
            int c_idx = min(nxt_idx, nxt2_idx);

            if (now_mx % now_mi == 0) {
                sub_ans += c_idx - now_idx;
            }
            if (c_idx == n) break;
            now_mx = max(now_mx, a[c_idx]);
            now_mi = min(now_mi, a[c_idx]);
            now_idx = c_idx;
        }
        debug(i, sub_ans);
        ans += sub_ans;
    }
    // debug(ans);
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
}