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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }

    vector<int> ans(n + 1);

    auto get_cnt = [&](int block, int m) {
        int sum = 0;
        for (int i = 0; i <= n; i += block) {
            int r = min(n, i + m);
            sum += cnt[r];
            if (i - 1 >= 0) {
                sum -= cnt[i - 1];
            }
        }
        return sum;
    };
    // debug(get_cnt(5, 1));
    // debug(get_cnt(5, 2));

    for (int i = 1; i <= n; i++) {
        int l = 0, r = i - 1;
        int res = -1;
        while (l <= r) {
            int m = l + r >> 1;
            int _cnt = get_cnt(i, m);

            if (_cnt <= n / 2) {
                res = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        ans[i] = res + 1;
    }

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
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
    return 0;
}