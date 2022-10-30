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
    int n;
    cin >> n;

    vector<int> a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    auto work = [&](int val) -> int {
        // debug(val);
        int res = 0;

        int now = 1;
        int now_val = 0;
        while (now <= n) {
            int go = now;
            while (go <= n && now_val < val) {
                now_val += a[go];
                go++;
            }
            if (now_val != val) return n + 10;
            int len = go - now;
            res = max(res, len);
            now = go;
            now_val = 0;
        }
        // debug(val, res);
        return res;
    };

    int ans = n + 10;
    for (int i = 1; i * i <= sum; i++) {
        if (sum % i == 0) {
            ans = min(ans, work(i));
            ans = min(ans, work(sum / i));
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