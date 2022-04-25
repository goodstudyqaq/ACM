#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, p;
    cin >> n >> p;
    vector V = vector(n + 1, vector(p, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            cin >> V[i][j];
        }
        sort(V[i].begin(), V[i].end());
    }

    const long long inf = numeric_limits<long long>::max() / 2;
    vector dp = vector(n + 1, vector(2, inf));

    dp[1][1] = V[1][p - 1];
    dp[1][0] = V[1][p - 1] * 2 - V[1][0];
    for (int i = 2; i <= n; i++) {
        long long tmp = V[i][p - 1] - V[i][0];
        dp[i][0] = min(dp[i][0], dp[i - 1][0] + abs(V[i - 1][0] - V[i][p - 1]) + tmp);
        dp[i][0] = min(dp[i][0], dp[i - 1][1] + abs(V[i - 1][p - 1] - V[i][p - 1]) + tmp);
        dp[i][1] = min(dp[i][1], dp[i - 1][0] + abs(V[i - 1][0] - V[i][0]) + tmp);
        dp[i][1] = min(dp[i][1], dp[i - 1][1] + abs(V[i - 1][p - 1] - V[i][0]) + tmp);
    }
    cout << min(dp[n][0], dp[n][1]) << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}