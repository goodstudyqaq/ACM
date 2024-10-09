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
    long long b, c, d;

    cin >> b >> c >> d;

    long long ans = 0;
    for (int i = 59; i >= 0; i--) {
        int _b = (b >> i) & 1;
        int _c = (c >> i) & 1;
        int _d = (d >> i) & 1;

        bool ok = false;
        for (int j = 0; j < 2; j++) {
            if ((j | _b) - (j & _c) == _d) {
                ok = true;
                if (j == 1) {
                    ans += 1LL << i;
                }
                break;
            }
        }
        if (!ok) {
            cout << -1 << endl;
            return;
        }
    }
    cout << ans << endl;


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