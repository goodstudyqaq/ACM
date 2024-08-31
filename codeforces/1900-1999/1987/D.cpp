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
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }
    vector<int> V;
    // V.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (cnt[i]) {
            V.push_back(cnt[i]);
        }
    }
    int sz = V.size();
    debug(V);
    vector<vector<int>> dp(sz + 1, vector<int>(sz + 1, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= sz; i++) {
        for (int j = 0; j <= i; j++) {
            if (dp[i - 1][j] >= 0) {
                dp[i][j] = dp[i - 1][j] + 1;
            }
            if (j - 1 >= 0) {
                int tmp = dp[i - 1][j - 1];
                if (tmp >= V[i - 1]) {
                    dp[i][j] = max(dp[i][j], tmp - V[i - 1]);
                }
            }
            // debug(i, j, dp[i][j]);
        }
    }

    for (int i = sz; i >= 0; i--) {
        if (dp[sz][i] >= 0) {
            cout << sz - i << endl;
            return;
        }
    }
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