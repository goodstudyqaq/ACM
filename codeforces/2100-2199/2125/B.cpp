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
    long long a, b, k;
    cin >> a >> b >> k;

    if (a == b) {
        cout << 1 << '\n';
        return;
    }

    long long g = gcd(a, b);

    long long a2 = a / g;
    long long b2 = b / g;

    if (a2 <= k && b2 <= k) {
        cout << 1 << '\n';
        return;
    }
    cout << 2 << '\n';
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