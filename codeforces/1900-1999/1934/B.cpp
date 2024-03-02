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
    int n;
    cin >> n;
    vector<int> v({1, 3, 6, 10, 15});
    const int maxn = 30;
    vector<int> dp(maxn + 1, 10000);
    dp[0] = 0;
    for (int i = 1; i <= maxn; i++) {
        for (auto it : v) {
            if (i - it >= 0) {
                dp[i] = min(dp[i], dp[i - it] + 1);
            }
        }
    }

    int ans = dp[30] * (n / 30);
    int tmp = dp[n % 30];
    ans += tmp;
    cout << ans << endl;


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