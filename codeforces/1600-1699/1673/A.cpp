#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += s[i] - 'a' + 1;
    }

    if (n == 1) {
        cout << "Bob" << ' ' << res << endl;
        return;
    }
    if (n % 2 == 0) {
        cout << "Alice" << ' ' << res << endl;
        return;
    } else {
        int get = max(res - (s[0] - 'a' + 1), res - (s[n - 1] - 'a' + 1));
        int other = min(s[0] - 'a' + 1, s[n - 1] - 'a' + 1);
        cout << "Alice" << ' ' << get - other << endl;
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