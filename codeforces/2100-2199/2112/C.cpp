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
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    // a, b, c
    // a + b > c and a + b + c > mx.
    // a + b + c < 2 * (a + b) 所以 2 * (a + b) 小于等于 mx 的话那么无解。

    long long ans = 0;
    int mx = v[n - 1];
    for (int c = 2; c < n - 1; c++) {
        for (int a = 0; a < c - 1; a++) {
            int c_val = v[c];
            int a_val = v[a];
            int tmp = c_val - a_val;
            int tmp2 = mx - a_val - c_val;
            int mx = max(tmp, tmp2);
            // b 要大于 mx
            int idx = upper_bound(v.begin(), v.end(), mx) - v.begin();
            if (idx <= a) {
                idx = a + 1;
            }
            // debug(idx, a, c);
            ans += max(c - idx, 0);
        }
    }
    debug(ans);

    // c = n - 1

    int c = n - 1;
    for (int a = 0; a < c - 1; a++) {
        for (int b = a + 1; b < c; b++) {
            // a b c

            int mx = v[c - 1];
            if (b == c - 1) {
                if (a == c - 2) {
                    if (c - 3 >= 0) {
                        mx = v[c - 3];
                    } else {
                        mx = 0;
                    }
                } else {
                    mx = v[c - 2];
                }
            }

            if (v[a] + v[b] > v[c] && v[a] + v[b] + v[c] > mx) {
                ans++;
            }
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