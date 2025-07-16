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

void yes() {
    cout << "YES\n";
}

void no() {
    cout << "NO\n";
}

void solve() {
    int l1, b1, l2, b2, l3, b3;
    cin >> l1 >> b1 >> l2 >> b2 >> l3 >> b3;

    auto check1 = [&](int l1, int b1, int l2, int b2) {
        if (l1 == l2) {
            if (l1 == b1 + b2) {
                return true;
            }
        }
        if (b1 == b2) {
            if (b1 == l1 + l2) {
                return true;
            }
        }
        return false;
    };

    if (b2 == b3) {
        if (check1(l1, b1, l2 + l3, b2)) {
            yes();
            return;
        }
    }
    if (l2 == l3) {
        if (check1(l1, b1, l2, b2 + b3)) {
            yes();
            return;
        }
    }
    no();
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