#include <bits/stdc++.h>

#include <cassert>

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
    int x, y;
    cin >> x >> y;
    if (x == y) {
        cout << -1 << '\n';
        return;
    }

    int mx = max(x, y);

    int ans;
    for (int i = 30; i >= 0; i--) {
        if ((mx >> i) & 1) {
            int val = 1LL << (i + 1);
            ans = val - mx;
            break;
        }
    }

    assert((x + ans) + (y + ans) == ((x + ans) ^ (y + ans)));

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