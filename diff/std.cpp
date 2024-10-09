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

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int lefta = i == 0 ? 0 : st1.fold(0, i);
            int leftb = i == 0 ? 0 : st2.fold(0, i);
            int mida = st2.fold(i, j + 1);
            int midb = st1.fold(i, j + 1);
            int righta = j == n - 1 ? 0 : st1.fold(j + 1, n);
            int rightb = j == n - 1 ? 0 : st2.fold(j + 1, n);

            int tmp = gcd(gcd(lefta, mida), righta);
            int tmp2 = gcd(gcd(leftb, midb), rightb);

            if (mx < tmp + tmp2) {
                mx = tmp + tmp2;
                debug(i, j, tmp, tmp2);
                ans = 1;
            } else if (mx == tmp + tmp2) {
                debug(i, j);
                ans++;
            }
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