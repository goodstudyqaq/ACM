#include <bits/stdc++.h>

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
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    set<int> S1[2], S2[2];

    S1[0].insert(a[n]);
    S1[1].insert(b[n]);

    S2[0].insert(b[n]);
    S2[0].insert(a[n - 1]);
    S2[1].insert(b[n - 1]);
    S2[1].insert(a[n]);

    auto check = [&](set<int> &S1, set<int> &S2, int v1, int v2) {
        if (S1.count(v1)) {
            return true;
        }
        if (S2.count(v2)) {
            return true;
        }
        if (v1 == v2) {
            return true;
        }
        return false;
    };

    if (a[n] == b[n]) {
        cout << n << '\n';
        return;
    }

    if (check(S1[0], S1[1], a[n - 1], b[n - 1])) {
        cout << n - 1 << '\n';
        return;
    }

    for (int i = n - 2; i >= 1; i--) {
        if (check(S2[0], S2[1], a[i], b[i])) {
            cout << i << '\n';
            return;
        }
        if (check(S1[0], S1[1], a[i], b[i])) {
            cout << i << '\n';
            return;
        }

        S1[0].insert(b[i + 1]);
        S1[1].insert(a[i + 1]);
        swap(S1[0], S1[1]);

        S2[0].insert(b[i]);
        S2[1].insert(a[i]);
        swap(S2[0], S2[1]);
    }
    cout << 0 << '\n';
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