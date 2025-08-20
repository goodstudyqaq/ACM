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
    int s, k;
    cin >> s >> k;
    if (s % k == 0) {
        cout << k << '\n';
        return;
    }
    if (s >= k * k) {
        cout << max(k - 2, 1) << '\n';
        return;
    }
    // 如果 s >= k * k 那么就可以直接 k - 2 完成
    const int M = 1e6;
    bitset<M + 1> dp;
    bitset<M + 1> dp2;
    bitset<M + 1> mask;
    for (int i = 0; i <= s; i++) {
        mask.set(i);
    }
    dp[0] = 1;
    int flag = 1;
    int T = s;
    while (T--) {
        // debug(dp, dp2, flag, k);
        dp2.reset();
        if (flag) {
            dp2 = dp << k;
            int times = s / k;
            times--;
            while (times--) {
                dp2 |= (dp2 << k);
            }
        } else {
            dp2 = dp >> k;
            int times = s / k;
            times--;
            while (times--) {
                dp2 |= (dp2 >> k);
            }
        }
        dp = dp2;
        dp &= mask;
        if (dp[s]) {
            cout << k << '\n';
            return;
        }
        k--;
        if (k == 0) k = 1;
        flag ^= 1;
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