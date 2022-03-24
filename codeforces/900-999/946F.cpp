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

const int mod = 1e9 + 7;
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, x;
    cin >> n >> x;
    vector<vector<vector<int>>> dp = vect(0, x + 1, n + 1, n + 1);
    // dp[x][l][r] s[l~r] 在 f(x) 出现的次数

    string s;
    cin >> s;

    if (x == 0) {
        int res = 0;
        if (s == "0") {
            res = 1;
        }
        cout << res << endl;
        return 0;
    } else if (x == 1) {
        int res = 0;
        if (s == "1") {
            res = 1;
        }
        cout << res << endl;
        return 0;
    }

    vector<int> mod_two = vect(0, x + 1);

    mod_two[0] = 2, mod_two[1] = 2;
    for (int i = 2; i <= x; i++) {
        mod_two[i] = 1LL * mod_two[i - 1] * mod_two[i - 2] % mod;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            dp[0][i + 1][i + 1] = 1;
        } else {
            dp[1][i + 1][i + 1] = 1;
        }
    }

    for (int i = 2; i <= x; i++) {
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                (dp[i][l][r] += 1LL * dp[i - 1][l][r] * (r == n ? mod_two[i - 2] : 1) % mod) %= mod;
                (dp[i][l][r] += 1LL * dp[i - 2][l][r] * (l == 1 ? mod_two[i - 1] : 1) % mod) %= mod;
                for (int k = l; k < r; k++) {
                    (dp[i][l][r] += 1LL * dp[i - 1][l][k] * dp[i - 2][k + 1][r] % mod) %= mod;
                }
            }
        }
    }
    cout << dp[x][1][n] << endl;
    return 0;
}