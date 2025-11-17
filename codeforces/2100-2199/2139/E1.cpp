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
    cin >> n >> k;
    vector<vector<int>> V(n);

    vector<int> dep(n);
    dep[0] = 0;
    vector<int> cnt(n), sumcnt(n);
    cnt[0] = 1;

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        dep[i] = dep[p] + 1;
        cnt[dep[i]]++;
        V[p].push_back(i);
    }

    int mi = n;
    for (int i = 0; i < n; i++) {
        if (V[i].size() == 0) {
            mi = min(mi, dep[i]);
        }
    }
    for (int i = 0; i <= mi; i++) {
        sumcnt[i] = cnt[i];
        if (i) {
            sumcnt[i] += sumcnt[i - 1];
        }
    }
    debug(mi);

    // 只考虑 [0, mi]
    vector<int> dp(k + 1);
    dp[0] = 1;

    for (int i = 0; i <= mi; i++) {
        vector<int> ndp(k + 1);
        int sz = cnt[i];
        bool ok = false;
        for (int j = 0; j <= k; j++) {
            if (dp[j]) {
                if (j + sz <= k) {
                    ndp[j + sz] = 1;
                    ok = true;
                }
                int other;
                if (i == 0) {
                    other = 0;
                } else {
                    other = (sumcnt[i - 1] - j);
                }

                if (other + sz <= n - k) {
                    ndp[j] = 1;
                    ok = true;
                }
            }
        }
        dp = ndp;
        if (!ok) {
            cout << i << '\n';
            return;
        }
        debug(i, dp);
    }
    cout << mi + 1 << '\n';
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