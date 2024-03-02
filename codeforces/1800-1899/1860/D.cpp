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

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int zero = count_if(s.begin(), s.end(), [&](char it) {
        return it == '0';
    });
    int limit = zero * (n - zero);

    vector<vector<int>> dp;  // dp[i][j] // i 个 0，j 个 01 的最小变换
    const int inf = numeric_limits<int>::max() / 2;
    dp.resize(zero + 1, vector<int>(limit + 1, inf));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        vector<vector<int>> ndp(zero + 1, vector<int>(limit + 1, inf));
        for (int j = 0; j <= zero; j++) {
            for (int k = 0; k <= limit; k++) {
                if (j - 1 >= 0) {
                    ndp[j][k] = min(ndp[j][k], dp[j - 1][k] + (s[i] != '0'));
                }
                if (k - j >= 0) {
                    ndp[j][k] = min(ndp[j][k], dp[j][k - j] + (s[i] != '1'));
                }
            }
        }
        dp = ndp;
    }
    cout << dp[zero][limit / 2] / 2 << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    solve();
    return 0;
}