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
    int n, k;
    cin >> n >> k;

    if (n == 1) {
        cout << k << endl;
        return;
    }

    int x = k;
    vector<int> v;
    while (x) {
        v.push_back(x % 2);
        x /= 2;
    }

    int sz = v.size();
    int val = (1 << (sz - 1)) - 1;

    int val2 = k - val;
    cout << val << ' ' << val2 << ' ';
    for (int i = 3; i <= n; i++) {
        cout << 0 << ' ';
    }
    cout << endl;
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