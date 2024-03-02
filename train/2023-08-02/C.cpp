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
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n, vector<int>(n));
    vector<vector<int>> path(n, vector<int>(n, -1));

    RMQ<int> great(a, greater<int>());
    RMQ<int> les(a, less<int>());

    long long ans = 0;
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int r = i + len - 1;

            if (dp[i][r - 1] == (r - 1 - i)) {
                if (great.rmq_value(i, r - 1) < a[r]) {
                    dp[i][r] = r - 1 - i;
                    path[i][r] = r - 1;
                } else {
                    dp[i][r] = r - i;
                    path[i][r] = -1;
                }
            } else {
                int the_path = path[i][r - 1];
                if (great.rmq_value(i, the_path) < a[r]) {
                    dp[i][r] = dp[i][the_path] + dp[the_path + 1][r];
                    path[i][r] = the_path;
                } else {
                    dp[i][r] = r - i;
                    path[i][r] = -1;
                }

            } 
            // debug(i, r, dp[i][r], idx);
            ans += dp[i][r];
        }
    }
    cout << ans << endl;


    


    // vector<vector<int>> V(n + 1);

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         if (a[i] > a[j]) V[i].push_back(j);
    //     }
    // }
    // vector<int> now_idx(n + 1);
    // for (int i = 1; i <= n - 1; i++) {
    //     for (int j = 1; j <= i; j++) {
    //         while (now_idx[j] < V[j].size() && V[j][now_idx[j]] <= i) {
    //             now_idx[j]++;
    //         }
    //     }
    //     if (a[i] > a[i + 1]) {
    //         ans += 1LL * i * (n - i);
    //     } else {
    //         for (int j = 1; j <= i; j++) {
    //             if (now_idx[j] < V[j].size()) {
    //                 int tmp = V[j][now_idx[j]];
    //                 ans += n - tmp + 1;
    //             }
    //         }
    //     }
    //     debug(i, ans);
    // }
    // cout << ans << endl;
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