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
    int n;
    string s;
    cin >> n >> s;
    s = " " + s;
    int LIMIT = 1 << n;
    vector<int> dp(LIMIT);

    const int mod = 998244353;
    function<string(int)> dfs = [&](int u) -> string {
        if (2 * u >= LIMIT) {
            dp[u] = 1;
            return string("") + s[u];
        }

        string a = dfs(2 * u);
        string b = dfs(2 * u + 1);
        string c = string("") + s[u];

        dp[u] = 1LL * dp[2 * u] * dp[2 * u + 1] % mod;
        if (a != b) {
            dp[u] = 1LL * dp[u] * 2 % mod;
        }
        if (a > b) swap(a, b);
        return c + a + b;
    };
    dfs(1);
    cout << dp[1] << endl;
    return 0;
}