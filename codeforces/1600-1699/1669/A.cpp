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
        int rating;
        cin >> rating;
        cout << "Division ";
        if (rating <= 1399) {
            cout << 4 << endl;
        } else if (rating <= 1599) {
            cout << 3 << endl;
        } else if (rating <= 1899) {
            cout << 2 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    return 0;
}