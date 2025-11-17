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

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && s[go] == '0') {
            go++;
        }
        if (go == n) break;
        int go2 = go;
        while (go2 < n && s[go2] == '1') {
            go2++;
        }
        int l = go2 - go;
        if (l >= k) {
            cout << "NO\n";
            return;
        }
        now = go2;
    }
    cout << "YES\n";

    int val = n;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            ans[i] = val;
            val--;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ans[i] = val;
            val--;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';


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