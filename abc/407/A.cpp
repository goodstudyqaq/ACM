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

    int a, b;
    cin >> a >> b;
    int ans = a / b;
    int ans2 = ans + 1;
    int d1 = abs(a - ans * b);
    int d2 = abs(a - ans2 * b);
    if (d1 <= d2) {
        cout << ans << '\n';
    } else {
        cout << ans2 << '\n';
    }
}