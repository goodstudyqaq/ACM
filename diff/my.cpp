#include <bits/stdc++.h>

#include <limits>

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
    vector<int> a(n + 1);
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        sum[i] += sum[i - 1];
    }

    vector<vector<pii>> V(sum[n] * 2 + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j <= n; j++) {
            V[sum[i - 1] + sum[j]].push_back({i, j});
        }
    }

    vector<vector<pii>> go(n + 1, vector<pii>(n + 1, {-1, -1}));
    for (int i = 0; i <= sum[n] * 2; i++) {
        if (V[i].size() > 1) {
            sort(V[i].begin(), V[i].end());
            int sz = V[i].size();
            for (int j = 0; j < sz - 1; j++) {
                go[V[i][j].first][V[i][j].second] = V[i][j + 1];
            }
        }
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    long long ans = 0;
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (len == 1) {
                dp[l][r] = 0;
            } else if (len == 2) {
                dp[l][r] = (a[l] != a[r]);
            } else {
                dp[l][r] = r - l;

                if (go[l][r] != pii(-1, -1)) {
                    int lnow = go[l][r].first, rnow = go[l][r].second;
                    // debug(l, r, lnow, rnow);
                    dp[l][r] = min(dp[l][r], dp[lnow][rnow] + lnow - l - 1 + r - rnow - 1);
                }
            }
            ans += dp[l][r];
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