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

    int n = s.size();
    int now = 0;
    int res = 0;
    while (now < n) {
        set<char> S;
        int go = now;
        while (go < n && S.count(s[go]) == 0) {
            S.insert(s[go]);
            go++;
        }
        if (go == n) {
            res += go - now;
        } else {
            res += go - now - 1;
        }
        now = go + 1;
    }
    cout << res << endl;
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