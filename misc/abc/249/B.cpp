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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    string s;
    cin >> s;

    bool f1 = false, f2 = false;

    set<int> S;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            f1 = true;
        } else {
            f2 = true;
        }
        if (S.count(s[i])) {
            cout << "No" << endl;
            return 0;
        }
        S.insert(s[i]);
    }
    if (f1 && f2) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}