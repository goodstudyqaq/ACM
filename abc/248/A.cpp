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
    vector<int> vis(10);
    for (auto it : s) {
        vis[it - '0'] = 1;
    }
    for (int i = 0; i < 10; i++) {
        if (vis[i] == 0) {
            cout << i << endl;
            return 0;
        }
    }
}