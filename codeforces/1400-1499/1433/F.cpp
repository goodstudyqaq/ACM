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
    int n, m, k;
    cin >> n >> m >> k;
    vector a = vector(n + 1, vector(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(n + 1, vector(k, -inf));
    dp[0][0] = 0;

    int half = m / 2;
    for (int i = 1; i <= n; i++) {
        vector ndp = vector(m + 1, vector(half + 1, vector(k, -inf)));
        ndp[0][0][0] = 0;
        for (int j = 1; j <= m; j++) {
            for (int num = 0; num <= j && num <= half; num++) {
                for (int mod = 0; mod < k; mod++) {
                    ndp[j][num][mod] = max(ndp[j][num][mod], ndp[j - 1][num][mod]);
                    if (num > 0) {
                        ndp[j][num][mod] = max(ndp[j][num][mod], ndp[j - 1][num - 1][(mod - a[i][j] % k + k) % k] + a[i][j]);
                    }
                }
            }
        }
        for (int mod = 0; mod < k; mod++) {
            for (int num = 0; num <= half; num++) {
                for (int mod2 = 0; mod2 < k; mod2++) {
                    dp[i][mod] = max(dp[i][mod], dp[i - 1][mod2] + ndp[m][num][(mod - mod2 + k) % k]);
                }
            }
        }
    }

    int res = dp[n][0];
    cout << res << endl;
    return 0;
}