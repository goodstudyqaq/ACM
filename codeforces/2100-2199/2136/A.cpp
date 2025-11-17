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
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int mi = min(a, b);
    int mx = max(a, b);

    if (mi * 2 < mx - 2) {
        cout << "NO\n";
        return;
    }

    c -= a;
    d -= b;
    mi = min(c, d);
    mx = max(c, d);
    if (mi * 2 < mx - 2) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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