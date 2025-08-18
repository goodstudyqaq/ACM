#include <bits/stdc++.h>

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
    int n, k;
    string s;
    int q;
    cin >> n >> k >> s >> q;

    vector<vector<int>> nxt(n, vector<int>(k + 1, n));
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        if (i != n - 1) {
            for (int j = 0; j < k; j++) {
                nxt[i][j] = nxt[i + 1][j];
            }
        }
        nxt[i][s[i] - 'a'] = i;
        nxt[i][k] = nxt[i][0];

        for (int j = 1; j < k; j++) {
            nxt[i][k] = max(nxt[i][k], nxt[i][j]);
        }
        if (nxt[i][k] == n) {
            dp[i] = 0;
        } else {
            dp[i] = dp[nxt[i][k] + 1] + 1;
        }
    }
    debug(nxt);
    while (q--) {
        string t;
        cin >> t;

        int m = t.size();

        int now = 0;
        bool flag = true;
        for (int i = 0; i < m; i++) {
            if (now == n) {
                flag = false;
                break;
            }
            if (nxt[now][t[i] - 'a'] == n) {
                flag = false;
                break;
            }
            now = nxt[now][t[i] - 'a'] + 1;
        }
        if (!flag) {
            cout << 0 << '\n';
            continue;
        }

        int ans = dp[now];
        cout << ans + 1 << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}