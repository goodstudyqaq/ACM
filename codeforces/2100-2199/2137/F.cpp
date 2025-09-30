#include <bits/stdc++.h>

#include "./structure/others/binary-indexed-tree.hpp"

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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<int> stk;
    vector<int> nxt(n, n);
    for (int i = n - 1; i >= 0; i--) {
        while (stk.size() && a[stk.back()] <= a[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            nxt[i] = stk.back();
        }
        stk.push_back(i);
    }

    vector<long long> dp2(n), dp3(n);
    BIT<int> bit(2 * n + 1);
    BIT<int> bit2(2 * n + 1);

    vector<vector<array<int, 3>>> query(n);
    for (int i = 0; i < n; i++) {
        int l = i, r = nxt[i];
        query[r - 1].push_back({a[i], i, 1});
        query[l].push_back({a[i], i, -1});
    }

    for (int i = 0; i < n; i++) {
        bit.add(b[i], i);
        bit2.add(b[i], 1);

        for (auto it : query[i]) {
            int val = it[0];
            int idx = it[1];
            int flag = it[2];

            if (flag > 0) {
                dp2[idx] += bit.query(val);
                dp3[idx] += bit2.query(val);
            } else {
                dp2[idx] -= bit.query(val);
                dp3[idx] -= bit2.query(val);
            }
        }
    }

    vector<long long> dp(n + 2);
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int l = i, r = nxt[i];
        // [l, r)
        long long res = 1LL * r * dp3[i] - dp2[i];
        int len = dp3[i];
        // for (int j = l + 1; j <= r - 1; j++) {
        //     if (b[j] <= a[i]) {
        //         len++;
        //         res += r - j;
        //     }
        // }
        // debug(i, res, len);
        // [l + 1, r - 1] b 中不能超过 a[i] 的个数
        if (a[i] == b[i]) {
            len++;
            res += r - i;
        }
        dp[i] = res;
        dp[i] += dp[r];
        int len2 = n - r;
        dp[i] += 1LL * len2 * len;
        // debug(i, dp[i], r);
        ans += dp[i];
    }
    cout << ans << '\n';
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