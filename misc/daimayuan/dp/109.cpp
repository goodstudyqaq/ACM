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
const int maxn = 1e6 + 5;
vector<int> V[maxn];
int dp[maxn][2];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        V[i].clear();
        dp[i][0] = dp[i][1] = 0;
    }
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        V[f].push_back(i);
    }
    const int inf = numeric_limits<int>::max() / 2;
    function<void(int, int)> dfs = [&](int u, int d) {
        if (V[u].size() == 0) {
            dp[u][0] = 0;
            dp[u][1] = d;
            return;
        }
        int tmp0 = 0, tmp1 = inf;
        for (auto v : V[u]) {
            dfs(v, d + 1);
            tmp1 = min({tmp0 + dp[v][1], tmp1 + dp[v][0] + 2, tmp1 + dp[v][1]});
            tmp0 += dp[v][0] + 2;
        }
        dp[u][0] = tmp0;
        dp[u][1] = tmp1;
    };
    dfs(1, 0);
    cout << min(dp[1][0], dp[1][1]) << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}