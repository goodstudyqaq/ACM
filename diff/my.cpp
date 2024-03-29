#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

    int mx = 0;
    for (int k = 1; k <= 1000; k++) {
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            if (i * i % k == 0) {
                cnt++;
            }
        }
        mx = max(mx, cnt);
    }
    debug(mx);
}