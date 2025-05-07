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

    int n, m;
    cin >> n >> m;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int len = 0;
        int now_st = 0;
        for (int j = m - 1; j >= 0; j--) {
            if (s[j] == 'B') {
                len = m - j + 1;
                now_st ^= len;
                ans ^= now_st;
            }
        }
    }
    if (ans) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}