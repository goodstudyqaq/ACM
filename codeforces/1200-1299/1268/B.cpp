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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    ll x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (i % 2) {
            x += (a + 1) / 2;
            y += a / 2;
        } else {
            x += a / 2;
            y += (a + 1) / 2;
        }
    }
    cout << min(x, y) << endl;
    return 0;
}