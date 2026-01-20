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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        ans[i] = i;
    }

    const int LIMIT = 18;
    for (int i = 0; i < LIMIT; i++) {
        int len = 1 << i;
        int len2 = len + len;
        // debug(len, len2);
        for (int j = 0; j < n; j += len2) {
            for (int k = 0; k < len; k++) {
                int idx1 = j + k;
                int idx2 = idx1 + len;
                if (idx1 < n && idx2 < n) {
                    swap(ans[idx1], ans[idx2]);
                } else {
                    break;
                }
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < n; i++) {
        // cout << ans[i] << ' ';
        res += (i | ans[i]);
    }
    cout << res << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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