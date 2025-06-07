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
    int n;
    string s, t;
    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o' && t[i] == 'o') {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}