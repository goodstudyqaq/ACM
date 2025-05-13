#include <bits/stdc++.h>

#include <cassert>

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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<long long> sum_a(n / 2), sum_b(m / 2);
    for (int i = 0; i < n / 2; i++) {
        sum_a[i] = a[n - 1 - i] - a[i];
        if (i) {
            sum_a[i] += sum_a[i - 1];
        }
    }

    for (int i = 0; i < m / 2; i++) {
        sum_b[i] = b[m - 1 - i] - b[i];
        if (i) {
            sum_b[i] += sum_b[i - 1];
        }
    }

    // 2x + y <= n
    // x + 2y <= m

    int mx_x = min(n / 2, m);
    int K = (n + m) / 3;
    vector<long long> ans(K + 1);
    int kmax = 0;

    auto get_res = [&](int x, int y) {
        long long res = 0;
        if (x) res += sum_a[x - 1];
        if (y) res += sum_b[y - 1];
        debug(x, y, res);
        return res;
    };

    for (int k = 1; k <= K; k++) {
        debug(k);
        int l = 2 * k - m, r = min(n - k, k);
        if (l > r || r < 0) {
            break;
        }
        l = max(l, 0);
        kmax = k;

        r--;
        int ansx = l - 1;
        while (l <= r) {
            debug(l, r);
            int x = l + r >> 1;
            int y = k - x;
            long long tmp1 = get_res(x, y);
            long long tmp2 = get_res(x + 1, y - 1);
            if (tmp1 <= tmp2) {
                ansx = x;
                l = x + 1;
            } else if (tmp1 > tmp2) {
                r = x - 1;
            } else {
                // 这种情况只会出现最顶端
                assert(false);
            }
        }

        ans[k] = get_res(ansx + 1, k - (ansx + 1));
    }

    cout << kmax << '\n';
    for (int i = 1; i <= kmax; i++) {
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