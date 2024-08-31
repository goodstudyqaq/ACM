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
    long long n, x;
    cin >> n >> x;
    long long ans = 0;
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n / a; b++) {
            long long ab = a * b;
            if (ab > n) break;
            long long a_b = a + b;
            if (a_b > x) break;
            // ab + (a + b) * c <= n
            long long tmp = (n - ab) / a_b;
            // a + b + c <= x
            long long tmp2 = x - a_b;
            ans += min(tmp, tmp2);
        }
    }
    cout << ans << endl;
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