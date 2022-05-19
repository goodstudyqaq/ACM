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

    int sz = s.size();
    int q_num = count(s.begin(), s.end(), '?');
    if (q_num == sz) {
        cout << sz << endl;
        return;
    }
    int l = 0, r = sz - 1;

    for (int i = 0; i < sz; i++) {
        if (s[i] == '1') l = i;
    }

    for (int i = sz - 1; i >= 0; i--) {
        if (s[i] == '0') r = i;
    }

    cout << r - l + 1 << endl;
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