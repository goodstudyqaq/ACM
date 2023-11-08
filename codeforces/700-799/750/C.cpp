#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int now = 0;

    int l = -1e9, r = 1e9;
    for (int i = 0; i < n; i++) {
        int val, c;
        cin >> val >> c;
        if (c == 1) {
            // div1
            // x + now >= 1900
            // x >= 1900 - now
            int tmp = 1900 - now;
            l = max(l, tmp);
        } else if (c == 2) {
            // div2
            // x + now <= 1899
            // x <= 1899 - now
            int tmp = 1899 - now;
            r = min(r, tmp);
        }
        now += val;
    }

    if (l > r) {
        cout << "Impossible" << endl;
    } else if (r == 1e9) {
        cout << "Infinity" << endl;
    } else {
        cout << r + now << endl;
    }

}