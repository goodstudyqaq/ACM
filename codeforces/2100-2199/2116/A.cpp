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

    auto out = [&](int x) {
        if (x == 1) {
            cout << "Gellyfish\n";
        } else {
            cout << "Flower\n";
        }
    };

    if (a >= b) {
        if (c >= d) {
            out(1);
            return;
        } else {
            if (c >= b) {
                out(1);
                return;
            } else {
                out(0);
                return;
            }
        }
    } else {
        if (c < d) {
            out(0);
            return;
        } else {
            if (d > a) {
                out(0);
                return;
            } else {
                out(1);
                return;
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