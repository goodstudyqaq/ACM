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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    vector<long long> dp(n, 0);
    const long long inf = numeric_limits<long long>::max() / 2;
    // dp[u] u 子树非空下的最大值
    long long ans = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        vector<long long> tmp;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            tmp.push_back(dp[v]);
        }
        int has_father = (pre != -1);
        dp[u] = a[u];
        ans = max(ans, a[u]);
        sort(tmp.rbegin(), tmp.rend());
        long long sum = 0;
        for (int i = 0; i < tmp.size(); i++) {
            sum += tmp[i];
            int cnt = i + 1;
            if (cnt + has_father == 2) {
                dp[u] = max(dp[u], sum);
            } else {
                dp[u] = max(dp[u], sum + a[u]);
            }
            if (cnt == 2) {
                ans = max(ans, sum);
            } else {
                ans = max(ans, sum + a[u]);
            }
        }
    };
    dfs(0, -1);
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