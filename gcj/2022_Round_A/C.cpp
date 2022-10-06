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
    int N, K;
    cin >> N >> K;
    vector<vector<int>> x(N, vector<int>(K));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> x[i][j];
        }
    }
    vector<vector<int>> mi(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        vector<int> now = x[i];
        for (int j = i; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < K; k++) {
                now[k] = min(now[k], x[j][k]);
                sum += now[k];
            }
            mi[i][j] = sum;
        }
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector<vector<int>> dp(N, vector<int>(N, inf));
    for (int i = 0; i < N; i++) {
        dp[i][i] = mi[i][i] * 2;
    }
    // debug(mi);
    // debug(dp);
    for (int l = 2; l <= N; l++) {
        for (int i = 0; i + l - 1 < N; i++) {
            int r = i + l - 1;
            for (int k = i; k < r; k++) {
                dp[i][r] = min(dp[i][r], dp[i][k] + dp[k + 1][r] - 2 * mi[i][r]);
            }
        }
    }
    debug(dp);
    cout << dp[0][N - 1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}