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
    long long x, y, k;
    cin >> x >> y >> k;

    // 每次去掉 y, 2y ...

    if (k < y) {
        cout << k << '\n';
        return;
    }

    long long l = 1, r = 1e12;




    auto check = [&](long long val) -> pll {
        bool ok = false;
        long long times = x;
        while (times) {
            if (val < y) break;
            long long tmp2 = val % y;
            long long remove = val / y;
            // 大于等于 tmp 都是 remove 的代价
            long long tmp_times = tmp2 / remove;
            long long real_times = min(times, tmp_times);
            times -= real_times;
            val -= real_times * remove;
            if (times == 0) break;
            if (val % y == 0) {
                ok = true;
            }
            val -= val / y;
            times--;
        }
        return {val, ok};
    };
    // check(10);

    auto it = check(r);

    if (it.first < k) {
        cout << -1 << '\n';
        return;
    }

    while (l <= r) {
        ll mid = l + r >> 1;
        pll ans = check(mid);
        // debug(l, r, mid, ans);
        if (ans.second == 1) {
            if (ans.first < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        } else {
            if (ans.first == k) {
                cout << mid << '\n';
                return;
            } else if (ans.first < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    cout << -1 << '\n';
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