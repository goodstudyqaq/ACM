#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for (int i = 2; i <= N; i++) {
        cin >> A[i];
    }
    vector<vector<int>> V(N + 1);
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    vector<int> dp(N + 1);
    vector<int> a(N + 1);

    function<void(int, int)> dfs = [&](int u, int pre) {
        dp[u] = a[u];
        int sum = 0;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
            sum += dp[v];
        }
        sum = max(sum - 1, 0);
        dp[u] += sum;
    };

    auto check = [&](int val) {
        for (int i = 2; i <= N; i++) {
            a[i] = (A[i] >= val);
        }
        dfs(1, 0);
        // debug(dp);
        return dp[1] > 0;
    };

    int l = 1, r = 1e9;
    int ans = 0;
    // l = r = 5;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}