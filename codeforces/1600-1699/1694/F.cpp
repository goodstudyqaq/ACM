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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    vector<int> dp(n + 1), pd(n + 1), f(n + 2);

    auto update = [&](auto self, int idx) {
        debug(idx);
        if (idx == n + 1) return;
        int val = 0;
        // idx 属于上升序列，下降序列的最大值
        if (a[idx] > pd[idx - 1]) {
            val = max(val, a[idx - 1]);
        }
        if (a[idx] > a[idx - 1]) {
            val = max(val, dp[idx - 1]);
        }

        // idx 属于下降序列，上升序列的最小值
        int val2 = n + 1;
        if (a[idx] < dp[idx - 1]) {
            val2 = min(val2, a[idx - 1]);
        }
        if (a[idx] < a[idx - 1]) {
            val2 = min(val2, pd[idx - 1]);
        }
        if (dp[idx] == val && pd[idx] == val2) {
            return;
        }

        dp[idx] = val;
        pd[idx] = val2;
        f[idx] = 0;
        if (val || val2 <= n) {
            self(self, idx + 1);
            f[idx] = f[idx + 1] + 1;
        }
    };

    for (int i = n; i >= 1; i--) {
        debug(i);
        dp[i] = n + 1;
        pd[i] = 0;

        if (i == n) {
            f[i] = 1;
            ans += f[i];
            continue;
        }

        update(update, i + 1);
        f[i] = f[i + 1] + 1;
        ans += f[i];
    }
    cout << ans << endl;
    return 0;
}