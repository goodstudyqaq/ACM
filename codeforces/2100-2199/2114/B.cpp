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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int zero = 0, one = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0')
            zero++;
        else
            one++;
    }

    int mx = zero / 2 + one / 2;

    int mi = mx - min(zero / 2, one / 2) * 2;

    if (k <= mx && k >= mi && (mx - k) % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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