#include <bits/stdc++.h>

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

    long long a_i, a_o, a_t, a_j, a_l, a_s, a_z;
    cin >> a_i >> a_o >> a_t >> a_j >> a_l >> a_s >> a_z;

    long long ans = 0;
    for (int i = 0; i < 5; i++) {
        if (i > a_i || i > a_j || i > a_l) break;

        long long left_a_i = a_i - i;

        long long tmp1 = i * 3;
        long long tmp2 = (left_a_i / 2) * 2;
        long long tmp3 = (a_j - i) / 2 * 2;
        long long tmp4 = (a_l - i) / 2 * 2;
        ans = max(ans, tmp1 + tmp2 + tmp3 + tmp4);
    }
    cout << ans + a_o << endl;
}