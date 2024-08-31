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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> no_same(n, n);
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == a[i + 1]) {
            no_same[i] = no_same[i + 1];
        } else {
            no_same[i] = i + 1;
        }
    }
    vector<int> b(n);
    for (int i = 0; i < n - 1; i++) {
        b[i] = abs(a[i] - a[i + 1]);
    }

    auto f = [&](int a, int b) -> int {
        return gcd(a, b);
    };
    using F = function<int(int, int)>;

    auto st = SparseTable<int, F>(b, [&](int a, int b) {
        return gcd(a, b);
    });

    long long ans = 1;
    for (int i = 0; i < n - 1; i++) {
        int l = no_same[i], r = n - 1;
        ans += l - i;
        int res = -1;
        while (l <= r) {
            // debug(l, r);
            int m = l + r >> 1;
            // [i, m - 1]
            int val = st.fold(i, m);
            while (val % 2 == 0) val /= 2;
            if (val == 1) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        // debug(i, no_same[i], res);
        if (res != -1) {
            ans += n - res;
        }
    }
    cout << ans << endl;
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