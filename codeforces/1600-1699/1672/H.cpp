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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    vector dp = vector(n, vector(2, 0));

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0];
        dp[i][1] = dp[i - 1][1];
        if (s[i] == s[i - 1]) {
            dp[i][s[i] - '0']++;
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << max(dp[r - 1][0] - dp[l - 1][0], dp[r - 1][1] - dp[l - 1][1]) + 1 << endl;
    }
    return 0;
}