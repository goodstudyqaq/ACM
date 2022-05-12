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
    set<int> S;
    vector<int> a(n);
    int zero_num = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S.insert(a[i]);
        if (a[i] == 0) {
            zero_num++;
        }
    }

    if (S.count(0)) {
        cout << n - zero_num << endl;
    } else {
        int sz = S.size();
        if (sz == n) {
            cout << n + 1 << endl;
        } else {
            cout << n << endl;
        }
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