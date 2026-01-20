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
    int n;
    cin >> n;

    int x = n / 2;
    int y = n % 2;

    if (n <= 3) {
        cout << n << '\n';
        return;
    }


    if (x % 2 == 0) {
        if (y == 0) {
            cout << 0 << '\n';
        } else {
            cout << 1 << '\n';
        }
    } else {
        if (y == 1) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
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