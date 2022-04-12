#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> V(n + 1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            V[p]++;
        }
        V[0] = 1;
        vector<int> f(n + 1);
        iota(f.begin(), f.end(), 0);

        sort(f.begin(), f.end(), [&](int a, int b) {
            return V[a] > V[b];
        });

        int no0 = 0;
        for (int i = 0; i < f.size(); i++) {
            no0 = i;
            if (V[f[i]] == 0) break;
        }

        auto check = [&](int val) -> bool {
            int cnt = 0;
            for (int i = 0, now = 0; i < no0; i++, now++) {
                int sz = V[f[i]];
                int auto_grow = min(sz, val - now);
                sz -= auto_grow;
                cnt += sz;
            }
            return no0 + cnt <= val;
        };

        int l = 1, r = n;
        int ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}