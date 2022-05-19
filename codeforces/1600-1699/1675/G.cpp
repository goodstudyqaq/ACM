#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> pancakes(1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < a[i]; j++) {
            pancakes.emplace_back(i);
            int sz = pancakes.size();
            pancakes[sz - 1] += pancakes[sz - 2];
        }
        if (i) {
            a[i] += a[i - 1];
        }
    }
    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(n, vector(m + 1, vector(m + 1, inf)));
    int sz = pancakes.size();
    debug(sz);
    debug(pancakes);

    for (int i = 0; i <= m; i++) {
        if (i <= a[0]) {
            dp[0][i][i] = a[0] - i;
        } else {
            dp[0][i][i] = pancakes[i];
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = i; j <= m; j++) {
            dp[0][i][j] = min(dp[0][i][j], dp[0][i + 1][j]);
        }
    }
    debug(dp);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = j; k <= m; k++) {
                if (a[i] >= k) {
                    int val = a[i] - k;
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - j] + val);
                } else {
                    int cnt = min(k - a[i], j);
                    int val = pancakes[k] - pancakes[k - cnt] - cnt * i;
                    debug(i, j, k, val);
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k - j] + val);
                }
            }
        }

        for (int j = m - 1; j >= 0; j--) {
            for (int k = (i + 1) * j; k <= m; k++) {
                dp[i][j][k] = min(dp[i][j][k], dp[i][j + 1][k]);
            }
        }
    }
    cout << dp[n - 1][0][m] << endl;
    return 0;
}