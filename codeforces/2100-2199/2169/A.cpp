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
    int n, a;
    cin >> n >> a;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int idx = lower_bound(v.begin(), v.end(), a) - v.begin();
    int idx2 = upper_bound(v.begin(), v.end(), a - 1) - v.begin();
    int b_have = idx2;
    int idx3 = lower_bound(v.begin(), v.end(), a + 1) - v.begin();
    int b_have2 = n - idx3;
    debug(b_have, b_have2);
    if (b_have < b_have2) {
        cout << a + 1 << '\n';
    } else {
        cout << a - 1 << '\n';
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