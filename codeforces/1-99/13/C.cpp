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

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());

    int m = b.size();
    vector<long long> dp(m);

    for (int i = 0; i < m; i++) {
        dp[i] = abs(a[0] - b[i]);
        if (i) dp[i] = min(dp[i], dp[i - 1]);
    }

    for (int i = 1; i < n; i++) {
        vector<long long> ndp(m);
        for (int j = 0; j < m; j++) {
            ndp[j] = dp[j] + abs(a[i] - b[j]);
            if (j) ndp[j] = min(ndp[j], ndp[j - 1]);
        }
        dp = ndp;
    }
    cout << dp[m - 1] << endl;
    return 0;
}