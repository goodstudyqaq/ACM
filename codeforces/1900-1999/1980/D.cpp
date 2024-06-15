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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> b(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        b[i] = gcd(a[i], a[i + 1]);
    }
    b[n] = 1e9;
    // debug(b);

    vector<int> f1(n + 1), f2(n + 1);
    f1[0] = 1;
    f1[1] = 1;
    for (int i = 2; i <= n - 1; i++) {
        f1[i] = f1[i - 1] && (b[i] >= b[i - 1]);
    }

    f2[n - 1] = 1;
    f2[n] = 1;
    for (int i = n - 2; i >= 1; i--) {
        f2[i] = f2[i + 1] && (b[i] <= b[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        // debug(i);
        if (i == 1) {
            if (f2[2]) {
                cout << "YES" << endl;
                return;
            }
        } else if (i == n) {
            if (f1[n - 2]) {
                cout << "YES" << endl;
                return;
            }
        } else {
            int tmp1 = gcd(a[i - 1], a[i + 1]);
            if (f1[i - 2] && b[i - 2] <= tmp1 && f2[i + 1] && b[i + 1] >= tmp1) {
                cout << "YES" << endl;
                return;
            }
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
    return 0;
}