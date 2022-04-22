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
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        for (int i = 30; i >= 0 && k; i--) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if ((a[j] >> i) & 1) continue;
                cnt++;
            }
            if (k >= cnt) {
                for (int j = 0; j < n; j++) {
                    if ((a[j] >> i) & 1) continue;
                    a[j] += (1 << i);
                }
                k -= cnt;
            }
        }

        int ans = a[0];
        for (int i = 1; i < n; i++) {
            ans = ans & a[i];
        }
        cout << ans << endl;
    }
    return 0;
}