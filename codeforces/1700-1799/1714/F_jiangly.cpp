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
    int n, d12, d23, d31;
    cin >> n >> d12 >> d23 >> d31;
    if ((d12 + d23 + d31) % 2) {
        cout << "NO" << endl;
        return;
    }

    int x1 = (d12 + d31 - d23) / 2;
    int x2 = (d12 + d23 - d31) / 2;
    int x3 = (d31 + d23 - d12) / 2;
    // debug(x1, x2, x3);
    if (x1 < 0 || x2 < 0 || x3 < 0) {
        cout << "NO" << endl;
        return;
    }

    if (x1 + x2 + x3 + 1 > n) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    int root;
    int now;
    if (x1 == 0) {
        root = 1;
        now = 4;
    } else if (x2 == 0) {
        root = 2;
        now = 4;
    } else if (x3 == 0) {
        root = 3;
        now = 4;
    } else {
        root = 4;
        now = 5;
    }

    if (x1) {
        int last = root;
        for (int i = 1; i < x1; i++) {
            cout << last << ' ' << now << endl;
            last = now;
            now++;
        }
        cout << last << ' ' << 1 << endl;
    }
    if (x2) {
        int last = root;
        for (int i = 1; i < x2; i++) {
            cout << last << ' ' << now << endl;
            last = now;
            now++;
        }
        cout << last << ' ' << 2 << endl;
    }
    if (x3) {
        int last = root;
        for (int i = 1; i < x3; i++) {
            cout << last << ' ' << now << endl;
            last = now;
            now++;
        }
        cout << last << ' ' << 3 << endl;
    }

    while (now <= n) {
        cout << root << ' ' << now << endl;
        now++;
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