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
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if (a == b) {
        cout << 0 << endl;
        return;
    }

    if (a < b) {
        if (x <= y) {
            cout << 1LL * x * (b - a) << endl;
            return;
        } else {
            int times = b - a;

            int even_times, odd_times;
            even_times = odd_times = times / 2;
            if (times % 2) {
                if (a % 2) {
                    odd_times++;
                } else {
                    even_times++;
                }
            }
            cout << even_times * y + odd_times * x << endl;
            return;
        }
    } else {
        if (a == b + 1 && a % 2) {
            cout << y << endl;
            return;
        } else {
            cout << -1 << endl;
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