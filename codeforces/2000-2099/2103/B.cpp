#include <bits/stdc++.h>

#include <algorithm>

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
    string s;
    cin >> s;

    int ans = n;
    char now = '0';
    for (int i = 0; i < n; i++) {
        if (now != s[i]) {
            ans++;
        }
        now = s[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (s[i] == '1') cnt++;
        } else {
            if (s[i - 1] == '0' && s[i] == '1') {
                cnt++;
            }
        }
    }

    int cnt2 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '1' && s[i + 1] == '0') cnt2++;
    }

    if (cnt == 0) {
        cout << ans << '\n';
    } else if (cnt == 1) {
        if (cnt2) {
            cout << ans - 1 << '\n';
        } else {
            cout << ans << '\n';
        }
    } else {
        cout << ans - 2 << '\n';
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