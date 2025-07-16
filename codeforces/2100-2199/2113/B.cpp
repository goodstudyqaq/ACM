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
    int w, h, a, b;
    int x1, y1, x2, y2;
    cin >> w >> h >> a >> b;
    cin >> x1 >> y1 >> x2 >> y2;

    int diff1 = 0;
    if (x1 < x2) {
        diff1 = x2 - x1 - a;
    } else {
        diff1 = x1 - x2 - a;
    }
    int diff2 = 0;
    if (y1 < y2) {
        diff2 = y2 - y1 - b;
    } else {
        diff2 = y1 - y2 - b;
    }
    debug(diff1, diff2);
    if (diff1 >= 0 && diff2 >= 0) {
        if (diff1 % a == 0 || diff2 % b == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else if (diff1 >= 0) {
        if (diff1 % a == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else {
        if (diff2 % b == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
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