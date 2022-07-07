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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int now = n - 1;
    while (now >= 0 && a[now] == 0) {
        now--;
    }
    if (now == -1) {
        cout << "YES" << endl;
        return;
    }

    if (a[now] > 0) {
        cout << "NO" << endl;
        return;
    }

    vector<ll> b(n);
    for (int i = 0; i <= now - 1; i++) {
        b[i] = 1;
    }

    while (now > 0) {
        debug(now, a[now], b[now]);
        if (b[now] <= a[now]) {
            cout << "NO" << endl;
            return;
        }
        ll tmp = b[now] - a[now];
        b[now - 1] += tmp - 1;
        now--;
    }

    if (b[0] == a[0]) {
        cout << "YES" << endl;
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