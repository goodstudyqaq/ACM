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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    if (a[0] == a[n - 1]) {
        cout << "No" << endl;
        return;
    }
    int idx = 0;
    ll sum = 0;
    ll sum2 = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += a[i];

        int go_idx = n - i;
        if (go_idx >= i) break;
        while (idx <= go_idx) {
            sum2 += a[idx];
            idx++;
        }
        if (sum2 < sum) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
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