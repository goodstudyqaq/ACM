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
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }

        vector<int> a(n, 1);
        for (int i = 0; i < n; i++) {
            if (c[i] == n) break;
            int val = max(c[i], i);
            a[val] = 0;
            c[val] += val;
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << " \n"[i == n - 1];
        }
    }
    return 0;
}