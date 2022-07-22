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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> dp(n + 2);
    vector<int> frequence(n + 1);
    int max_fre = 0;

    for (int i = 1; i <= n + 1; i++) {
        if ((i - 1) % 2 == 0 && max_fre <= (i - 1) / 2) {
            dp[i] = 1;
        } else {
            dp[i] = 0;
        }
        if (i <= n) {
            frequence[a[i]]++;
            max_fre = max(max_fre, frequence[a[i]]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dp[i] == 0) continue;
        for (int j = 1; j <= n; j++) {
            frequence[j] = 0;
        }
        max_fre = 0;

        for (int j = i + 1; j <= n + 1; j += 1) {
            if ((j - i - 1) % 2 == 0 && max_fre <= (j - i - 1) / 2 && (j == n + 1 || a[j] == a[i])) {
                dp[j] = max(dp[j], dp[i] + 1);
            }
            if (j <= n) {
                frequence[a[j]]++;
                max_fre = max(max_fre, frequence[a[j]]);
            }
        }
    }
    debug(dp);
    cout << dp[n + 1] - 1 << endl;
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