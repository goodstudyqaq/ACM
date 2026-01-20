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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    int l = 0, r = mx;
    int ans = mx;

    auto check = [&](int mx) {
        int need = 0;

        int now = 0;
        while (now < n) {
            int go = now;

            int wrong_num = 0;
            while (go < n) {
                if (a[go] > mx && s[go] == 'R') {
                    break;
                }

                if (a[go] > mx) {
                    wrong_num++;
                }
                go++;
            }
            if (wrong_num > 0) {
                need++;
            }
            now = go + 1;
        }

        return need <= k;
    };

    // debug(check(2));

    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << '\n';
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