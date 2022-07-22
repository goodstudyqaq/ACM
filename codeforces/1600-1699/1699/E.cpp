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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    int mi = 1e9;
    vector<int> cnt(m + 1);
    vector<int> vis(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mi = min(mi, a[i]);
        vis[a[i]] = 1;
    }

    vector<int> dp(m + 1);
    for (int i = 1; i <= m; i++) {
        dp[i] = i;
        if (vis[i]) cnt[i] = 1;
    }

    int ans = 1e9;
    int now = m;
    for (int i = m; i >= 1; i--) {
        if (1LL * i * i <= m) {
            for (int j = i * i; j <= m; j += i) {
                if (vis[j]) {
                    cnt[dp[j]]--;
                }
                dp[j] = min(dp[j], dp[j / i]);
                if (vis[j]) {
                    cnt[dp[j]]++;
                }
            }
        }

        while (cnt[now] == 0) now--;

        if (i <= mi) {
            ans = min(ans, now - i);
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
}