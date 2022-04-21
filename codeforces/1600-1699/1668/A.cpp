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
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        if (n == 1 && m == 1) {
            cout << 0 << endl;
            continue;
        }
        if (n > m) {
            swap(n, m);
        }
        if (n == 1) {
            if (m > 2) {
                cout << -1 << endl;
            } else {
                cout << 1 << endl;
            }
            continue;
        }

        int res = n + n - 2;
        int tmp = (m - n);
        res += (m - n) * 2;
        if (tmp % 2) res--;
        cout << res << endl;
    }
    return 0;
}