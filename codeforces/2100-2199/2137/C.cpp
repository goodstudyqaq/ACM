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
    long long a, b;
    cin >> a >> b;
    if (a % 2 == 0 && b % 2) {
        cout << -1 << '\n';
        return;
    }

    if (a % 2 == 0) {
        // b % 2 = 0
        long long tmp = b / 2;
        a *= tmp;
        b = 2;
        cout << a + b << '\n';
        return;
    } else {
        if (b % 2) {
            a *= b;
            b = 1;
            cout << a + b << '\n';
        } else {
            long long tmp = b / 2;
            if (tmp % 2) {
                cout << -1 << '\n';
            } else {
                a *= tmp;
                b = 2;
                cout << a + b << '\n';
            }
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