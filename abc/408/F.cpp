#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int N, D, R;
    cin >> N >> D >> R;

    vector<int> h(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
    }

    auto get_go = [&]() {
        vector<int> stk;
        vector<int> pre(N + 1, -1);

        auto work = [&](int val, int idx) {
            debug(idx, stk);
            int sz = stk.size();
            int l = 0, r = sz - 1;
            int ans = -1;
            while (l <= r) {
                int m = l + r >> 1;
                if (idx - stk[m] <= R) {
                    ans = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }

            if (ans == -1) return -1;

            l = ans;
            r = sz - 1;
            ans = -1;
            while (l <= r) {
                int m = l + r >> 1;
                if (val - h[stk[m]] >= D) {
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            if (ans == -1) return -1;
            return stk[ans];
        };

        for (int i = 1; i <= N; i++) {
            int val = h[i];
            while (stk.size() && h[stk.back()] > val) stk.pop_back();

            if (stk.size()) {
                int idx = work(val, i);
                pre[i] = idx;
            }
            stk.push_back(i);
        }
        return pre;
    };

    auto pre = get_go();

    reverse(h.begin() + 1, h.begin() + 1 + N);
    auto suf = get_go();
    reverse(suf.begin() + 1, suf.begin() + 1 + N);

    for (int i = 1; i <= N; i++) {
        if (suf[i] != -1) {
            suf[i] = N - suf[i] + 1;
        }
    }
    debug(pre, suf);

    vector<int> f(N + 1);
    iota(f.begin() + 1, f.begin() + 1 + N, 1);

    sort(f.begin() + 1, f.begin() + 1 + N, [&](int x, int y) {
        return h[x] < h[y];
    });

    vector<int> dp(N + 1);
    int res = 0;
    for (int i = 1; i <= N; i++) {
        int idx = f[i];

        int go1 = pre[idx];

        if (go1 != -1) {
            dp[i] = max(dp[i], dp[go1] + 1);
        }

        int go2 = suf[idx];
        if (go2 != -1) {
            dp[i] = max(dp[i], dp[go2] + 1);
        }
        res = max(res, dp[i]);
    }
    cout << res << '\n';
}