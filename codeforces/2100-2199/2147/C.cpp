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
    int n;
    string s;
    cin >> n >> s;

    vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            dp[i + 1] = dp[i];
        } else {
            if (i == 0) {
                dp[i + 1] = 1;
                continue;
            }
            if (i - 1 >= 0 && s[i - 1] == '0') {
                dp[i + 1] |= dp[i - 1];
                dp[i + 1] |= dp[i];
            }
            if (i - 2 >= 0 && s[i - 1] == '1' && s[i - 2] == '0') {
                dp[i + 1] |= dp[i - 2];
            }
        }
    }
    if (dp[n] == 1) {
        cout << "YES\n";
    } else {
        if (s[n - 1] == '0') {
            if (dp[n - 1] == 1) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            cout << "NO\n";
        }
    }
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