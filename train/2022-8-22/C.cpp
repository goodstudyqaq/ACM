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
typedef array<int, 3> a3;

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
    vector a = vector(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<a3>> V(n + 1);
    for (int i = 1; i <= m; i++) {
        int e, t, p;
        cin >> e >> t >> p;
        V[e].push_back({t, p, i});
    }

    ll now_ct = 0;
    const ll inf = numeric_limits<ll>::max() / 2;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int sz = V[i].size();
        vector dp = vector(sz + 1, vector(200, inf));
        vector choose = vector(sz + 1, vector(200, -1));
        dp[0][0] = 0;
        // debug(i);
        for (int j = 1; j <= sz; j++) {
            auto [t, p, idx] = V[i][j - 1];
            // debug(j, t, p, idx);
            // 花 t 时间 涨 p
            for (int k = 199; k >= 0; k--) {
                dp[j][k] = dp[j - 1][k];
                choose[j][k] = choose[j - 1][k];
                if (k >= p) {
                    if (dp[j][k] > dp[j - 1][k - p] + t) {
                        dp[j][k] = dp[j - 1][k - p] + t;
                        choose[j][k] = j;
                    }
                }
            }
        }

        int per = 100;
        for (int i = 101; i < 200; i++) {
            if (dp[sz][per] > dp[sz][i]) {
                per = i;
            }
        }
        ll ct = dp[sz][per];
        now_ct += ct;
        if (now_ct > a[i]) {
            cout << -1 << endl;
            return;
        }
        int now = per;
        int now_idx = sz;
        while (now) {
            int idx = choose[now_idx][now];
            ans.push_back(V[i][idx - 1][2]);
            int p = V[i][idx - 1][1];
            now -= p;
            now_idx = idx - 1;
        }
    }

    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << endl;
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