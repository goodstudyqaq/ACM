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
typedef array<int, 2> a2;

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

    int ans = 0;
    if (s[0] == 'u') {
        s[0] = 's';
        ans++;
    }

    if (s[n - 1] == 'u') {
        s[n - 1] = 's';
        ans++;
    }

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && s[go] == 's') go++;

        if (go == n) break;
        int go2 = go;

        while (go2 < n && s[go2] == 'u') go2++;
        int l = go, r = go2 - 1;

        int len = r - l + 1;
        ans += len / 2;
        now = go2;
    }
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