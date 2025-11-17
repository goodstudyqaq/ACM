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
    int n, a, b;
    cin >> n >> a >> b;

    if (a <= b) {
        if (n % 2 != b % 2) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    } else {
        if (n % 2 != a % 2 || n % 2 != b % 2) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
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