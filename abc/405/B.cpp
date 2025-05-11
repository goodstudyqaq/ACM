#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }

    for (int i = 1; i <= m; i++) {
        if (M[i] == 0) {
            cout << 0 << '\n';
            return 0;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        M[a[i]]--;
        if (M[a[i]] == 0) {
            cout << n - i << '\n';
            return 0;
        }
    }
}