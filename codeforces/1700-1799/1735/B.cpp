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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mi = *min_element(a.begin(), a.end());
    int mod = mi * 2 - 1;

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > mod) {
            int tmp = a[i] / mod - 1;
            int left = a[i] % mod;
            if (left > 0) tmp++;
            debug(i, tmp);
            // if (left < mi && left) {
            //     tmp++;
            // }
            res += tmp;
        }
    }
    cout << res << endl;
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