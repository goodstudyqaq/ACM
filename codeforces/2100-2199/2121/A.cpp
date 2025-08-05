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
    vector<int> x(n);
    int l = s, r = s;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        l = min(l, x[i]);
        r = max(r, x[i]);
    }

    int mi = min(abs(s - l) + abs(l - r), abs(s - r) + abs(l - r));
    cout << mi << '\n';
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