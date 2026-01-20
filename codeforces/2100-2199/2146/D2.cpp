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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    auto work1 = [&]() {
        vector<int> ans(n);
        auto work = [&](int now_l, int now_r, int b) {
            if (now_l == now_r) return;
            int n = now_r - now_l + 1;

            int mask = (1 << b) - 1;

            map<int, int> M;
            for (int i = now_l; i <= now_r; i++) {
                int val = (ans[i - l] & mask);
                M[val] = ans[i - l];
            }
            // debug(M);

            for (int i = now_l; i <= now_r; i++) {
                int need = (mask ^ (i & mask));
                ans[i - l] = M[need];
            }
        };
        for (int i = 0; i < n; i++) {
            ans[i] = l + i;
        }

        int now = l;
        for (int i = 29; i >= 0; i--) {
            if ((n >> i) & 1) {
                int len = 1 << i;
                // debug(len);
                for (int j = now; j + len <= r; j++) {
                    swap(ans[j - l], ans[j + len - l]);
                }

                // debug(ans);

                int go = now + (1 << i) - 1;
                work(now, go, i);
                now = go + 1;
            }
        }
        return ans;
    };

    auto ans1 = work1();

    ll res1 = 0;
    for (int i = l; i <= r; i++) {
        res1 += (i | ans1[i - l]);
    }

    cout << res1 << '\n';
    // for (int i = 0; i < n; i++) {
    //     cout << ans1[i] << ' ';
    // }
    // cout << '\n';
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