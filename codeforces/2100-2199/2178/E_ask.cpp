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
// #ifdef LOCAL
//     freopen("./data.in", "r", stdin);
// #endif

    vector<int> a = {1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2};
    vector<int> sum(a.size());
    for (int i = 0; i < a.size(); i++) {
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }
    debug(sum);

    while (true) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        debug(l, r);
        int ans = sum[r];
        if (l) ans -= sum[l - 1];
        debug(ans);
    }
}