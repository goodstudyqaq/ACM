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
template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int x, k, p;
    cin >> x >> k >> p;

    vector<vector<vector<vector<double>>>> dp = vect(0.0, 2, 2, 251, 256);
    typedef array<int, 3> a3;

    auto get_status = [&](int val) -> a3 {
        int a = val % 256;
        int b = val >> 8;
        if (b == 0) {
            return {0, 0, a};
        }
        int c = b % 2;
        int cnt = 0;
        while (b % 2 == c) {
            b /= 2;
            cnt++;
        }
        return {c, cnt, a};
    };

    a3 s = get_status(x);
    debug(s);
    dp[0][s[0]][s[1]][s[2]] = 1.0;
    double _p = 1.0 * p / 100.0;

    auto convert1 = [&](a3 s) -> a3 {
        // * 2
        int b = s[2];
        auto it = get_status(b * 2);

        if (s[1] == 0) {
            return it;
        }
        if (s[0] == 0) {
            if (it[1] > 0) {
                return {1, 1, it[2]};
            } else {
                return {0, s[1] + 1, it[2]};
            }
        } else {
            if (it[1] > 0) {
                return {1, s[1] + 1, it[2]};
            } else {
                return {0, 1, it[2]};
            }
        }
    };
    auto convert2 = [&](a3 s) -> a3 {
        // debug(s);
        int b = s[2];
        auto it = get_status(b + 1);

        if (s[1] == 0) {
            return it;
        }
        if (s[0] == 0) {
            if (it[1] > 0) {
                return {1, 1, it[2]};
            } else {
                return {s[0], s[1], it[2]};
            }

        } else {
            if (it[1] > 0) {
                return {0, s[1], it[2]};
            } else {
                return {s[0], s[1], it[2]};
            }
        }
    };

    for (int i = 0; i < k; i++) {
        int f = i % 2;

        for (int j = 0; j <= 250; j++) {
            for (int k = 0; k < 256; k++) {
                dp[f ^ 1][0][j][k] = 0;
                dp[f ^ 1][1][j][k] = 0;
            }
        }

        for (int t = 0; t < 2; t++) {
            for (int j = 0; j <= 250; j++) {
                for (int k = 0; k < 256; k++) {
                    if (dp[f][t][j][k] != 0) {
                        // _p 概率 {j, k} -> {}
                        a3 c1 = convert1({t, j, k});
                        a3 c2 = convert2({t, j, k});
                        // debug(c1, c2);
                        dp[f ^ 1][c1[0]][c1[1]][c1[2]] += dp[f][t][j][k] * p / 100.0;
                        dp[f ^ 1][c2[0]][c2[1]][c2[2]] += dp[f][t][j][k] * (100 - p) / 100.0;
                    }
                }
            }
        }
    }

    auto get_zero = [&](int val) {
        if (val == 0) return 1;
        int res = 0;
        while (val % 2 == 0) {
            res++;
            val /= 2;
        }
        return res;
    };

    double ans = 0;
    double one = 0;

    int tmp = x >> 8;
    int have_one = 0;
    while (tmp % 2 == 1) {
        have_one++;
        tmp /= 2;
    }
    debug(have_one);

    for (int t = 0; t < 2; t++) {
        for (int i = 0; i <= 250; i++) {
            for (int j = 0; j < 256; j++) {
                double it = dp[k % 2][t][i][j];
                if (it == 0) continue;
                // debug(i, j, it);
                one += it;
                if (j == 0) {
                    if (t == 0) {
                        ans += it * (8 + i);
                    } else {
                        ans += it * 8;
                    }
                } else {
                    int zero = get_zero(j);
                    ans += it * zero;
                }
            }
        }
    }

    debug(one);
    cout << ans << endl;
    return 0;
}