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
    vector<int> dp(n);
    vector<int> pre(n);
    dp[0] = 1;
    pre[0] = -1;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[i - 1]) {
            dp[i] = dp[i - 1] + 1;
            pre[i] = i - 1;
        } else {
            if (i - 2 >= 0) {
                dp[i] = dp[i - 2] + 1;
                pre[i] = i - 2;
            } else {
                dp[i] = 1;
                pre[i] = -1;
            }
        }
    }
    long long ans = 0;

    int now = n - 1;
    vector<int> vis(n);
    while (now != -1) {
        vis[now] = 1;
        ans += 1LL * (now + 1) * (n - now);
        now = pre[now];
    }

    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            ans += i + 1;
        }
    }
    cout << ans << '\n';

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