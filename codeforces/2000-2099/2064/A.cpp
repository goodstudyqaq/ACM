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
    int n;
    string s;
    cin >> n >> s;

    int now = 0;
    while (now < n && s[now] == '0') now++;

    if (now == n) {
        cout << 0 << '\n';
        return;
    }
    int ans = 1;
    while (now < n) {
        int go = now;

        while (go < n && s[go] == '1') go++;
        if (go == n) break;
        ans++;
        int go2 = go;
        while (go2 < n && s[go2] == '0') go2++;
        if (go2 == n) break;
        ans++;
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