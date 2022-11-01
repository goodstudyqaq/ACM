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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        V[p].push_back(i);
    }

    vector<int> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    map<pii, ll> M;

    const ll inf = numeric_limits<ll>::max() / 2;

    vector<ll> dp(n + 1), ndp(n + 1);

    function<ll(int, int)> dfs = [&](int u, int k) -> ll {
        if (M.count({u, k})) return M[{u, k}];

        int sz = V[u].size();
        if (sz == 0) {
            return 1LL * k * s[u];
        }
        int nxt_k = k / sz;
        int num = k % sz;  // 有 num 个孩子多 1

        for (int i = 0; i <= num; i++) dp[i] = -inf;
        dp[0] = 1LL * k * s[u];

        for (int i = 0; i < sz; i++) {
            int v = V[u][i];
            ll x = dfs(v, nxt_k);
            ll y = num > 0 ? dfs(v, nxt_k + 1) : 0;

            for (int j = 0; j <= min(i + 1, num); j++) ndp[j] = -inf;

            for (int j = 0; j <= min(i + 1, num); j++) {
                ndp[j] = max(ndp[j], dp[j] + x);
                if (j > 0) {
                    ndp[j] = max(ndp[j], dp[j - 1] + y);
                }
            }
            dp = ndp;
            if (u == 1) {
                debug(dp);
            }
        }
        debug(u, k, dp[num]);
        return M[{u, k}] = dp[num];
    };
    cout << dfs(1, k) << endl;
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