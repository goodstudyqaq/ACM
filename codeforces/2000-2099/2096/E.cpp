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
    string s;
    cin >> n >> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = (s[i] == 'P');
    }

    long long inv = 0;
    int one = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == 1) {
            one += 1;
        } else {
            inv += one;
        }
    }

    int zero = n - one;

    int even_zero = 0;
    for (int i = 0; i < n; i += 2) {
        if (v[i] == 0) {
            even_zero++;
        }
    }
    int d = abs((zero + 1) / 2 - even_zero);

    long long ans = (inv - d) / 2 + d;
    cout << ans << '\n';
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