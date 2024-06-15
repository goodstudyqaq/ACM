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
    int x, y;
    cin >> x >> y;
    debug(x, y, x ^ y);
    int res = x ^ y;
    vector<int> v;
    while (res) {
        v.push_back(res % 2);
        res /= 2;
    }

    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) {
            cout << (1 << i) << endl;
            return;
        }
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