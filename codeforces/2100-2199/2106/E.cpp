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
    vector<int> p(n);
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        idx[p[i]] = i;
    }

    auto work = [&](int l, int r, int k) -> int {
        int loc = idx[k];
        if (loc < l || loc > r) {
            return -1;
        }

        int less = k;
        int big = n - 1 - k;
        // debug(less, big);

        int big_num = 0, less_num = 0;
        while (l <= r) {
            int m = l + r >> 1;
            if (m == loc) {
                break;
            }
            // debug(m, p[m], loc, less, big);
            if (m < loc) {
                // p[m] 小于 k
                if (less == 0) return -1;
                if (p[m] > k) {
                    big_num++;
                    less--;
                    l = m + 1;
                } else {
                    less--;
                    l = m + 1;
                }
            } else {
                // p[m] 大于 k
                if (big == 0) return -1;
                if (p[m] < k) {
                    less_num++;
                    big--;
                    r = m - 1;
                } else {
                    big--;
                    r = m - 1;
                }
            }
        }
        int ans = max(big_num, less_num);

        return ans * 2;
    };

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--, k--;
        cout << work(l, r, k) << ' ';
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