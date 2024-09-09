#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, k, p;
    cin >> n >> k >> p;

    // map<pair<int, int>, int> cache;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    vector<vector<int>> sum(n + 1, vector<int>(k + 1));
    vector<vector<int>> dp2(n + 1, vector<int>(k + 1));
    vector<vector<int>> sum2(n + 1, vector<int>(k + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (i == 1 || j == 0) {
                dp2[i][j] = 1;
            } else {
                for (int j2 = 0; j2 <= j; j2++) {
                    int l = 0, r = j - j2;
                    (dp2[i][j] += (1LL * dp2[i - 1][j2] * sum2[i - 1][r]) % p) %= p;
                }
            }
            sum2[i][j] = dp2[i][j];
            if (j) {
                (sum2[i][j] += sum2[i][j - 1]) %= p;
            }
        }
    }
    // debug(dp2[1]);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (i == 1 || j == 0) {
                dp[i][j] = 1;
            } else {
                for (int j2 = 0; j2 <= j; j2++) {
                    int l = j2 + 1, r = j - j2;

                    if (r >= l) {
                        int tmp = (sum[i - 1][r] - sum[i - 1][l - 1]) % p;
                        (dp[i][j] += (1LL * dp2[i - 1][j2] * tmp) % p) %= p;
                    }
                }
                dp[i][j] = (1LL * dp[i][j] * 2) % p;
            }
            sum[i][j] = dp[i][j];
            if (j) {
                (sum[i][j] += sum[i][j - 1]) %= p;
            }
        }
    }
    cout << (dp[n][k] + p) % p << endl;
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