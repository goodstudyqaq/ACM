#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;

    int now = 0;
    while (now < m && a[n - now - 1] == b[m - now - 1]) {
        now++;
    }

    if (now == m) {
        cout << "YES" << endl;
        return;
    }

    if (now == m - 1) {
        char it = b[0];
        for (int i = 0; i < n - now - 1; i++) {
            if (a[i] == it) {
                cout << "YES" << endl;
                return;
            }
        }
        cout << "NO" << endl;
    } else {
        cout << "NO" << endl;
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