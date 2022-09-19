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

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);

    auto work = [&](ll val) -> pii {
        int num2 = 0, num5 = 0;
        while (val % 2 == 0) {
            val /= 2;
            num2++;
        }
        while (val % 5 == 0) {
            val /= 5;
            num5++;
        }
        return {num2, num5};
    };
    vector<pii> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = work(a[i]);
    }
    debug(b);

    const int maxm = 60 * n;
    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(2, vector(k + 1, vector(maxm + 1, -inf)));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        int f1 = i % 2, f2 = f1 ^ 1;
        for (int j = 0; j <= min(i, k); j++) {
            for (int t = 0; t <= maxm; t++) {
                dp[f1][j][t] = dp[f2][j][t];
                if (j - 1 >= 0 && t - b[i - 1].first >= 0) {
                    dp[f1][j][t] = max(dp[f1][j][t], dp[f2][j - 1][t - b[i - 1].first] + b[i - 1].second);
                }
                // debug(i, j, t, dp[f1][j][t]);
            }
        }
    }

    int res = 0;
    for (int i = 0; i <= maxm; i++) {
        int five = dp[n % 2][k][i];
        // debug(i, five);
        res = max(res, min(five, i));
    }
    cout << res << endl;
    return 0;
}