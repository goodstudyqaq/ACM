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
    vector<int> a(n);
    bool valid = true;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long lcm = 1;
    for (int i = 0; i < n - 1; i++) {
        if (a[i + 1] % a[i]) {
            int g = gcd(a[i], a[i + 1]);
            debug(i, g, a[i] / g);

            long long tmp = a[i] / g;

            long long tmp2 = gcd(lcm, tmp);
            lcm = lcm * tmp / tmp2;
        }
    }
    cout << lcm << '\n';
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