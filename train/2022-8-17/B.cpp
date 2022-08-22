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
    vector c = vector(n + 1, vector(n + 1, 0LL));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] += c[i][j - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            c[i][j] += c[i - 1][j];
        }
    }
    const ll inf = numeric_limits<ll>::max() / 2;
    vector dp = vector(n + 2, vector(n + 2, 0LL));
    vector choose = vector(n + 2, vector(n + 2, -1));

    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = inf;
            for (int k = l; k <= r; k++) {
                ll tmp2 = dp[l][k - 1] + dp[k + 1][r] + c[r][n] - c[l - 1][n] - (c[r][r] - c[l - 1][r]) + c[r][l - 1] - c[l - 1][l - 1];
                if (dp[l][r] > tmp2) {
                    dp[l][r] = tmp2;
                    choose[l][r] = k;
                }
            }
        }
    }
    debug(dp[1][n]);

    vector<int> res(n + 1);
    function<void(int l, int r, int u)> dfs2 = [&](int l, int r, int u) {
        int c = choose[l][r];
        res[c] = u;
        if (c != l) {
            dfs2(l, c - 1, c);
        }
        if (c != r) {
            dfs2(c + 1, r, c);
        }
    };
    int idx = choose[1][n];
    if (idx != 1) {
        dfs2(1, idx - 1, idx);
    }
    if (idx != n) {
        dfs2(idx + 1, n, idx);
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}