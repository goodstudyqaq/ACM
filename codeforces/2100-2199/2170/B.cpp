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
    ll sum = 0;
    ll can_remove = 0;
    int big_zero = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        can_remove += a[i] - 1;
        if (a[i] > 0) big_zero++;
    }
    sort(a.begin(), a.end());
    if (can_remove >= n - 1) {
        cout << big_zero << '\n';
    } else {
        can_remove = n - 1;
        for (int i = 0; i < n && can_remove; i++) {
            if (a[i] > 1) {
                ll tmp = min(can_remove, 1LL * a[i] - 1);
                can_remove -= tmp;
                a[i] -= tmp;
            }
        }

        int have = 0;
        for (int i = 0; i < n; i++) {
            if (a[i]) have++;
        }
        if (can_remove) {
            have -= can_remove;
        }
        cout << have << '\n';
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