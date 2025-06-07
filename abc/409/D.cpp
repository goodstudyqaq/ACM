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

    int idx = -1;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] > s[i + 1]) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << s << '\n';
        return;
    }

    int idx2 = -1;
    for (int i = idx + 2; i < n; i++) {
        if (s[idx] < s[i]) {
            idx2 = i - 1;
            break;
        }
    }
    if (idx2 == -1) {
        idx2 = n - 1;
    }
    debug(idx, idx2);

    string ans = s.substr(0, idx) + s.substr(idx + 1, idx2 - idx) + s[idx] + s.substr(idx2 + 1);
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