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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    ll sum = 0;
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        S.insert(i);
    }
    int change = -1;
    debug(q);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            if (S.count(i)) {
                sum = sum - a[i] + x;
            } else {
                sum = sum - change + x;
                S.insert(i);
            }
            a[i] = x;
            cout << sum << endl;
        } else if (t == 2) {
            int x;
            cin >> x;
            S.clear();
            change = x;
            sum = 1LL * n * x;
            cout << sum << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}