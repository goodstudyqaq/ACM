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
    string s;
    cin >> n >> s;

    vector dp = vector(n, vector(n, -1));

    function<int(int, int)> dfs = [&](int l, int r) -> int {
        if (l > r) return 0;
        if (l == r) return 1;
        if (dp[l][r] != -1) return dp[l][r];
        int res = 1 + dfs(l + 1, r);

        for (int i = l + 1; i <= r; i++) {
            if (s[i] == s[l]) {
                res = min(res, dfs(l + 1, i - 1) + dfs(i, r));
            }
        }
        return dp[l][r] = res;
    };

    cout << dfs(0, n - 1) << endl;

    return 0;
}