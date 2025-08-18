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
    vector<int> p(n), s(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < n - 1; i++) {
        if (p[i] < p[i + 1]) {
            cout << "NO" << endl;
            return;
        }
    }

    for (int i = n - 1; i > 0; i--) {
        if (s[i] < s[i - 1]) {
            cout << "NO" << endl;
            return;
        }
    }
    if (p[n - 1] != s[0]) {
        cout << "NO" << endl;
        return;
    }


    vector<long long> ans(n);
    for (int i = 0; i < n; i++) {
        int tmp = gcd(p[i], s[i]);
        ans[i] = 1LL * p[i] * s[i] / tmp;
    }

    long long g = 0;
    for (int i = 0; i < n; i++) {
        g = gcd(g, ans[i]);
        if (g != p[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    g = 0;
    for (int i = n - 1; i >= 0; i--) {
        g = gcd(g, ans[i]);
        if (g != s[i]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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