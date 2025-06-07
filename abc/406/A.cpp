#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int A, B, C, D;
    cin >> A >> B >> C >> D;
    if (A < C) {
        cout << "No\n";
        return 0;
    } else if (A > C) {
        cout << "Yes\n";
        return 0;
    } else {
        if (B > D) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}