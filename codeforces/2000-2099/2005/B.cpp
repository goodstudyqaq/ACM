#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());
    while (q--) {
        int a;
        cin >> a;
        if (a < b[0]) {
            cout << b[0] - 1 << endl;
        } else if (a > b[m - 1]) {
            cout << n - b[m - 1] << endl;
        } else {
            int idx = lower_bound(b.begin(), b.end(), a) - b.begin();

            int idx2 = idx - 1;

            int len = b[idx] - b[idx2];
            cout << len / 2 << endl;
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
    return 0;
}