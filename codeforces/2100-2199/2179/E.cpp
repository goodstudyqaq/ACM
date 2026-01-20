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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;

    vector<ll> a(n), b(n);
    ll asum = 0, bsum = 0;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    int two = 0;
    for (int i = 0; i < n; i++) {
        int half = p[i] / 2;
        a[i] += half;
        b[i] += half;
        if (p[i] % 2 == 0) {
            if (s[i] == '0') {
                a[i] += 1;
                b[i] -= 1;
            } else {
                b[i] += 1;
                a[i] -= 1;
            }
            two++;
        } else {
            if (s[i] == '0') {
                a[i]++;
            } else {
                b[i]++;
            }
        }
    }
    debug(a, b);
    for (int i = 0; i < n; i++) {
        asum += a[i];
        bsum += b[i];
    }

    if (asum > x || bsum > y) {
        cout << "NO\n";
        return;
    }
    x -= asum;
    y -= bsum;

    // s has 0 and 1

    bool one = false, zero = false;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            zero = true;
        else
            one = true;
    }
    if (zero && one) {
        cout << "YES\n";
        return;
    }

    if (zero == false) {
        if (x > y + two) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
        return;
    } else {
        if (x + two < y) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
        return;
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