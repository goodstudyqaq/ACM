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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int N, P;
    cin >> N >> P;
    vector<vector<int>> dp = vector(N + 1, vector(N + 1, 0));
    vector<vector<int>> sum = vector(N + 1, vector(N + 1, 0));

    auto cal = [&](int k) {
        int res = 1;
        while (k) {
            k /= 10;
            res++;
        }
        return res;
    };
    dp[0][0] = 1;
    /*
        [1, 9]
        [10, 99]
        [100, 999]
        [1000, 3000]
        */

    vector<int> R = {0, 9, 99, 999, 3000};
    vector<int> L = {0, 1, 10, 100, 1000};

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int tmp = cal(i);
            if (j >= tmp) {
                dp[i][j] = dp[0][j - tmp] * 26 % P;
            }

            for (int k = 1; k <= 4; k++) {
                if (i - 1 < L[k]) break;
                if (j < k + 1) continue;
                int r = min(R[k], i - 1);
                // k = [L[k], r] -> [i - r, i  - L[k]]
                long long tmp = sum[j - k - 1][i - L[k]];
                tmp = (tmp - sum[j - k - 1][i - r - 1]) % P;
                tmp = tmp * 25 % P;
                dp[i][j] = (dp[i][j] + tmp) % P;
            }

            sum[j][i] = (sum[j][i - 1] + dp[i][j]) % P;

            // for (int k = 1; k <= i; k++) {
            //     int tmp = cal(k);
            //     if (j >= tmp) {
            //         if (i == k) {
            //             dp[i][j] = dp[i][j] + dp[i - k][j - tmp] * 26;
            //         } else {
            //             dp[i][j] = dp[i][j] + dp[i - k][j - tmp] * 25;
            //         }
            //     }
            // }
        }
    }
    // debug(dp);
    long long ans = 0;
    for (int i = 1; i < N; i++) {
        ans += dp[N][i];
        ans %= P;
    }
    ans = (ans + P) % P;
    cout << ans << endl;
}