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
    long long n, k, x;
    cin >> n >> k >> x;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const long long inf = numeric_limits<long long>::max() / 2;
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, -inf));
    dp[0][0] = 0;

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i && j <= k; j++) {
            // dp[i][j] 以 i 位结尾的子数组，用了 j 个
            // 不用

            if (j <= i - 1) {
                dp[i][j] = max(dp[i][j], max(dp[i - 1][j], 0LL) + a[i] - x);
            }
            // 用
            if (j > 0) {
                dp[i][j] = max(dp[i][j], a[i] + x + max(0LL, dp[i - 1][j - 1]));
            }

            // 后面还有 n - i 个数，意味着后面可以最多用 n - i 个, 前面至少用 k - (n - i)
            if (j + n - i >= k) {
                // debug(i, j, dp[i][j]);
                ans = max(ans, dp[i][j]);
            }
        }
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