#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int m = s.size();

    int R = 0, D = 0;
    for (int i = 0; i < m; i++) {
        if (s[i] == 'R')
            R++;
        else
            D++;
    }
    if (R == 0 || D == 0) {
        cout << n << endl;
        return;
    }

    ll right = n - 1 - R;
    ll down = n - 1 - D;
    ll ans = 1LL * (right + 1) * (down + 1) + m;
    debug(ans);
    debug(R, D);

    for (int i = m - 1; i >= 0; i--) {
        if (s[i] == 'R') {
            if (D == 0) break;
            ans += down;
            R--;
        } else {
            if (R == 0) break;
            ans += right;
            D--;
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
}