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
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long ans = 1e18;
    for (int i = 1; i <= n; i++) {
        // b[i] = 0;
        long long nans = 0;
        long long lst = 0;
        for (int j = i + 1; j <= n; j++) {
            long long step = a[j];
            long long tmp = lst / step + 1;
            nans += tmp;
            lst = step * tmp;
        }
        lst = 0;
        for (int j = i - 1; j >= 1; j--) {
            long long step = a[j];
            long long tmp = lst / step + 1;
            nans += tmp;
            lst = step * tmp;
        }
        ans = min(ans, nans);
    }
    cout << ans << endl;
}