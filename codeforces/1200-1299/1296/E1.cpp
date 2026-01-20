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
    string s;
    cin >> n >> s;

    vector<int> color(n, -1);
    color[0] = 0;
    int last_idx = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] >= s[last_idx]) {
            color[i] = 0;
            last_idx = i;
        } else {
            color[i] = 1;
        }
    }

    last_idx = -1;
    for (int i = 1; i < n; i++) {
        if (color[i] == 1) {
            if (last_idx == -1 || s[i] >= s[last_idx]) {
                last_idx = i;
            } else {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << color[i];
    }
    cout << '\n';
}