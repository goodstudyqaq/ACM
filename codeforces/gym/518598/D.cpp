#include <bits/stdc++.h>

#include <limits>

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

void solve() {
    long long s, k;
    cin >> s >> k;

    long long ans = s * k;

    if (s % 10 == 0) {
        cout << s * k << endl;
        return;
    } else if (s % 10 == 5) {
        s += 5;
        k--;
        ans = max(ans, s * k);
        cout << ans << endl;
        return;
    } else if (s % 2 == 1) {
        s += s % 10;
        k--;
    }

    auto work = [&]() {
        // -80x2 + (20k - 4s)x + sk
        // -b/2a = (5k - s) / 40
        int l = 0, r = k / 4 - 1;
        long long ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            long long v1 = (s + 20LL * m) * (k - 4 * m);
            long long v2 = (s + 20LL * (m + 1)) * (k - 4 * m - 4);
            if (v1 < v2) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        if (ans == -1) {
            ans = l;
        } else {
            ans++;
        }
        debug(s, ans);
        return (s + 20LL * ans) * (k - 4 * ans);
    };

    for (int i = 0; i < 4; i++) {
        ans = max(ans, work());
        s += s % 10;
        k--;
        if (k < 0) break;
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