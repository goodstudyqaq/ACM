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
    int n, x;
    ll k;
    cin >> n >> x >> k;

    string s;
    cin >> s;

    int now = 0;

    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            now--;
        } else {
            now++;
        }
        if (now == 0) {
            idx = i;
            break;
        }
    }

    int need_time = (idx == -1 ? -1 : idx + 1);
    now = x;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            now--;
        } else {
            now++;
        }
        if (now == 0) {
            ll ans = 1;
            ll left = k - i - 1;

            if (need_time != -1) {
                ans += left / need_time;
            }
            cout << ans << '\n';
            return;
        }
    }
    cout << 0 << '\n';
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