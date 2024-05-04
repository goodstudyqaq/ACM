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
    int p;
    cin >> p;
    int limit = 800;

    vector<int> C(limit + 1);
    for (int i = 2; i <= limit; i++) {
        C[i] = i * (i - 1) / 2;
        // debug(i, C[i]);
    }

    const int inf = 1e9;
    vector<int> dp(p + 1, inf);
    vector<int> last(p + 1, 0);
    dp[0] = 0;

    for (int i = 1; i <= p; i++) {
        for (int j = 2; j <= limit && C[j] <= i; j++) {
            if (dp[i] > dp[i - C[j]] + j) {
                dp[i] = dp[i - C[j]] + j;
                last[i] = j;
            }
        }
        // debug(i, dp[i], last[i]);
    }

    int now = p;
    vector<int> V;
    while (now != 0) {
        int lst = last[now];
        V.push_back(lst);
        now -= C[lst];
    }

    long long ans = 0;
    int all = dp[p];
    debug(V);
    for (auto it : V) {
        ans += 1LL * it * (all - it);
    }
    ans /= 2;
    cout << all << ' ' << ans << endl;
    return 0;
}