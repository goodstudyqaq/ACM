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

    int n, s;
    cin >> n >> s;
    int now = 0;
    bool ok = false;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a - now > s) {
            ok = true;
        }
        now = a;
    }
    if (ok) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
    }
}