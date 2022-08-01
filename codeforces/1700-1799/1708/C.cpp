
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

void solve() {
    int n, q;
    cin >> n >> q;
    int tmp_q = q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int l = 0, r = n;

    int ans = -1;

    auto check = [&](int idx) {
        int now = q;
        for (int i = idx + 1; i <= n; i++) {
            if (now < a[i]) {
                now--;
            }
        }
        if (now < 0) return false;
        return true;
    };

    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    debug(ans);

    int now = q;
    int cnt = 0;
    vector<int> res(n + 1, 1);
    for (int i = 1; i <= ans; i++) {
        if (now < a[i]) {
            res[i] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i];
    }
    cout << endl;
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