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

    int one = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') one++;
    }
    if (one <= k) {
        cout << "Alice" << endl;
        return;
    }

    int x = n - k;
    if (n >= 2 * k) {
        cout << "Bob" << endl;
    } else {
        cout << "Alice" << endl;
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