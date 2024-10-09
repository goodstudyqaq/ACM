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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int x, y, k;
    cin >> x >> y >> k;

    int x_step = (x + k - 1) / k;
    int y_step = (y + k - 1) / k;

    if (y_step >= x_step) {
        cout << 2 * y_step << endl;
    } else {
        cout << 2 * x_step - 1 << endl;
    }

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