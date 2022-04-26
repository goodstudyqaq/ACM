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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << "YES" << endl;
        return;
    }
    vector<int> dp(n);
    dp[0] = a[0] + 1;
    for (int i = 1; i < n; i++) {
        int val = dp[i - 1];
        if (val < a[i] - 2) {
            cout << "NO" << endl;
            return;
        }
        dp[i] = min(dp[i - 1] + 1, a[i] + 1);
    }
    cout << "YES" << endl;
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
}