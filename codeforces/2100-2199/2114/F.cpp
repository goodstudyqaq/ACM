#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    int x, y, k;
    cin >> x >> y >> k;

    auto check = [&](int y) {
        for (int i = 2; i <= sqrt(y); i++) {
            if (y % i == 0) {
                if (k < i) {
                    return false;
                }
                while (y % i == 0) {
                    y /= i;
                }
            }
        }
        // debug(y);
        if (y != 1) {
            if (k < y) {
                return false;
            }
        }
        return true;
    };

    auto work = [&](int val) -> int {
        vector<int> v;
        for (int i = 1; i <= sqrt(val); i++) {
            if (val % i == 0) {
                v.push_back(i);
                int i2 = val / i;
                if (i2 != i) {
                    v.push_back(i2);
                }
            }
        }
        sort(v.begin(), v.end());
        int sz = v.size();

        vector<int> dp(sz, 1e9);
        dp[sz - 1] = 0;

        for (int i = sz - 2; i >= 0; i--) {
            for (int j = i + 1; j < sz; j++) {
                if (v[j] % v[i] == 0 && v[j] / v[i] <= k) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[0];
    };

    int g = gcd(x, y);
    debug(x / g, y / g);
    if (check(x / g) && check(y / g)) {
        int ans = work(x / g) + work(y / g);
        cout << ans << '\n';
    } else {
        cout << -1 << '\n';
    }
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