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

    auto check1 = [&]() {
        char it = s[0];
        for (int i = 0; i < n; i++) {
            if (s[i] != it) return false;
        }
        return true;
    };

    auto check2 = [&]() {
        for (int i = 1; i < n; i++) {
            if (s[i - 1] == s[i]) return true;
        }
        return false;
    };
    if (check1()) {
        cout << "YES" << endl;
        return;
    }

    if (check2()) {
        cout << "NO" << endl;
        return;
    }
    debug("zz");

    vector<bool> vis(26);

    int i;
    for (i = 0; i < n; i++) {
        if (vis[s[i] - 'a']) {
            break;
        }
        vis[s[i] - 'a'] = 1;
    }

    int len = i;
    for (int j = i; j < n; j++) {
        if (s[j] != s[j % len]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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