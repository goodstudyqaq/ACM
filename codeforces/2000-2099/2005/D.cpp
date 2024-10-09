#include <bits/stdc++.h>

#include "./structure/others/sparse-table.hpp"

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

    using F = function<int(int, int)>;
    F f = [&](int a, int b) {
        return gcd(a, b);
    };

    auto st1 = SparseTable<int, F>(a, f);
    auto st2 = SparseTable<int, F>(b, f);

    int mx = -1;
    long long ans = 0;

    auto get_mid_change = [&](int idx, int r, SparseTable<int, F> &st) -> int {
        int val = st.fold(idx, r + 1);

        int l2 = r, r2 = n - 1;
        int ans = -1;
        while (l2 <= r2) {
            int m = l2 + r2 >> 1;
            if (st.fold(idx, m + 1) == val) {
                ans = m;
                l2 = m + 1;
            } else {
                r2 = m - 1;
            }
        }
        return ans;
    };

    auto get_right_change = [&](int idx, SparseTable<int, F> &st) -> int {
        int val = st.fold(idx, n);
        int l2 = idx, r2 = n - 1;
        int ans = -1;
        while (l2 <= r2) {
            int m = l2 + r2 >> 1;
            if (st.fold(m, n) == val) {
                ans = m;
                l2 = m + 1;
            } else {
                r2 = m - 1;
            }
        }
        return ans;
    };

    for (int l = 0; l < n; l++) {
        int lefta = (l == 0 ? 0 : st1.fold(0, l));
        int leftb = (l == 0 ? 0 : st2.fold(0, l));

        int now = l;
        debug(l);
        while (now < n) {
            // debug(now);
            int mida = st2.fold(l, now + 1);
            int midb = st1.fold(l, now + 1);

            int righta = now + 1 < n ? st1.fold(now + 1, n) : 0;
            int rightb = now + 1 < n ? st2.fold(now + 1, n) : 0;

            int mida_change = get_mid_change(l, now, st2);
            int midb_change = get_mid_change(l, now, st1);

            int righta_change = now + 1 < n ? get_right_change(now + 1, st1) : now;
            int rightb_change = now + 1 < n ? get_right_change(now + 1, st2) : now;

            int go = min({mida_change, midb_change, righta_change, rightb_change});

            int tmp = gcd(gcd(lefta, mida), righta);
            int tmp2 = gcd(gcd(leftb, midb), rightb);
            long long number = go - now + 1;
            if (mx < tmp + tmp2) {
                mx = tmp + tmp2;
                ans = number;
            } else if (mx == tmp + tmp2) {
                ans += number;  
            }
            now = go + 1;
        }
    }
    cout << mx << ' ' << ans << endl;
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