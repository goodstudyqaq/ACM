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
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    long long ans = 0;

    auto work = [&](int l, int r) {
        int sz = r - l + 1;
        vector<int> dp(sz);

        for (int i = l; i <= r; i++) {
            dp[i - l] = 1;
            for (int j = l; j < i; j++) {
                if (p[i] < p[j]) {
                    dp[i - l] = max(dp[i - l], dp[j - l] + 1);
                }
            }
        }
        return dp[sz - 1];
    };

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ans += work(i, j);
        }
    }
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