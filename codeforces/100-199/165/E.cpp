#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<int> a(n);
    const int LIMIT = 22;
    const int maxa = 1 << LIMIT;
    vector<int> dp(maxa, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[a[i]] = a[i];
    }

    for (int i = 1; i < maxa; i++) {
        if (dp[i] != -1) continue;
        for (int j = 0; j < LIMIT; j++) {
            if (((i >> j) & 1) && dp[i ^ (1 << j)] != -1) {
                dp[i] = dp[i ^ (1 << j)];
                break;
            }
        }
    }

    int rev = (1 << LIMIT) - 1;

    for (int i = 0; i < n; i++) {
        int val = a[i];
        int val2 = rev ^ val;
        cout << dp[val2] << ' ';
    }
    cout << '\n';
}