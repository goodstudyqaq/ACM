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
    string s, b;
    cin >> s >> b;

    if (b == "a") {
        cout << 1 << endl;
        return;
    }

    int bn = b.size();
    for (int i = 0; i < bn; i++) {
        if (b[i] == 'a') {
            cout << -1 << endl;
            return;
        }
    }

    int sn = s.size();
    cout << (1LL << sn) << endl;
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