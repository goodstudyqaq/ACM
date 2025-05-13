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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto check = [&]() {
        int small = 0, big = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] > a[0] && -a[i] > a[0]) {
                big++;
            }
            if (a[i] < a[0] && -a[i] < a[0]) {
                debug(a[i], i);
                small++;
            }
        }

        int flex = n - 1 - small - big;

        int need_small = (n - 1) / 2;

        if (small > need_small) {
            return false;
        } else {
            int need = need_small - small;
            if (flex >= need) {
                return true;
            }
            return false;
        }
    };
    if (check()) {
        cout << "Yes\n";
        return;
    }
    a[0] = -a[0];
    if (check()) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
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