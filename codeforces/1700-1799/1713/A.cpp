#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int mx_x = 0, mi_x = 0;
    int mx_y = 0, mi_y = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mx_x = max(mx_x, x);
        mi_x = min(mi_x, x);
        mx_y = max(mx_y, y);
        mi_y = min(mi_y, y);
    }
    debug(mx_x, mi_x, mx_y, mi_y);
    int ans = (mx_x + abs(mi_x) + mx_y + abs(mi_y)) * 2;
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
}