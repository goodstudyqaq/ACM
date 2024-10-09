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
    string a;
    cin >> a;
    if (a.size() < 3) {
        cout << "NO" << endl;
        return;
    }

    if (a[0] == '1' && a[1] == '0') {
        if (a[2] == '0') {
            cout << "NO" << endl;
            return;
        }
        if (a.size() == 3 && a[2] == '1') {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    } else {
        cout << "NO" << endl;
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