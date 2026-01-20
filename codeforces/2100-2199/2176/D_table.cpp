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

    typedef long long ll;
    vector<ll> ans(100);
    ans[0] = 1;
    ans[1] = 1;
    for (int i = 2; i < 100; i++) {
        ans[i] = ans[i - 1] + ans[i - 2];
        debug(i, ans[i]);
        if (ans[i] >= 1e18) {
            break;
        }
    }



}