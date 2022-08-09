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

    // RMQ(const vector<T>& _values = {}) {
    //     func = f;
    //     if (!_values.empty())
    //         build(_values);
    // }

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
        func = f;

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
};

void solve() {
    int m;
    cin >> m;
    vector<vector<int>> a(2, vector<int>(m));
    vector<int> v1, v2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int now = 0;
    for (int j = 0; j < m; j++, now++) {
        v1.push_back(a[0][j] - now);
        v2.push_back(a[1][j] - now);
    }
    for (int j = m - 1; j >= 0; j--, now++) {
        v1.push_back(a[1][j] - now);
        v2.push_back(a[0][j] - now);
    }
    debug(v1, v2);

    RMQ<int> rmq1, rmq2;
    rmq1.build(v1, [&](int a, int b) -> bool {
        return a > b;
    });
    rmq2.build(v2, [&](int a, int b) -> bool {
        return a > b;
    });

    vector<int> v3;

    for (int i = 0; i < m; i++) {
        if (i % 2 == 0) {
            v3.push_back(a[0][i]);
            v3.push_back(a[1][i]);
        } else {
            v3.push_back(a[1][i]);
            v3.push_back(a[0][i]);
        }
    }

    const int inf = numeric_limits<int>::max() / 2;
    int res = inf;

    int now_res = 0;

    int chose;
    auto get_interval = [&](int x, int y) -> pii {
        int l, r;
        l = y + 1;
        int num = m - l;
        r = m + num - 1;

        if (x ^ (y % 2) == 0) {
            r++;
        }
        return {l, r};
    };

    auto get_res = [&](int now, pii interval, int flag, int y) -> int {
        int res;
        if (flag) {
            res = rmq2.rmq_value(interval.first, interval.second + 1);
        } else {
            res = rmq1.rmq_value(interval.first, interval.second + 1);
        }
        res += y + 1;
        return max(res, now);
    };

    for (int i = 0; i < 2 * m - 1; i++) {
        int cow = i / 2;
        int flag = (cow % 2) ^ (i % 2);
        if (i < 2 * m - 2) {
            pii interval = get_interval(flag, i / 2);
            int tmp_res = get_res(now_res, interval, flag, i / 2);
            // debug(tmp_res);
            res = min(res, tmp_res + 2 * m - i - 1);
        }
        // debug(i, now_res, res);
        int val = v3[i + 1];
        now_res = max(now_res, val);
        now_res++;
    }
    debug(now_res);
    res = min(res, now_res);
    cout << res << endl;
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