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

bool solve() {
    int n;
    string s;
    cin >> n >> s;

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && s[go] == 'W') go++;
        if (go == n) {
            break;
        }
        int go2 = go;
        bool f[2] = {false, false};
        while (go2 < n && s[go2] != 'W') {
            if (s[go2] == 'R')
                f[0] = true;
            else
                f[1] = true;
            go2++;
        }
        if (go2 - go == 1) return false;
        if (!f[0] || !f[1]) return false;
        now = go2;
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        bool f = solve();
        if (f) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}