#include <bits/stdc++.h>

#include <algorithm>

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
    int n, m;
    cin >> n >> m;
    vector<int> from(n), to(n);

    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        vector<int> cnt(l + 2);
        for (int j = 0; j < l; j++) {
            int a;
            cin >> a;
            if (a <= l + 1) cnt[a]++;
        }

        int now = 0;
        while (cnt[now]) now++;
        from[i] = now;
        now++;
        while (cnt[now]) now++;
        to[i] = now;
    }

    int mx = *max_element(to.begin(), to.end());
    debug(from, to, mx);
    vector<vector<int>> V(mx + 1);
    for (int i = 0; i < n; i++) {
        V[from[i]].push_back(to[i]);
    }

    vector<int> dp(mx + 1);
    int super_mx = 0;
    for (int i = mx; i >= 0; i--) {
        dp[i] = i;
        for (auto it : V[i]) {
            dp[i] = max(dp[i], dp[it]);
        }
        if (V[i].size() > 0) super_mx = max(super_mx, i);
        if (V[i].size() > 1) super_mx = max(super_mx, dp[i]);
    }
    debug(super_mx, dp);

    long long ans = 0;
    for (int i = 0; i <= min(super_mx, m); i++) {
        ans += max(super_mx, dp[i]);
    }

    if (m > super_mx) {
        ans += 1LL * (super_mx + 1 + m) * (m - super_mx) / 2;
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