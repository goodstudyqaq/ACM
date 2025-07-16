#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    string s, t;
    cin >> s >> t;
    set<char> T;
    for (auto it : t) {
        T.insert(it);
    }

    for (int i = 1; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            if (T.count(s[i - 1]) == 0) {
                cout << "No\n";
                return 0;
            }
        }
    }
    cout << "Yes\n";
    return 0;
}