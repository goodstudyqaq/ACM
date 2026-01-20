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
    int n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    x = abs(x);
    y = abs(y);
    int four = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '4') four++;
    }

    int eight = n - four;
    x -= eight, y -= eight;

    x = max(x, 0);
    y = max(y, 0);
    if (x + y <= four) {
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