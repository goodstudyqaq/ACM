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

int quick(int x, int y, int m) {
    int res = 1;
    while (y) {
        if (y % 2) {
            res = 1LL * res * x % m;
        }
        x = 1LL * x * x % m;
        y /= 2;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k, m;
    cin >> n >> k >> m;

    int ans = 0;
    for (int S = 0; S < k; S++) {
        vector<int> valid;
        for (int i = 0; i < k; i++) {
            if (i * 2 % k != S) {
                valid.push_back(i);
            }
        }

        vector<int> dp(k);

        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            vector<int> ndp(k);
            for (int j = 0; j < k; j++) {
                if (dp[j]) {
                    for (auto v : valid) {
                        int t = (j + v) % k;
                        ndp[t] = (ndp[t] + dp[j]) % m;
                    }
                }
            }
            dp = ndp;
        }

        ans = (ans + dp[S]) % m;
    }

    int res = ((quick(k, n, m) - ans) % m + m) % m;
    cout << res << endl;
}