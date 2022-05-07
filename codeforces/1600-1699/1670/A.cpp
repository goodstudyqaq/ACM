#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int num = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < 0) num++;
    }

    for (int i = 0; i < n; i++) {
        if (i < num) {
            a[i] = -abs(a[i]);
        } else {
            a[i] = abs(a[i]);
        }
    }
    cout << (is_sorted(a.begin(), a.end()) ? "YES" : "NO") << endl;
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