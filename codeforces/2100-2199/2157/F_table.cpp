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

    int cost = 1e6;
    int n = 25e4;
    // long long mx_left = 0;
    // for (int p = 0; p <= n; p++) {

    //     long long val = 1LL * (n - p) * (n - p - 1) / 2;
    //     if (val > cost) continue;
    //     long long left = cost - val;
    //     left /= p;
    //     mx_left = max(mx_left, left);
    //     debug(p, left);
    //     if (left >= 1000) {
    //         debug(p, left - 1000);
    //     }

    // }
    // debug(mx_left);

    // for (int l = 0; l * l <= cost; l++) {
    //     long long val = l * l;
    //     long long left = cost - val;
    //     long long tmp = 1LL * (1 + n - (l + 1)) * (n - (l + 1)) / 2 + 1000LL * (n - (l + 1));
    //     debug(l, tmp, left);
    //     if (tmp <= left) debug(l);
    // }



}