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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int s, k, m;
    cin >> s >> k >> m;

    int x = m % k;
    int y = m / k;

    if (s <= k) {
        cout << max(0, s - x) << '\n';
    } else {
        if (y % 2) {
            cout << max(0, k - x) << '\n';
        } else {
            cout << max(0, s - x) << '\n';
        }
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