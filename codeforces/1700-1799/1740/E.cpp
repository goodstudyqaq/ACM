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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> p(n + 1);
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        V[p[i]].push_back(i);
    }

    vector<vector<int>> dp = vector(n + 1, vector(2, 0));

    function<void(int)> dfs = [&](int u) {
        dp[u][1] = 1;
        for (auto v : V[u]) {
            dfs(v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] = max(dp[u][1], dp[v][1] + 1);
        }
    };

    dfs(1);
    cout << max(dp[1][0], dp[1][1]) << endl;
    return 0;
}