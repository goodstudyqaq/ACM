#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int a, b;
    cin >> a >> b;

    if (a > b) swap(a, b);
    int t1 = a % 2;
    int t2 = b % 2;
    if (t1 != t2) {
        if (a * 2 == b) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    } else {
        if (t1)
            cout << "No" << endl;
        else
            cout << "Yes" << endl;
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