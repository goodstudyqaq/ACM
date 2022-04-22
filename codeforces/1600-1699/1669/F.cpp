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
        int sum = 0;
        vector<int> a(n + 1);
        map<int, int> m;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += a[i];
            m[sum] = i;
        }

        int now = 0;
        int ans = 0;
        for (int i = n; i >= 1; i--) {
            now += a[i];
            if (m.count(now) && m[now] < i) {
                ans = max(ans, m[now] + n - i + 1);
            }
        }
        cout << ans << endl;
    }
}