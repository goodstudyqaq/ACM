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
    int n, s;
    cin >> n >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int dx, dy, x, y;
        cin >> dx >> dy >> x >> y;

        if (x == y) {
            if (dx * dy == 1) {
                ans++;
            }
        }

        if (x + y == s) {
            if (dx * dy == -1) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
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