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
        int n, r, b;
        cin >> n >> r >> b;

        int tmp = r / (b + 1);
        int tmp2 = r % (b + 1);

        int tmp3 = b - r % (b + 1);
        for (int i = 0; i < tmp3; i++) {
            for (int j = 0; j < tmp; j++) {
                r--;
                cout << 'R';
            }
            if (b) {
                cout << 'B';
                b--;
            }
        }
        for (int i = 0; i < tmp2; i++) {
            for (int j = 0; j <= tmp; j++) {
                r--;
                cout << 'R';
            }
            if (b) {
                cout << 'B';
                b--;
            }
        }
        while (r) {
            cout << 'R';
            r--;
        }

        cout << endl;
    }
    return 0;
}