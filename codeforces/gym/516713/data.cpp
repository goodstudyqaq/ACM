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
    freopen("./data.in", "w", stdout);
#endif
    int n = 1365;
    cout << n << endl;
    int dep = 30;
    int times = 0;
    for (int i = 1; i <= dep - 1; i++) {
        times++;
        cout << i << ' ' << i + 1 << endl;
    }

    int need = 60;
    int new_node = 31;
    for (int i = 1; i <= 30; i++) {
        int left = 30 - i + 1;

        int right = need - left;

        for (int j = 1; j <= right; j++) {
            if (j == 1) {
                times++;
                cout << i << ' ' << new_node << endl;
            } else {
                times++;
                cout << new_node - 1 << ' ' << new_node << endl;
            }
            new_node++;
        }
    }
    debug(new_node, times);
}