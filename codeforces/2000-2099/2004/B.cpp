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
    int l, r;
    int L, R;
    cin >> l >> r >> L >> R;

    if (l > L) {
        swap(l, L);
        swap(r, R);
    }

    if (L <= r) {
        int res = 0;
        if (l != L) {
            res++;
        }
        res += min(R, r) - L;
        if (R != r) {
            res++;
        }
        cout << res << endl;

    } else {
        cout << 1 << endl;
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