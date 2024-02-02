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
    for (int a = 1; a <= 1000; a++) {
        for (int b = 1; b + a <= 1000; b++) {
            int c = 1000 - a - b;
            if (a * a + b * b == c * c) {
                cout << a * b * c << endl;
            }
        }
    }

}