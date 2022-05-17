#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    set<char> S;
    for (int i = 0; i < 6; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            char v = s[i] - 'A' + 'a';
            if (S.count(v) == 0) {
                cout << "NO" << endl;
                return;
            }
        } else {
            S.insert(s[i]);
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