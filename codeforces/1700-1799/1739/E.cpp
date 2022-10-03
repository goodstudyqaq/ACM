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
    vector<vector<int>> a(2, vector<int>(n + 2, 0));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            char it;
            cin >> it;
            a[i][j] = it - '0';
        }
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(2, vector(n + 1, -inf));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (dp[j][i] == -inf) continue;
            debug(i, j, dp[j][i]);
            dp[j][i + 1] = max(dp[j][i + 1], dp[j][i] + a[j][i + 1]);
            if (a[j ^ 1][i]) {
                dp[j ^ 1][min(n, i + 2)] = max(dp[j ^ 1][min(n, i + 2)], dp[j][i] + 1 + a[j ^ 1][i + 1] + a[j ^ 1][i + 2]);
            }
        }
    }
    cout << max(dp[0][n], dp[1][n]) << endl;
    return 0;
}