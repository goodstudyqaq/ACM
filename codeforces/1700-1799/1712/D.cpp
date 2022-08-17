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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == k) {
        cout << 1000000000 << endl;
        return;
    }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int x, int y) -> bool {
        return a[x] < a[y];
    });

    auto work = [&]() {
        int mi = 1e9;
        for (int i = 0; i < n; i++) {
            mi = min(mi, a[i]);
        }

        int mx = 0;
        // debug(a);
        for (int i = 0; i < n - 1; i++) {
            mx = max(mx, min({a[i], a[i + 1], 2 * mi}));
        }
        // mx = max(mx, 2 * mi);
        return mx;
    };

    if (k == 1) {
        int mi1 = a[idx[0]];
        a[idx[0]] = 1e9;
        // 换最小值
        int mx = work();
        a[idx[0]] = mi1;
        // 不换
        for (int i = 0; i < n - 1; i++) {
            mx = max({mx, min(max(a[i], a[i + 1]), 2 * mi1)});
        }
        cout << mx << endl;
    } else {
        for (int i = 0; i < k - 2; i++) {
            a[idx[i]] = 1e9;
        }

        // 把两个最小值换掉
        int tmp1 = a[idx[k - 2]], tmp2 = a[idx[k - 1]];
        a[idx[k - 2]] = a[idx[k - 1]] = 1e9;
        int mx = work();
        debug(mx);
        a[idx[k - 2]] = tmp1, a[idx[k - 1]] = tmp2;

        // 换一个最小值
        a[idx[k - 2]] = 1e9;
        int mi = a[idx[k - 1]];
        for (int i = 0; i < n - 1; i++) {
            mx = max({mx, min(max(a[i], a[i + 1]), 2 * mi)});
        }
        debug(mx);
        a[idx[k - 2]] = tmp1;

        mi = a[idx[k - 2]];
        mx = max(mx, min(2 * mi, 1000000000));
        cout << mx << endl;
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
}